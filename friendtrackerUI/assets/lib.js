/**
 * Utility class
 * 
 * by Sukwon Oh, Yuguang Zhang
 */

/**
 * handles decoding subscription and get replies
 */
decodeJSON = function(j) {
	var coordinates, data, json;
	json = JSON.parse(j.data)["SUBSCRIBE"];
	if (!json || !(json[0] === "message")) {
		json = JSON.parse(j.data)["GET"];
        if (!json || !(json[0] == "message")) {
            return false;
        }
	}
	coordinates = json[2].split(',');
	data = {
			user: json[1],
			location: {
				x: parseFloat(coordinates[0]),
				y: parseFloat(coordinates[1])
			}
	};
	return data;
};

/**
 * subscribe to real-time location updates for list of users
 * @param friends
 * @param navigator
 * @returns {Function}
 */
function startSubscription(friends, websocketView) {
	console.log("start subscription");
	var host = "198.58.106.27";
    var port = 8081;
    var socket = new WebSocket("ws://" + host + ":" + port + "/");
    socket.onopen = function() {
    	var i, _i, _results;
    	// first get locations and then subscribe for later
    	for (i = _i = 0; _i < friends.length; i = ++_i) {
    		socket.send(JSON.stringify({
    			"GET": friends[i]
            }));
    	}
    	_results = [];
    	for (i = _i = 0; _i < friends.length; i = ++_i) {
    		_results.push(socket.send(JSON.stringify({
    			"SUBSCRIBE": friends[i]
    		})));
    	}
    	return _results;
    };
    socket.onmessage = function(message) {
    	//console.log(message.data);
    	if (message == null) {
    		console.log("data NULL!");
    	}
    	var data = decodeJSON(message);
    	if (data) {
    		//console.log(socket + " user: " + data.user + " x:" + data.location.x + " y:" + data.location.y);
    		return websocketView.updateUserLocation(data.user, data.location.x, data.location.y);    		
    	}
    };
    
    return socket;
};

/**
 * sends unsubscribe messages to all subscriptions
 */
function endSubscription(friends, websocket) {
	console.log("end subscription");
	for (var i = 0; i < friends.length; i++) {
		var msg = JSON.stringify({"UNSUBSCRIBE": friends[i]});
		websocket.send(msg);
	}
}