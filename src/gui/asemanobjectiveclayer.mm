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
