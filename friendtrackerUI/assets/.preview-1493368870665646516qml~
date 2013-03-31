/*
 * Main Window for the Friendtracker App
 * 
 * by Sukwon Oh
 */
import bb.cascades 1.0
import bb.system 1.0
import bb.cascades.maps 1.0

NavigationPane {
    id: navigationPane    
    objectName: "navigationPane"
    Menu.definition: MenuDefinition {
        // help action
        actions: [
            ActionItem {
            	title: "Info"
            	imageSource: "images/ic_info.png"
            	onTriggered: {
                	infoSheet.open();
                }
            }
        ]

        // settings action
        settingsAction: SettingsActionItem {
        	onTriggered: {
        	    // this is only effective on first call, multiple calls are ignored internally
        	    // load the user's profile setting
        	    _settings.initUserProfileFromBBM();
        	    // load settings page
                navigationPane.push(settingsPage.createObject());
            }
    	}
    }
    
    onPopTransitionEnded: {
    	page.destroy();        
    }
    
    Page {
        actions: [
            ActionItem {
                title: "Center Me"
                imageSource: "asset:///images/pin.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    mapview.latitude = _mapView.myLat;
                    mapview.longitude = _mapView.myLon;
                }
            },
            ActionItem {
                title: "Friends"
                imageSource: "asset:///images/friends.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    console.log("showing friends javascript");
                    navigationPane.push(friendListPage.createObject());
                }
            }
        ]        
        Container {
            id: map
            layout: DockLayout {
            }
            
            //! [0]
            property variant center: [ "-1", "-1" ]
            property variant centerPixel: [ "-1", "-1" ]
            //! [0]
            
            /*
             * Insert a friend into a friends list in websocket.js
             */
            function addOnlineFriend(friend) {
                var script = "addOnlineFriend(\"" + friend + "\")";
                websocketView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            
            /*
             * Send subscription request to the redis
             */
            function subscribe() {
                var script = "subscribe()";
                websocketView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }
            
            /*
             * Unsubscribe to all user's friends
             */
            function unsubscribe() {
                var script = "unsubscribe()"
                websocketView.evaluateJavaScript(script, JavaScriptWorld.Normal);
            }

            MapView {
                id: mapview
                altitude: 3000
                latitude: _mapView.myLat
                longitude: _mapView.myLon
                preferredWidth: 768
                preferredHeight: 1280                  
                
                onCreationCompleted: {
                    // Put a pin for the user on map after the mapView is initialized
                    pinContainer.addMe(_mapView.myLat, _mapView.myLon);
                }
                
                onAltitudeChanged: {
                }
                onHeadingChanged: {
                }
                onLatitudeChanged: {
                }
                onLongitudeChanged: {
                }
                onTiltChanged: {
                }
                onMapLongPressed: {
                }
                onRequestRender: {
                    pinContainer.updateMarkers();
                }
            }
            
            Container {
                id: pinContainer
                // Must match the mapview width and height and position
                preferredHeight: 1280
                preferredWidth: 768
                //touchPropagationMode: TouchPropagationMode.PassThrough
                overlapTouchPolicy: OverlapTouchPolicy.Allow
                property variant currentBubble: null
                property variant me
                property variant locations: {}
                layout: AbsoluteLayout {
                }
                
                /*
                 * Connect the pinContainer to update the user's profile picture when it is changed from BBM
                 * Connect the pinContainer to update the friend's profile picture when it is changed from BBM
                 */
                onCreationCompleted: {
                    _friendtracker.updateProfilePictureOnMap.connect(pinContainer.updateProfilePicture);
                    _friendtracker.updateFriendProfilePictureOnMap.connect(pinContainer.updateFriendProfilePicture);
                    _friendtracker.showPin.connect(pinContainer.showPin);
                    _friendtracker.hidePin.connect(pinContainer.hidePin);
                }
                
                /*
                 * show pin
                 */
                function showPin(ppId) {
                    var marker = _mapView.getPin(ppId);
                    if (marker != null) {
                        
                    }
                }
                
                function hidePin(ppId) {
                    
                }
                
                /*
                 * Method for adding myself on the map
                 */
                function addMe(lat, lon) {
                    var marker = pin.createObject();
                    marker.lat = lat;
                    marker.lon = lon;
                    // update the user's profile picture on map
                    var image = _friendtracker.getProfilePicture();
                    marker.profileImage.image = image;
                    var xy = _mapView.worldToPixelInvokable(mapview, marker.lat, marker.lon);
                    marker.x = xy[0];
                    marker.y = xy[1];
                    pinContainer.add(marker);
                    me = marker;
                    
                    marker.animDrop.play();                                    
                }
                
                /*
                 * Method for adding a marker for general user(i.e. friends)
                 */
                function addPin(ppId, lat, lon) {
                    var marker = _mapView.getPin(ppId);
                    var isNew = (marker == null);
                    if (isNew) {
                        marker = pin.createObject();
                    }
                    marker.lat = lat;
                    marker.lon = lon;                    
                    // asynchronously update the friend's profile picture on map
                    _friendtracker.askFriendProfilePicture(ppId);
                    var xy = _mapView.worldToPixelInvokable(mapview, marker.lat, marker.lon);
                    marker.x = xy[0];
                    marker.y = xy[1];
                    if (isNew) {
                        pinContainer.add(marker);
                        //marker.animDrop.play();
                    }                    
                    _mapView.addPin(ppId, marker);                    
                }
                
                /*
                 * Show bubble with the person's current address
                 */
                function showBubble(pin) {
                    if (currentBubble != null) {
                        pinContainer.remove(currentBubble);
                    }
                    
                    var details = bubble.createObject();
                    details.lat = pin.lat;	// this is not real error
                    details.lon = pin.lon;	// this is not real error
                    var xy = _mapView.worldToPixelInvokable(mapview, details.lat, details.lon);
                    details.x = xy[0];
                    details.y = xy[1];
                    // asynchronously get the person's address given location and write it on bubble
                    _friendtracker.getAddress(details, pin.lat, pin.lon);
                    pinContainer.add(details);
                    details.play();
                    currentBubble = details;
                }
                
                /*
                 * Not used now
                 */
                function showMe() {
                    var marker = pin.createObject();
                    marker.profileImageSource = "asset:///profile.jpg"
                    marker.pointerOffsetX = 30
                    marker.pointerOffsetY = 30
                    pinContainer.insert(-1, marker);
                    marker.visible = false;
                    me = marker;
                }
                
                /*
                 * Update the user's profile picture
                 */
                function updateProfilePicture(image) {
                    var marker = pinContainer.at(0);
                    if (marker == null) {
                        console.log("MARKER NULL!!!");
                    }
                    marker.profileImage.image = image;                    
                }
                
                /*
                 * Find a pin for the user with ppId and update its profile image
                 */
                function updateFriendProfilePicture(ppId, image) {
                    var marker = _mapView.getPin(ppId);
                    if (marker != null) {
                        marker.profileImage.image = image;
                    }                    
                }
                
                /*
                 * Update every marker present
                 */
                function updateMarkers() {
                    _mapView.updateMarkers(mapview, pinContainer);
                }
                
                /*
                 * Remove bubble if it exists
                 */
                function removeBubble() {
                    if (currentBubble != null) {
                        pinContainer.remove(currentBubble);
                    }                    
                }
                
                /*
                 * Remove bubble when the user touchs on screen outside of bubble
                 */
                onTouch: {
                    if (event.isDown()) {
                    	if (currentBubble == null) return;                        
                        if ((event.localX <= currentBubble.actualX) || (event.localX >= currentBubble.actualX + currentBubble.contentWidth) || (event.localY <= currentBubble.actualY) || (event.localY >= currentBubble.actualY + currentBubble.contentHeight)) {
                            removeBubble();
                        }
                    }
                }
            }
            attachedObjects: [
                //! [5]
                ComponentDefinition {
                    id: pin
                    source: "pin.qml"
                },
                ComponentDefinition {
                    id: bubble
                    source: "bubble.qml"
                }
            ]
            
            /*
             * This webview is purely for creating websocket connection on cascades
             */
            WebView {
                id: websocketView
                html: _webSocketView.pageContent
                visible: false
                
                // connect to subscribe/unsubscribe signals from WebMaps
                onCreationCompleted: {                    
                    _mapView.subscribe.connect(map.subscribe);
                    _mapView.unsubscribe.connect(map.unsubscribe);
                }

				/*
				 * When the webview loads completely, add the user's friends to websocket.js' friends list
				 * and subscribe to all of them.
				 */
                onLoadingChanged: {
                    if (loadRequest.status == WebLoadStatus.Succeeded) {
                        for (var i = 0; i < _friendtracker.onlinePpIds.length; i ++) {
                            map.addOnlineFriend(_friendtracker.onlinePpIds[i]);
                        }
                        map.subscribe();
                    }
                }

				/*
				 * When location update arrives, update the pin for that user
				 */
                onMessageReceived: {
                    if (message.data.indexOf("UserLocation") >= 0) {
                        var data = message.data.substring(message.data.indexOf(":") + 1);
                        var values = data.split(",");
                        var ppId = values[0].substr(1);
                        //console.log("ppId: " + ppId + "@" + values[1] + "," + values[2]);
                        pinContainer.addPin(ppId, values[1], values[2]);
                    }
                }
            }
        }       
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("NavigationPane - onCreationCompleted()");

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
    attachedObjects: [
        ComponentDefinition {
            id: settingsPage
            source: "settings.qml"
        },
        Sheet {
            id: infoSheet
            Info {
            	id: infoPage
                onDone: {
                    infoSheet.close();
                }
            }
        },
        ComponentDefinition {
            id: friendListPage
            source: "friendlist.qml"
        }
    ]
}
