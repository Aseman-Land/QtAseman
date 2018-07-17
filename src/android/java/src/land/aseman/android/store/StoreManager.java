/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

package land.aseman.android.store;

import land.aseman.android.AsemanApplication;
import land.aseman.android.AsemanActivity;
import land.aseman.android.AsemanService;

import land.aseman.android.store.util.IabHelper;
import land.aseman.android.store.util.IabResult;
import land.aseman.android.store.util.Inventory;
import land.aseman.android.store.util.Purchase;
import land.aseman.android.store.util.SkuDetails;
import com.android.vending.billing.IInAppBillingService;

import android.util.Log;
import android.content.Context;
import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Iterator;

public class StoreManager
{
    static final String STORE_MANAGER_TAG = "StoreManager";
    static final int STORE_MANAGER_RC_REQUEST = 0;

    boolean _storeHasFound;
    String _storeManagerLastPurchaseSku;
    public IabHelper mStoreManagerHelper;

    public native void _inventoryStateChanged(String sku, boolean state);
    public native void _setupFinished(boolean state);
    public native void _detailsFetched(String sku, String type, String price, String title, String description);

    private HashMap<String, Boolean> data = new HashMap<String, Boolean>();
    public static HashSet<StoreManager> instances = new HashSet<StoreManager>();

    StoreManager() {
        instances.add(this);
    }

    public void end() {
        if (mStoreManagerHelper != null) mStoreManagerHelper.dispose();
        mStoreManagerHelper = null;
        instances.remove(this);
    }

    public static Context getContext() {
        if(AsemanActivity.getActivityInstance() != null)
            return AsemanActivity.getActivityInstance();
        else
        if(AsemanService.getServiceInstance() != null)
            return AsemanService.getServiceInstance();
        else
            return AsemanApplication.getAppContext();
    }

    public void setup(String base64EncodedPublicKey, String storePackageName, String billingBindIntentPath) {
        if (mStoreManagerHelper != null)
            mStoreManagerHelper.dispose();

        List moreSkus = new ArrayList();
        HashMap<String, Boolean> inventoriesMap = data;
        if (inventoriesMap != null) {
            Iterator it = inventoriesMap.keySet().iterator();
            while(it.hasNext()) {
                String inventoryKey = (String)it.next();
                moreSkus.add(inventoryKey);
            }
        }

        final List _moreSkus = moreSkus;
        mStoreManagerHelper = new IabHelper(getContext(), base64EncodedPublicKey);
        try {
            Log.d(STORE_MANAGER_TAG, "Starting setup.");
            mStoreManagerHelper.startSetup(storePackageName, billingBindIntentPath,
                new IabHelper.OnIabSetupFinishedListener() {
                    public void onIabSetupFinished(IabResult result) {
                        if (!result.isSuccess()) {
                            Log.d(STORE_MANAGER_TAG, "Problem setting up In-app Billing: " + result);
                        } else {
                            _storeHasFound = true;
                            mStoreManagerHelper.queryInventoryAsync(true, _moreSkus, mGotInventoryListener);
                            Log.d(STORE_MANAGER_TAG, "Setup finished.");
                        }
                        _setupFinished(_storeHasFound);
                    }
                });

        } catch(Exception e) {
            return;
        }
    }

    public void updateStates() {
        if(!_storeHasFound)
            return;

        Log.d(STORE_MANAGER_TAG, "Start getting inventories.");
        try {
            mStoreManagerHelper.queryInventoryAsync(mGotInventoryListener);
        } catch(Exception e) {
            return;
        }
    }

    public boolean containsInventory(String sku) {
        return data.containsKey(sku);
    }

    public void setState(String sku, boolean state) {
        boolean contains = data.containsKey(sku);
        data.put(sku, state);
        if(contains)
            _inventoryStateChanged(sku, state);
    }

    public void insertInventory(String sku, boolean state) {
        data.put(sku, state);
    }

    public void insertInventory(String sku) {
        if(!containsInventory(sku))
            insertInventory(sku, false);
    }

    public void removeInventory(String sku) {
        data.remove(sku);
    }

    public boolean getState(String sku) {
        return data.get(sku).booleanValue();
    }

    public void purchaseInventory(String sku) {
        Log.d(STORE_MANAGER_TAG, "Start purchasing " + sku);
        try {
            _storeManagerLastPurchaseSku = sku;
            mStoreManagerHelper.launchPurchaseFlow(AsemanActivity.getActivityInstance(), sku, STORE_MANAGER_RC_REQUEST, mPurchaseFinishedListener, "payload-string");
        } catch(Exception e) {
            return;
        }
    }

    public int count() {
        return data.size();
    }

    public void clear() {
        data.clear();
    }

    IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(STORE_MANAGER_TAG, "Query inventory finished.");
            if (result.isFailure()) {
                Log.d(STORE_MANAGER_TAG, "Failed to query inventory: " + result);
                return;
            }
            else {
                Log.d(STORE_MANAGER_TAG, "Query inventory was successful.");

                HashMap<String, Boolean> inventoriesMap = data;
                if (inventoriesMap != null) {
                    Iterator it = inventoriesMap.keySet().iterator();
                    while(it.hasNext()) {
                        String inventoryKey = (String)it.next();
                        boolean newState = inventory.hasPurchase(inventoryKey);
                        setState(inventoryKey, newState);

                        SkuDetails detail = inventory.getSkuDetails(inventoryKey);
                        if(detail != null)
                            _detailsFetched(detail.getSku(), detail.getType(), detail.getPrice(), detail.getTitle(), detail.getDescription());
                    }
                }
            }
        }
    };

    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            if (result.isFailure()) {
                Log.d(STORE_MANAGER_TAG, "Error purchasing: " + result);
                setState(_storeManagerLastPurchaseSku, false);
                return;
            }
            else
                setState(purchase.getSku(), true);
        }
    };
}
