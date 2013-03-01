function extend(subClass, superClass) {
	var F = function() {};
	F.prototype = superClass.prototype;
	subClass.prototype = new F();
	subClass.prototype.constructor = subClass;
}

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
		user: new User(json[1]),
	    location: {
	       	x: parseFloat(coordinates[0]),
	        y: parseFloat(coordinates[1])
	    }
	};
	return data;
};

User = (function() {

    function User(name) {
      	this.name = name;
      	this.color = '#' + Math.floor(Math.random() * 16777215).toString(16);
    }

    return User;

})();

function startSubscription() {
    console.log("start subscription");
      var host = "198.58.106.27";
      var port = 8081;
      var socket = new WebSocket("ws://" + host + ":" + port + "/");
      socket.onopen = function() {
      var i, _i, _results;
      // first get locations and then subscribe for later
      for (i = _i = 1; _i <= 6; i = ++_i) {
          socket.send(JSON.stringify({
              "GET": "testusr" + i
            }));
      }
      _results = [];
      for (i = _i = 1; _i <= 6; i = ++_i) {
        _results.push(socket.send(JSON.stringify({
          "SUBSCRIBE": "testusr" + i
        })));
      }
      return _results;
    };
    return socket.onmessage = function(message) {
      var data;
      data = decodeJSON(message);
      if (data && AbstractMap.getCurrentMap() != null) {
        return AbstractMap.getCurrentMap().plot(data.location, data.user);
      }
    };
  };
