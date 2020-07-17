#include <QCoreApplication>
#include <UIKit/UIKit.h>
#include <QPointer>
#include <QtCore>
#include <QImage>
#include "qisystemdispatcher.h"
#include "qiviewdelegate.h"
#include "quickios.h"

@interface QIOSViewController : UIViewController
@property (nonatomic, assign) BOOL prefersStatusBarHidden;
@property (nonatomic, assign) UIStatusBarAnimation preferredStatusBarUpdateAnimation;
@property (nonatomic, assign) UIStatusBarStyle preferredStatusBarStyle;
@end

static QImage fromUIImage(UIImage* image) {
    QImage::Format format = QImage::Format_RGB32;

    CGColorSpaceRef colorSpace = CGImageGetColorSpace(image.CGImage);
    CGFloat width = image.size.width;
    CGFloat height = image.size.height;

    long int orientation = [image imageOrientation];
    int degree = 0;

    switch (orientation) {
    case UIImageOrientationLeft:
        degree = -90;
        break;
    case UIImageOrientationDown: // Down
        degree = 180;
        break;
    case UIImageOrientationRight:
        degree = 90;
        break;
    }

    if (degree == 90 || degree == -90)  {
        CGFloat tmp = width;
        width = height;
        height = tmp;
    }

    QSizeF size(width,height);

    QImage result = QImage(size.toSize(),format);

    CGContextRef contextRef = CGBitmapContextCreate(result.bits(),                 // Pointer to  data
                                                   width,                       // Width of bitmap
                                                   height,                       // Height of bitmap
                                                   8,                          // Bits per component
                                                   result.bytesPerLine(),              // Bytes per row
                                                   colorSpace,                 // Colorspace
                                                   kCGImageAlphaNoneSkipFirst |
                                                   kCGBitmapByteOrder32Little); // Bitmap info flags

    CGContextDrawImage(contextRef, CGRectMake(0, 0, width, height), image.CGImage);
    CGContextRelease(contextRef);

    if (degree != 0) {
        QTransform myTransform;
        myTransform.rotate(degree);
        result = result.transformed(myTransform,Qt::SmoothTransformation);
    }

    return result;
}

static QString fromNSUrl(NSURL* url) {
    QString result = QString::fromNSString([url absoluteString]);

    return result;
}

static UIImagePickerController* imagePickerController = nullptr;
static UIActivityIndicatorView* imagePickerControllerActivityIndicator = nullptr;

static bool imagePickerControllerPresent(QVariantMap& data) {
    UIWindow *rootWindow = [[UIApplication sharedApplication] keyWindow];
    UIViewController* rootViewController = rootWindow.rootViewController;

    int sourceType = data["sourceType"].toInt();
    bool animated = data["animated"].toBool();

    if (![UIImagePickerController isSourceTypeAvailable:(UIImagePickerControllerSourceType) sourceType]) {
        UIAlertView *myAlertView = [[UIAlertView alloc] initWithTitle:@"Error"
                          message:@"The operation is not supported in this device"
                          delegate:nil
                          cancelButtonTitle:@"OK"
                          otherButtonTitles: nil];
        [myAlertView show];
//        [myAlertView release];
        return false;
    }

    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    imagePickerController = picker;
    picker.sourceType = (UIImagePickerControllerSourceType) sourceType;

    static QIViewDelegate *delegate = nullptr;
    delegate = [QIViewDelegate alloc];

    delegate->imagePickerControllerDidFinishPickingMediaWithInfo = ^(UIImagePickerController *picker,
                                                                     NSDictionary* info) {
        Q_UNUSED(picker);

        QString name = "imagePickerControllerDisFinishPickingMetaWithInfo";
        QVariantMap data;

        data["mediaType"] = QString::fromNSString(info[UIImagePickerControllerMediaType]);
        data["mediaUrl"] = fromNSUrl(info[UIImagePickerControllerMediaURL]);
        data["referenceUrl"] = fromNSUrl(info[UIImagePickerControllerPHAsset]);

        UIImage *chosenImage = info[UIImagePickerControllerEditedImage];
        if (!chosenImage) {
            chosenImage = info[UIImagePickerControllerOriginalImage];
        }

        if (!chosenImage) {
            qWarning() << "Image Picker: Failed to take image";
            name = "imagePickerControllerDidCancel";
        } else {
            QImage chosenQImage = fromUIImage(chosenImage);
            data["image"] = QVariant::fromValue<QImage>(chosenQImage);
        }

        QISystemDispatcher* m_instance = QISystemDispatcher::instance();

        QMetaObject::invokeMethod(m_instance,"dispatched",Qt::DirectConnection,
                                  Q_ARG(QString , name),
                                  Q_ARG(QVariantMap,data));

        delegate = nil;
    };

    delegate->imagePickerControllerDidCancel = ^(UIImagePickerController *picker) {
        Q_UNUSED(picker);

        QString name = "imagePickerControllerDidCancel";
        QVariantMap data;
        QISystemDispatcher* m_instance = QISystemDispatcher::instance();
        QMetaObject::invokeMethod(m_instance,"dispatched",Qt::DirectConnection,
                                  Q_ARG(QString , name),
                                  Q_ARG(QVariantMap,data));

        delegate = nil;
    };

    picker.delegate = delegate;

    imagePickerControllerActivityIndicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    imagePickerControllerActivityIndicator.center = picker.view.center;
    [picker.view addSubview:imagePickerControllerActivityIndicator];

    [rootViewController presentViewController:picker animated:animated completion:nullptr];

    return true;
}

bool imagePickerControllerDismiss(QVariantMap& data) {
    Q_UNUSED(data);
    if (!imagePickerController)
        return false;

    bool animated = data["animated"].toBool();

    [imagePickerController dismissViewControllerAnimated:animated completion:nullptr];
//    [imagePickerController release];

//    [imagePickerControllerActivityIndicator release];

    imagePickerController = nullptr;
    imagePickerControllerActivityIndicator = nullptr;
    return true;
}

bool imagePickerControllerSetIndicator(QVariantMap& data) {
    if (!imagePickerControllerActivityIndicator)
        return false;

    bool active = data["active"].toBool();

    if (active) {
        [imagePickerControllerActivityIndicator startAnimating];
    } else {
        [imagePickerControllerActivityIndicator stopAnimating];
    }

    return true;
}

static bool applicationSetStatusBarStyle(QVariantMap& data) {
    if (!data.contains("style")) {
        qWarning() << "applicationSetStatusBarStyle: Missing argument";
        return false;
    }

    int style = data["style"].toInt();
    
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    QIOSViewController *viewController = static_cast<QIOSViewController *>([window rootViewController]);

    viewController.preferredStatusBarStyle = (UIStatusBarStyle) style;
    [viewController setNeedsStatusBarAppearanceUpdate];

    return true;
}

void QuickIOS::registerTypes() {
    static bool typesRegistered = false;
    if (typesRegistered)
        return;

    QISystemDispatcher* dispatcher = QISystemDispatcher::instance();

    dispatcher->addListener("applicationSetStatusBarStyle",applicationSetStatusBarStyle);

    dispatcher->addListener("imagePickerControllerPresent",imagePickerControllerPresent);
    dispatcher->addListener("imagePickerControllerDismiss",imagePickerControllerDismiss);
    dispatcher->addListener("imagePickerControllerSetIndicator",imagePickerControllerSetIndicator);

    typesRegistered = true;
}
