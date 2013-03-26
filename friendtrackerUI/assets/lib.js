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
 * @param map
 * @returns {Function}
 */
function startSubscription(friends, map) {
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
    	var data = decodeJSON(message);
    	if (data) {
    		return map.plot(data);
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
		console.log("MSG: " + msg);
		websocket.send(msg);
	}
}