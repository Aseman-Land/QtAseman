#include "asemanobjectiveclayer.h"
#include "asemantools.h"

#import <UIKit/UIKit.h>
#import <Contacts/Contacts.h>

AsemanObjectiveCLayer::AsemanObjectiveCLayer()
{

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
    UIImage *image = [[[UIImage alloc] initWithContentsOfFile:imagePath]autorelease];

    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
    return true;
}

void AsemanObjectiveCLayer::getContactList(std::function<void(const QVariantList &res)> asyncCallback)
{
    CNContactStore *store = [[CNContactStore alloc] init];
    [store requestAccessForEntityType:CNEntityTypeContacts completionHandler:^(BOOL granted, NSError * _Nullable) {
        QVariantMap sorted;
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
                        sorted.insertMulti(name, QVariantMap({{"name", name}, {"phone", QString::fromNSString(phone)}}));
                }
            }
        }

        asyncCallback(sorted.values());
    }];
}

void AsemanObjectiveCLayer::sharePaper(const QString &text)
{
    UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
    NSString *textToShare = text.toNSString();
    UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:@[textToShare] applicationActivities:nil];
    activityVC.excludedActivityTypes = @[UIActivityTypePrint, UIActivityTypeCopyToPasteboard, UIActivityTypeAssignToContact, UIActivityTypeSaveToCameraRoll]; //Exclude whichever aren't relevant
            [controller presentViewController:activityVC animated:YES completion:nil];
}

