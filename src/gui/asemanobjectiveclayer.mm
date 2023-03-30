#include "asemanobjectiveclayer.h"
#include "asemantools.h"

#import <UIKit/UIKit.h>
#import <SafariServices/SafariServices.h>
#import <Foundation/Foundation.h>

#ifndef DISABLE_IOS_CONTACTS_SUPPORT
#import <Contacts/Contacts.h>
#endif

#include <QSet>
#include <QUrl>
#include <QDesktopServices>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>

QSet<AsemanObjectiveCLayer*> ObjectiveCLayer_mObjects;

@interface AsemanObjectiveCLayer_core : NSObject;
@end

@implementation AsemanObjectiveCLayer_core

#pragma mark - Methods

- (void)keyboardWillShow:(NSNotification *)notification
{
    CGFloat height = [[[notification userInfo] objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size.height;
    for (auto o: ObjectiveCLayer_mObjects)
        o->setKeyboardHeight(height);
}

@end


AsemanObjectiveCLayer::AsemanObjectiveCLayer(QObject *parent)
    : QObject(parent)
{

    ObjectiveCLayer_mObjects.insert(this);
    AsemanObjectiveCLayer_core *core = [AsemanObjectiveCLayer_core alloc];

    [[NSNotificationCenter defaultCenter] addObserver:core selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
}

AsemanObjectiveCLayer::~AsemanObjectiveCLayer()
{
    ObjectiveCLayer_mObjects.remove(this);
}

qreal AsemanObjectiveCLayer::statusBarHeight()
{
    CGFloat menuBarHeight = [UIApplication sharedApplication].statusBarFrame.size.height;
    return menuBarHeight;
}

qreal AsemanObjectiveCLayer::navigationBarHeight()
{
    CGFloat navBarHeight = 0;
    if (statusBarHeight() > 24)
        return 22;
    return navBarHeight;
}

bool AsemanObjectiveCLayer::saveToCameraRoll(const QString &filePath)
{
    auto path = AsemanTools::urlToLocalPath(filePath);

    NSString *imagePath = path.toNSString();
    UIImage *image = [[UIImage alloc] initWithContentsOfFile:imagePath];

    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
    return true;
}

void AsemanObjectiveCLayer::getContactList(std::function<void(const QVariantList &res)> asyncCallback)
{
#ifndef DISABLE_IOS_CONTACTS_SUPPORT
    CNContactStore *store = [[CNContactStore alloc] init];
    [store requestAccessForEntityType:CNEntityTypeContacts completionHandler:^(BOOL granted, NSError * _Nullable) {
        QMap<QString, QVariantList> sorted;
        if (granted)
        {
            NSArray *keys = @[CNContactNamePrefixKey, CNContactFamilyNameKey, CNContactGivenNameKey, CNContactPhoneNumbersKey, CNContactImageDataKey, CNContactEmailAddressesKey];

            NSString *containerId = store.defaultContainerIdentifier;
            NSPredicate *predicate = [CNContact predicateForContactsInContainerWithIdentifier:containerId];
            NSArray *cnContacts = [store unifiedContactsMatchingPredicate:predicate keysToFetch:keys error:nil];

            for (CNContact *contact in cnContacts)
            {
                QString name = QString(QString::fromNSString(contact.givenName) + " " + QString::fromNSString(contact.familyName)).trimmed();
                for (CNLabeledValue *label in contact.phoneNumbers)
                {
                    NSString *phone = [label.value stringValue];
                    if ([phone length] > 0)
                        sorted[name] << QVariantMap({{"name", name}, {"phone", QString::fromNSString(phone)}});
                }
            }
        }

        QVariantList result;
        for (const auto &vals: sorted)
            result << vals;
        asyncCallback(result);
    }];
#else
    asyncCallback(QVariantList());
#endif
}

void AsemanObjectiveCLayer::sharePaper(const QString &text)
{
    UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
    NSString *textToShare = text.toNSString();
    UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:@[textToShare] applicationActivities:nil];
    activityVC.excludedActivityTypes = @[UIActivityTypePrint, UIActivityTypeCopyToPasteboard, UIActivityTypeAssignToContact, UIActivityTypeSaveToCameraRoll]; //Exclude whichever aren't relevant
            [controller presentViewController:activityVC animated:YES completion:nil];
}

QString AsemanObjectiveCLayer::deviceId()
{
    UIDevice *device = [UIDevice currentDevice];
    NSString  *currentDeviceId = [[device identifierForVendor]UUIDString];
    return QString::fromNSString(currentDeviceId);
}

bool AsemanObjectiveCLayer::openUrlInSafari(const QString &str)
{
    auto url = QUrl(str).toNSURL();

    if ([SFSafariViewController class]) {

        QEventLoop loop;

        UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
        SFSafariViewController *viewController = [[SFSafariViewController alloc] initWithURL:url];
        [controller presentViewController:viewController animated:YES completion: nil];

        auto t = new QTimer;
        t->connect(t, &QTimer::timeout, [&](){
            if (viewController.beingDismissed)
                loop.exit();
        });
        t->start(100);

        loop.exec();

        delete t;
        return true;
    } else {
        return false;
    }
}

void AsemanObjectiveCLayer::triggerVibrateFeedback()
{
    // Create an instance of the feedback generator
    auto generator = [[UIImpactFeedbackGenerator alloc] initWithStyle:UIImpactFeedbackStyleLight];

    // Trigger the feedback
    [generator impactOccurred];
}

qreal AsemanObjectiveCLayer::keyboardHeight() const
{
    return mKeyboardHeight;
}

void AsemanObjectiveCLayer::setKeyboardHeight(const qreal &keyboardHeight)
{
    if (mKeyboardHeight == keyboardHeight)
        return;
    mKeyboardHeight = keyboardHeight;
    Q_EMIT keyboardHeightChanged();
}
