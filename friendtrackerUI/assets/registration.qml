/**
 * BBM registration page
 * 
 * by Sukwon Oh, Bill Chen
 */
import bb.cascades 1.0

NavigationPane {
    id: navigationPane
    
    Page {
        id: page
        
        Container {
            onCreationCompleted: {
                navigationPane.push(page);
                _registrationHandler.registerApplication();
            }
    
            layout: DockLayout {}
    
            ImageView {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
    
                imageSource: "asset:///images/background.png"
            }
    
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
    
    			/*
                Label {
                    horizontalAlignment: HorizontalAlignment.Center
                    text: _registrationHandler.statusMessage
                    textStyle {
                        base: SystemDefaults.TextStyles.BodyText
                        color: Color.White
                    }
                    multiline: true
                }
                */
    			
                Button {
                    horizontalAlignment: HorizontalAlignment.Center
    
                    visible: _registrationHandler.temporaryError
                    text: qsTr("Connect to BBM")
                    onClicked: {
                        _registrationHandler.registerApplication()
                    }
                }
                // Display the main page if the user chooses to Continue
                /*
                Button {
                    horizontalAlignment: HorizontalAlignment.Center
                    visible: _registrationHandler.allowed
                    text: qsTr("Continue")
                    onClicked: {
                        _registrationHandler.finishRegistration()
                    }
                }
                */
            }
        }         
    }
}
