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

function startSubscription(friends) {
    console.log("start subscription");
      var host = "198.58.106.27";
      var port = 8081;
      var socket = new WebSocket("ws://" + host + ":" + port + "/");
      socket.onopen = function() {
      var i, _i, _results;
      // first get locations and then subscribe for later
      for (i = _i = 1; _i <= friends.length; i = ++_i) {
          socket.send(JSON.stringify({
              "GET": friends[i]
            }));
      }
      _results = [];
      for (i = _i = 1; _i <= friends.length; i = ++_i) {
        _results.push(socket.send(JSON.stringify({
          "SUBSCRIBE": friends[i]
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

  /**
   * populate image list for the user's friends.
   */
  function addFriendItem(friend) {
    var item = null;

    // Create the item's DOM in a fragment
    item = document.createElement('div');
    item.setAttribute('data-bb-type','item');
    item.setAttribute('data-bb-title', friend);
    item.setAttribute('data-bb-image', 'http://friendtracker.org/client/pics/' + friend + '.png');
    item.innerHTML = 'nice day!';
    item.onclick = function() {alert('clicked');};    // TODO implement locating to user
                                                      // (needs to keep track of users locations)
    document.getElementById('received').appendItem(item);
  }
