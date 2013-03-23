/*
 * Copyright 2010-2011 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// initialize the map
var googleMap;
var bingMap;
var markersArray = [];

// pushpin for the user
var mypin;
var friendsPins = {};

function initMaps(lat, lng) {
    console.log("init BingMaps");
    var myLat = lat;
    var myLong = lng;
    console.log("lat:" + lat + " lng:" + lng);


    bingMap = new Microsoft.Maps.Map(document.getElementById("map_canvas"), {
        credentials : 'Aq19BSd2VjCXz6tNKIolUJs-jyrrWdSHSealOdlKq7jb18l1OSZWzPk3ae2qA5ac',
        center : new Microsoft.Maps.Location(myLat, myLong),
        zoom : 14,
        mapTypeId : Microsoft.Maps.MapTypeId.auto,
        enableClickableLogo: false,
        enableSearchLogo: false,
        showDashboard: false,
        showMapTypeSelector: false,
        showScalebar: false,
        showCopyright : false
    });

    Microsoft.Maps.Events.addHandler(bingMap, 'viewchange', centerChanged);
    Microsoft.Maps.Events.addHandler(bingMap, 'click', clicked);
    
    // put pushpin for the user
    var iconpath = "local:///assets/images/pin.png";
    mypin = new Microsoft.Maps.Pushpin(new Microsoft.Maps.Location(myLat, myLong),{
    	icon:iconpath, height:60, width:60, anchor:new Microsoft.Maps.Point(20,58), draggable: false});
    bingMap.entities.push(mypin);
    Microsoft.Maps.Events.addHandler(mypin, 'click', markerClicked);
    
    var friends = ["testusr1", "testusr2", "testusr3", "testusr4", "testusr5", "testusr6"];
    startSubscription(friends, this);
    
    console.log("Done init BingMaps");
}

userImages = {"testusr1": "http://placekitten.com/20/20", "testusr2": "http://placekitten.com/20/20", "testusr3": "http://placekitten.com/20/20", "testusr4": "http://placekitten.com/20/20", "testusr5": "http://placekitten.com/20/20", "testusr6": "http://placekitten.com/20/20"}

function plot(data) {
	if (data.user in friendsPins) {
		updatePushPin(data.location.x, data.location.y, data.user, userImages[data.user]);
	} else {
    // username console.log(data.user)
		createPushPin(data.location.x, data.location.y, data.user, userImages[data.user]);	
	}
}

function clicked(e) {
    var location = bingMap.tryPixelToLocation(new Microsoft.Maps.Point(e.getX(), e.getY()), Microsoft.Maps.PixelReference.page);
    //navigator.cascades.postMessage("clicked:" + location.latitude + "," + location.longitude + "," + e.pageX + "," + e.pageY);
}

function centerChanged() {
    var point = bingMap.tryLocationToPixel(bingMap.getCenter(), Microsoft.Maps.PixelReference.page);
    //navigator.cascades.postMessage("centerChanged:" + bingMap.getCenter().latitude + "," + bingMap.getCenter().longitude + "," + point.x + "," + point.y);

}

function onMessage(message) {

}

function setZoom(zoomLevel) {
    var options = bingMap.getOptions();
    options.zoom = zoomLevel;
    bingMap.setView(options);
}

function zoomIn() {
    setZoom(bingMap.getZoom() + 1);
}

function zoomOut() {
    setZoom(bingMap.getZoom() - 1);
}

function setCenter(lat, lon) {
    bingMap.setView({center:new Microsoft.Maps.Location(lat, lon)});
}

function setMapTypeId(mapType) {
    var options = bingMap.getOptions();
    options.mapTypeId = mapType;
    bingMap.setView(options);
}

// create a marker / push-pin
function createPushPin(lat, lon, title, iconpath) {
    var pin = new Microsoft.Maps.Pushpin(new Microsoft.Maps.Location(lat, lon), {text: title, textOffset: new Microsoft.Maps.Point(0, 20), width: 45, typeName: 'blackText', icon:iconpath, height:60, width:60, anchor:new Microsoft.Maps.Point(20,58), draggable: true});
    bingMap.entities.push(pin);
    Microsoft.Maps.Events.addHandler(pin, 'click', markerClicked);
    markersArray.push(pin);
    friendsPins[title] = pin;
    
    //Remove: set center on user
    setCenter(lat, lon);
}

function updatePushPin(lat, lon, title) {
	var pin = friendsPins[title];
	pin.setLocation(new Microsoft.Maps.Location(lat, lon));
}

function removeAllPins() {
    if (markersArray) {
        for (i in markersArray) {
            bingMap.entities.remove(markersArray[i])
        }
    }
}

function markerClicked(e) {
    var pinLoc = e.target.getLocation();
    var point = bingMap.tryLocationToPixel(pinLoc, Microsoft.Maps.PixelReference.page);
    navigator.cascades.postMessage("markerClicked:" + pinLoc.latitude + "," + pinLoc.longitude + "," + point.x + "," + point.y);
}
