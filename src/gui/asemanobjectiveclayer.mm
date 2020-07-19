#include "asemanobjectiveclayer.h"

#import <UIKit/UIKit.h>

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
