import bb.cascades 1.0
import bb.cascades.pickers 1.0

Page {
    titleBar: TitleBar {
        title: "Settings"
    }
    
    resizeBehavior: PageResizeBehavior.None

    attachedObjects: [
        FilePicker {
            id: filePicker
            type: FileType.Picture
            title: "Select Profile Picture"
            directories: ["/accounts/1000/shared/camera"]
            imageCropEnabled: true

            onFileSelected: {
                _settings.updateProfilePicture(selectedFiles);
            }
        }
    ]

    actions: [
        ActionItem {
            title: "Take Picture"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _settings.openCamera()
            }
        },
        ActionItem {
            title: "Pick Picture"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                filePicker.open()
            }
        }
    ]

    ScrollView {
        scrollViewProperties {
            scrollMode: ScrollMode.Vertical
        }

        Container {
            id: mainContainer
            layout: StackLayout {
            }

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

                Container {
                    layout: StackLayout {
                    }
                    Label {
                        id: displayName
                        text: _settings.displayName
                        textStyle.color: Color.White
                        textStyle.fontSize: FontSize.Medium
                        textStyle.fontWeight: FontWeight.Bold
                    }
                }
                
                ImageView {
                    id: profilePicture
                    image: _settings.profilePicture
                    preferredHeight: 300
                    preferredWidth: 300
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
                    
                    property int initialized: 0;

                    onCreationCompleted: {
                        if (_settings.statusMessage == "Available") {
                            selectedIndex = 0;
                        } else if (_settings.statusMessage == "Busy") {
                            selectedIndex = 1;
                        } else {
                            customStatusMessage.text = _settings.statusMessage;
                            selectedIndex = 2;
                        }
                        _settings.statusMessageChangedFromBBM
                        	.connect(statusMessageDropDown.selectedValueChanged);
                        initialized = 1;
                    }

                    function selectedValueChanged(val) {
                        if (val == "Available") {
                            selectedIndex = 0;
                        } else if (val == "Busy") {
                            selectedIndex = 1;
                        } else {
                            customStatusMessage.text = val;
                            selectedIndex = 2;
                        }
                    }
                    
                    onSelectedOptionChanged: {
                        if (initialized == 1) {
                        	// signals BBM about the changes made
                    	   	_settings.statusMessage = selectedOption.value;
                    	}
                    }                    

                    Option {
                        text: "Available"
                        value: "Available"
                    }
                    Option {
                        text: "Busy"
                        value: "Busy"
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
                Button {
                    text: "Update"
                    horizontalAlignment: HorizontalAlignment.Right

                    onClicked: {
                        _settings.personalMessage = personalMessage.text;
                    }
                }
                // placeholder so that keyboard won't hide PersonalMessage textarea
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
                Label {
                    text: ""
                }
            }
        }        
    }
}