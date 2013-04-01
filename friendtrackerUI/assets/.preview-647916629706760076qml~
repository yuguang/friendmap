import bb.cascades 1.0
import bb.cascades.pickers 1.0

Page {
    titleBar: TitleBar {
        title: "Settings"
    }

    actions: [
        ActionItem {
            title: "Profile Picture"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _settings.openCamera()
            }
        }
    ]
    Container {
        id: mainContainer
        layout: StackLayout {}

        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill

        topPadding: 20
        leftPadding: 20
        rightPadding: 20

        background: Color.Black

        Label {
            text: "Profile Settings"
            textStyle.color: Color.White
            textStyle.fontWeight: FontWeight.Bold
        }

        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }

            ImageView {
                id: profilePicture
                image: _settings.profilePicture
                preferredHeight: 300
                preferredWidth: 300
            }

            Container {
                layout: StackLayout {
                }
                Label {
                    text: "Display Name"
                    textStyle.color: Color.White
                }
                TextArea {
                    id: displayName
                    text: _settings.displayName
                    textStyle.fontSize: FontSize.Medium
                    textStyle.fontWeight: FontWeight.Bold
                }
            }
        }

        Divider {
        }

        Container {
            layout: StackLayout {
                //    orientation: LayoutOrientation.LeftToRight
            }

            Label {
                text: "Status Message"
                textStyle.color: Color.White
            }

            DropDown {
                id: statusMessageDropDown
                title: "Status Message"
                enabled: true

                onCreationCompleted: {
                    _settings.statusMessageChanged.connect(statusMessageDropDown.onSelectedValueChanged);
                    if (_settings.statusMessage == "Available") {
                        selectedIndex = 0;
                    } else if (_settings.statusMessage == "Busy") {
                        selectedIndex = 1;
                    } else {
                        customStatusMessage.text = _settings.statusMessage;
                        selectedIndex = 2;
                    }
                }

                function onSelectedValueChanged(val) {
                    if (val == "Available") {
                        selectedIndex = 0;
                    } else if (val == "Busy") {
                        selectedIndex = 1;
                    } else {
                        customStatusMessage.text = val;
                        selectedIndex = 2;
                    }
                }

                Option {
                    text: "Available"
                    value: "available"
                }
                Option {
                    text: "Busy"
                    value: "busy"
                }
                Option {
                    id: customStatusMessage
                    text: "Edit Status Message"
                }
            }

            Label {
                text: "Personal Message"
                textStyle.color: Color.White

            }
            TextArea {
                id: personalMessage
                text: _settings.personalMessage
                horizontalAlignment: HorizontalAlignment.Fill
            }
        }
    }
}