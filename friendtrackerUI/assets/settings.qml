import bb.cascades 1.0
import bb.cascades.pickers 1.0

Sheet {
    id: settingsSheet    
    content: TabbedPane {
        
        onCreationCompleted: {
            settingsSheet.open();
        }

        /* Note:
         * To push a NavigationPane Page from the ApplicationMenu, we will need
         * to keep track which NavigationPane to push it to (that is, which is the active NavigationPane)
         * Tab cannot be added to NavigationPane (but the other way around is possible)
         */
        property NavigationPane currentNavigationPane: profileTab.navHandle

        // Update the NavigationPane handle when the Tab is changed
        onActiveTabChanged: {
            console.log("TabbedPane : onActiveTabChanged : activeTab.description = " + activeTab.description);
            currentNavigationPane = activeTab.navHandle
        }

        attachedObjects: [
            FilePicker {
                id: filePicker
                type: FileType.Picture
                title: "Select Profile Picture"
                directories: [ "/accounts/1000/shared/camera" ]
                imageCropEnabled: true

                onFileSelected: {
                    _settings.updateProfilePicture(selectedFiles);
                }
            }
        ] // attachedObjects

        Tab {
            id: profileTab
            title: qsTr("Profile Settings")
            description: "Profile Settings"
            property alias navHandle: nav1
            NavigationPane {
                id: nav1
        
                onPopTransitionEnded: {
                    console.log("Tab1 : NavigationPane - onPopTransitionEnded");
                    Application.menuEnabled = true;
                }

                Page {
                    titleBar: TitleBar {
                        title: "Profile Settings"
                        dismissAction: ActionItem {
                            title: "Close"
                            onTriggered: {
                                // Emit the custom signal here to indicate that this page needs to be closed
                                // The signal would be handled by the page which invoked it
                                settingsSheet.close();
                            }
                        }
                    }
                    resizeBehavior: PageResizeBehavior.None
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
                    ] // actions

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
                            } // Container

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

                                    property int initialized: 0

                                    onCreationCompleted: {
                                        if (_settings.statusMessage == "Available") {
                                            selectedIndex = 0;
                                        } else if (_settings.statusMessage == "Busy") {
                                            selectedIndex = 1;
                                        } else {
                                            customStatusMessage.text = _settings.statusMessage;
                                            selectedIndex = 2;
                                        }
                                        _settings.statusMessageChangedFromBBM.connect(
                                            statusMessageDropDown.selectedValueChanged);
                                        initialized = 1;
                                    }

                                    function selectedValueChanged(val) {
                                        if (val == "available") {
                                            selectedIndex = 0;
                                        } else if (val == "busy") {
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
                            } // Container
                        } // mainContainer
                    } // ScrollView
                } // Page
            } // NavigationPane
        } // Tab

        Tab {
            id: serverSettings
            property alias navHandle: nav2
            title: qsTr("Server Settings")
            description: "Server Settings"

            NavigationPane {
                id: nav2

                onPopTransitionEnded: {
                    Application.menuEnabled = true;
                }

                Page {
                    id: tab2
                    titleBar: TitleBar {
                        title: "Server Settings"
                        dismissAction: ActionItem {
                            title: "Close"
                            onTriggered: {
                                // Emit the custom signal here to indicate that this page needs to be closed
                                // The signal would be handled by the page which invoked it
                                settingsSheet.close();
                            }
                        }
                    }
                    Container {
                        //background: Color.Black
                        layout: StackLayout {}
                        topPadding: 20
                        Container {
                            topPadding: 20
                            background: Color.White
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            // Define tab content here
                            Label {
                                text: "Visibility"
                                verticalAlignment: VerticalAlignment.Top
                            }
                            ToggleButton {
                                id: visibility
                                objectName: "visibility"
                                checked: _friendtracker.getValueFor(visibility.objectName, "true")
                                horizontalAlignment: HorizontalAlignment.Right
                                
                                onCheckedChanged: {
                                    _friendtracker.setVisibility(checked);
                                    _friendtracker.saveValueFor(visibility.objectName, visibility.checked);
                                }
                            }
                        }
                        Container {
                            topPadding: 40
                            background: Color.White
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            Label {
                                text: "Real-Time Mode"
                            }
                            ToggleButton {
                                id: mode
                                objectName: "mode"
                                checked: _friendtracker.getValueFor(mode.objectName, "true")
                                horizontalAlignment: HorizontalAlignment.Right
                                
                                onCheckedChanged: {
                                    if (!checked) {
                                        _friendtracker.setRegularMode(pullFrequency.value);
                                    } else {
                                        _friendtracker.setRealtimeMode();
                                    }
                                    _friendtracker.saveValueFor(mode.objectName, mode.checked);
                                }
                            }
                        }
                        Container {
                            topPadding: 40
                            layout: StackLayout{}
                            Label {
                                text: "Location Retrieval Frequency"
                            }
                            Slider {
                                id: pullFrequency
                                objectName: "pullFrequencySlider"
                                fromValue: 1
                                toValue: 300
                                value: _friendtracker.getValueFor(pullFrequency.objectName, "5")

                                onImmediateValueChanged: {
                                    var str = printPullFrequency(value);
                                    _friendtracker.saveValueFor(pullSliderValue.objectName, value);
                                    _friendtracker.saveValueFor(pullSliderValue.objectName, str);
                                    pullSliderValue.text = str;
                                }

                                onValueChanged: {
                                    var str = printPullFrequency(value);
                                    _friendtracker.saveValueFor(pullFrequency.objectName, value);
                                    _friendtracker.saveValueFor(pullSliderValue.objectName, str);
                                    pullSliderValue.text = str;
                                }

                                function printPullFrequency(value) {
                                    var str = "";
                                    if (value < 60.0) {
                                        str = Math.floor(value) + " seconds";
                                    } else {
                                        str = Math.floor(value / 60) + " minutes " + Math.floor(value % 60) + " seconds";
                                    }
                                    return str;
                                }
                            }
                            Label {
                                id: pullSliderValue
                                objectName: "pullSliderValueLabel"
                                text: _friendtracker.getValueFor(pullSliderValue.objectName, "5 seconds")
                                horizontalAlignment: HorizontalAlignment.Center
                            }
                        }
                        Container {
                            topPadding: 40
                            layout: StackLayout{}
                            
                            Label {
                                text: "Location Update Frequency"
                                //textStyle.color: Color.White
                            }                                                        
                            Slider {
                                id: updateFrequency
                                objectName: "updateFrequencySlider"
                                fromValue: 1
                                toValue: 300
                                value: _friendtracker.getValueFor(updateFrequency.objectName, "5")
                                
                                onImmediateValueChanged: {
                                    var str = printFrequency(value);
                                    _friendtracker.saveValueFor(updateFrequency.objectName, value);
                                    _friendtracker.saveValueFor(sliderValue.objectName, str);
                                    sliderValue.text = str;
                                }

                                onValueChanged: {
                                    var str = printFrequency(value);
                                    _friendtracker.saveValueFor(updateFrequency.objectName, value);
                                    _friendtracker.saveValueFor(sliderValue.objectName, str);
                                    sliderValue.text = str;
                                }
                                
                                function printFrequency(value) {
                                    if (value < 60.0) {
                                        return Math.floor(value) + " seconds";
                                    } else {
                                        return Math.floor(value / 60) + " minutes "
                                        	+ Math.floor(value % 60) + " seconds";
                                    }
                                }
                            }
                            Label {
                                id: sliderValue
                                objectName: "sliderValueLabel"
                                text: _friendtracker.getValueFor(sliderValue.objectName, "5 seconds")
                                horizontalAlignment: HorizontalAlignment.Center
                            }
                            Button {
                                text: "Update"
                                horizontalAlignment: HorizontalAlignment.Center
                                
                                onClicked: {
                                    // change update location interval
                                    _mapView.setGeoLocationInterval(updateFrequency.value);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}