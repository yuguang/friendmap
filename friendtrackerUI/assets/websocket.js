/**
 * Initiates a websocket connection to the location server
 * to receive real-time location updates for the user's friends.
 * 
 * by Sukwon Oh
 */

var friends = [];
var websocket = null;
var bingMap;

function initWebSocketConnection() {
	console.log("init websocket connection");
	
	// this is a pure hack to make websocket live as long as the map is up
    console.log("init BingMaps");
    var myLat = 43.4575;
    var myLong = -80.5405;
    console.log("lat:" + myLat + " lng:" + myLong);


    bingMap = new Microsoft.Maps.Map(document.getElementById("websocket_canvas"), {
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
    
    if (bingMap != null) {
    	console.log("Done init BingMaps");	
    }
}

/*
 * populates friend to friends list
 */
function addOnlineFriend(friend) {
	friends.push(friend);
}

/*
 * start subscription
 */
function subscribe() {
	websocket = startSubscription(friends, this);
}

/*
 * unsubscribe to all friends in friends list
 */
function unsubscribe() {
	endSubscription(friends, websocket);
}

function onMessage(message) {

}

/*
 * let MapView know that there's location update
 */
function updateUserLocation(ppId, x, y) {
	navigator.cascades.postMessage("UserLocation: " + ppId + "," + x + "," + y);
}