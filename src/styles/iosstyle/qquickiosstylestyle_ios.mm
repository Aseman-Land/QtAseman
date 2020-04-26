#import <UIKit/UIKit.h>
#import "qquickiosstylestyle_ios.h"

bool appearanceIsDark() {
    if (@available(iOS 13.0, *)) {
        UITraitCollection *traitCollection = [UITraitCollection currentTraitCollection];
        bool isDark = (traitCollection.userInterfaceStyle == UIUserInterfaceStyle::UIUserInterfaceStyleDark);
        return isDark;
    }
    return false;
}
