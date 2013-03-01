var GoogleMap = function(){};
extend(GoogleMap, AbstractMap);
GoogleMap.prototype = {
	init: function(options) {
		this.googleMap = new google.maps.Map(document.getElementById("map_canvas"), options);
        markersGoogle = {};
        infosGoogle = {};
	},
	plot: function(location, user) {
		var latLng = new google.maps.LatLng(location.x, location.y);
		if (user.name in markersGoogle) {
			infosGoogle[user.name].setPosition(latLng);
			return markersGoogle[user.name].setPosition(latLng);
		} else {
			// create infobox with user profile
    		var info = new google.maps.InfoWindow({
    			content: user.name + '<br/><img border="0" align="left" src="http://friendtracker.org/client/pics/'
    				+ user.name + '.png"/>'
    		});
    		infosGoogle[user.name] = info;

            // create marker for a user
            markersGoogle[user.name] = new StyledMarker({
                styleIcon: new StyledIcon(StyledIconTypes.MARKER, {
                    color: user.color
                }),
                position: latLng,
                map: this.googleMap
            });

            google.maps.event.addListener(markersGoogle[user.name], 'click', function() {
                info.open(this.googleMap, markersGoogle[user.name]);
            });

    		return markersGoogle[user.name];
    	}
	},
	plotSelf: function() {
		var selfLoc = new google.maps.LatLng(myLat, myLong);
    	if(this.selfpin){
        	this.selfpin.setPosition(selfLoc);
    	} else{
            this.user = new User("You");
        	this.selfpin = new google.maps.Marker({
                icon: 'images/me.png',
                map: this.googleMap,
                position: selfLoc
            });
    	}
	},
	centerOnSelf: function() {
        this.googleMap.setCenter(new google.maps.LatLng(myLat, myLong));
	}
};