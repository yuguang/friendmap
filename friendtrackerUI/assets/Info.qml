import bb.cascades 1.0
import bb.cascades.pickers 1.0

/**
 * Brief description of project
 * 
 * by Sukwon Oh
 */

Page {
    id: infoPage

    signal done()

    titleBar: TitleBar {
        title: "FriendTracker Info"
        dismissAction: ActionItem {
            title: "Close"
            onTriggered: {
                // Emit the custom signal here to indicate that this page needs to be closed
                // The signal would be handled by the page which invoked it
                infoPage.done();
            }
        }
    }
    Container {
        layout: StackLayout{}
        background: Color.Black
        
        Label {
            text: "Developed by Bill Chen, Sukwon Oh, Lu Zou, Yuguang Zhang"
            textStyle.color: Color.White
            multiline: true
        }
        
        Label {
            text: "A  mobile  application  that  tracks  the  real-time  location  of  the user’s  friends and  acquaintances.  This  enables  the  user  to  conveniently  schedule meetings  and  gatherings. This  app  also  eliminates  the  need  for  text  messages  and phone  calls  to  inquire  your  friend’s physical  location,  thus  reducing  the  amount  of hassle  and  network  bandwidth  for  social  interactions. In  addition,  the  app  can  be used  to  find  other  users  with  similar  interest  around  the user’s  area."
            textStyle.color: Color.White
            multiline: true
        }
    }
}
