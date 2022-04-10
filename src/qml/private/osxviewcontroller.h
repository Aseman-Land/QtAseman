#ifndef MYVIEWCONTROLLER_H
#define MYVIEWCONTROLLER_H

#include <QtGlobal>

#ifdef Q_OS_IOS

#import <UIKit/UIKit.h>

@interface QIOSViewController : UIViewController
@end


@interface QIOSViewController (MyView)
@end

#endif
#endif // MYVIEWCONTROLLER_H
