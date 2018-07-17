# BackHandler

## What is it?

BackHandler is the component, you can use to handle back actions of the Applications.

## How to

BackHandler has two primary functions. back() and pushHandler()

### pushHandler(var obj, function(){code})

The ```pushHandler()``` function, push an special method to the BackHandler stack. Whenever obj destroyed or back() function called, our code will call by the BackHandler.

If the code, returns false or null, BackHandler remove the code from top of the stack. Else It keep the code for the next call.

You can also use pushDownHandler function to push a method to the bottom of the stack.

### removeHandler(var obj)

Remove handler remove an object and his code from the stack.

### back()

The ```back()``` function will call top code of the stack and remove it.

## Examples

## A Simple Back

```
Item {
    id: myItem
    
    Button {
        anchors.centerIn: parent
        text: "Back"
        onClicked: BackHandler.back()
    }
    
    Component.onCompleted: BackHandler.pushHandler(myItem, function(){
        myItem.destroy()
    })
}
```

## Get android Back signals

```
Rectangle {
    id: myRect
    
    Keys.onEscapePressed: if(View.backController) AsemanApp.back()

    Connections {
        target: View
        onCloseRequest: AsemanApp.back()
    }

    Connections {
        target: AsemanApp
        onBackRequest: {
            if(!View.backController)
                return
            var res = BackHandler.back()
            if( !res && !Devices.isDesktop ) // If there is no item in the stack, close the app
                View.tryClose()
        }
    }
    
    Component.onCompleted: View.backController = true
}
```

You can use AsemanMain component instead of this example.


