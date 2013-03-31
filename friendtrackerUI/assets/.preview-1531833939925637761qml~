/**
 * Pin container for the MapView
 */
import bb.cascades 1.0

Container {
    // File path of the pin image
    property string profileImageSource: "asset:///images/default.jpg"
    property string pinImageSource: "asset:///images/Map_pin4.png"
    // pointerOffsetX, pointerOffsetY is the position of the pixel in pin image that should point to the location. Change these to match your pin image.
    property int pointerOffsetX: 90
    property int pointerOffsetY: 184
    /////////////////////////////////////////////////////////
    id: root
    property int x: 0
    property int y: 0
    property double lat
    property double lon
    property alias animDrop: animDrop
    property alias profileImage: profileImage
    clipContentToBounds: false
    layout: AbsoluteLayout{}
    layoutProperties: AbsoluteLayoutProperties {
        id: position
        positionX: x - pointerOffsetX
        positionY: y - pointerOffsetY
    }
    ImageView {
        id: pinImage
        imageSource: pinImageSource
        layoutProperties: AbsoluteLayoutProperties {
            positionX: -18
            positionY: -8
        }
    }
    ImageView {
        id: profileImage
        //imageSource: profileImageSource
        focusPolicy: FocusPolicy.Touch
        overlapTouchPolicy: OverlapTouchPolicy.Allow
        onFocusedChanged: {
            if (focused) {
                root.parent.showBubble(root);
            }
        }
        attachedObjects: [
            ImageTracker {
                id: profileImageTracker
                imageSource: profileImageSource
                
                onImageChanged: {
                    profileImage.image = image;
                }
            }
        ]
    }
    animations: [
        TranslateTransition {
            id: animDrop
            fromY: - position.positionY
            toY: 0
            duration: 600
            easingCurve: StockCurve.BounceOut
        }
    ]
}

