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

/**
 *  called by the webworksready event when the environment is ready
 */
 
var initial = true;
var mapProvider = 'bing';   // initial map provider is google
var ppId = null;
var friends = [];
var onlinefriends = [];

function initApp() {
    APIKey = {
        'bing': 'Ap76EAymF6IBSmNmnfSqNgoP8BIAD9T0m9cdXiIqlc95OkOOFnjuUwlKkat8I-Ou'
    };

    console.log('app initialized');

    // Get my ppId
    ppId = 'testusr1';                                  // TODO: grab from bbm contact
    friends = ["testusr2", "testusr3", "testusr4"];     // TODO: get friends from bbm
    startGeolocation();                                 // login done after getting user's location
                                                        // also subscription is started on successful login
}

/**
 * Login to friendtrack server
 * @returns list of online friends
 */
function login(ppId, friends) {
    $.ajax({
        type: 'POST',
        url: "http://friendtracker.org:9000/login",
        data: JSON.stringify({
            "ppId": ppId,
            "x": myLat,
            "y": myLong,
            "friends": friends}
        ),
        dataType: 'json',
        contentType: 'application/json',
        success: function(reply) {
            // parse response and return online friends
            var status = reply.status;
            var sessionKey = reply.sessionKey;
            onlinefriends = reply.friends;
            startSubscription(onlinefriends);
        },
        error: function(xhr, status, msg) {
            console.log("ajax error - " + status + " " + msg);
        }
    });
}

function getCurrentMap() {
    return g_map;
}

var markersGoogle, markersBing, infosGoogle, infosBing;
var myLat, myLong;

markersBing = {};
markersGoogle = {};
infosBing = {};
infosGoogle = {};
  
/**
 *  google maps
 */

// initialize the map
function initGoogleMaps() {
    console.log("Init google maps @" + myLat + "," + myLong);
    g_map = new GoogleMap();
    g_map.init({
        zoom: 14,
        center: new google.maps.LatLng(myLat, myLong),
        mapTypeId: google.maps.MapTypeId.ROADMAP
    }); 
    mapProvider = 'google';  
}

// search for nearby places
function initGooglePlaces() {
    searchForPlaces(googlePlacesCallback);
}

// search callback
function googlePlacesCallback(results) {
    for(var i = 0; i < results.length; i++) {
        createGoogleMarker(results[i]);
    }
}

// create a marker / push-pin
function createGoogleMarker(place) {
    var placeLoc = place.geometry.location;
    var marker = new google.maps.Marker({
        map: googleMap,
        position: place.geometry.location
    });
}

/**
 *  bing
 */

function initBingMaps() {
    console.log("InitBingMaps @" + myLat + "," + myLong);
    g_map = new BingMap();
    g_map.init({
        credentials: APIKey.bing,
        center: new Microsoft.Maps.Location(myLat, myLong),
        zoom: 14,
        mapTypeId: Microsoft.Maps.MapTypeId.road,
        showCopyright: false
    });    
    mapProvider = 'bing';
}

// search for nearby places
function initBingPlaces() {
    Microsoft.Maps.loadModule('Microsoft.Maps.Search', {
        callback: bingSearch
    });
}

// seraching bing, using a query
function bingSearch() {
    bingMap.addComponent('searchManager', new Microsoft.Maps.Search.SearchManager(bingMap));
    searchManager = bingMap.getComponent('searchManager');

    var query = 'bars in Waterloo, Canada';
    var request = {
        query: query,
        count: 15,
        startIndex: 0,
        bounds: bingMap.getBounds(),
        callback: bingPlacesCallback
    };
    searchManager.search(request);
}

// search callback
function bingPlacesCallback(result) {
    var searchResults = result && result.searchResults;
    if(searchResults) {
        for(var i = 0; i < searchResults.length; i++) {
            createBingMarker(searchResults[i]);
        }
    }
}

// create marker / push-pin
function createBingMarker(result) {
    if(result) {
        var pin = new Microsoft.Maps.Pushpin(result.location, null);
        bingMap.entities.push(pin);
    }
}

/**
 *  search for POI
 */

// example of seraching for places using google
function searchForPlaces(callback) {
    var request = {
        location: myLocation,
        radius: 2000,
        types: ['bar']
    };

    infowindow = new google.maps.InfoWindow();
    var service = new google.maps.places.PlacesService(googleMap);
    service.search(request, callback);
    return;
}



/**
 *  geolocation
 */

// we use HTML5 Geolocation to pin-point where the user is
function startGeolocation() {
    var options = {
        enableHighAccuracy: false   // do not receive best possible result (i.e. use GPS)
    };
    // continusouly watch user's location and update on the map
    navigator.geolocation.watchPosition(geoSuccess, geoFail, options);
}

// geolocation success callback
function geoSuccess(position) {
    var gpsPosition = position;
    var coordinates = gpsPosition.coords;
    myLat = coordinates.latitude;
    myLong = coordinates.longitude;
    if (g_map !== null) {
        g_map.plotSelf();    
    }
    console.log('geoSuccess pushing screen');
    // only run once during initialization
    if (initial) {
        onlinefriends = login(ppId, friends);
        bb.pushScreen('google.html', mapProvider);
        initial = false;
    }  
}

// geolocation failure callback
function geoFail() {
    var msg = 'Using default position (Waterloo, ON, Canada) instead';
    switch(error.code) {
        case PositionError.PERMISSION_DENIED:
            alert('Error. PERMISSION_DENIED. ' + msg);
            break;
        case PositionError.POSITION_UNAVAILABLE:
            alert('Error. POSITION_UNAVAILABLE. ' + msg);
            break;
        case PositionError.TIMEOUT:
            alert('Error. TIMEOUT. ' + msg);
            break;
        default:
            alert('Error. Unknown error code');
    }
    alert('Error getting your position. Using defaults instead');
    // set default position upon failure
    myLat = 43.465187;
    myLong = -80.522372;
    if (g_map !== null) {
        g_map.plotSelf();  
    }
    bb.pushScreen('google.html', mapProvider);
}