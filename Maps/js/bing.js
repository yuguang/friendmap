var BingMap = function(){};
extend(BingMap, AbstractMap);
BingMap.prototype = {
	init: function(options) {
		this.bingMap = new Microsoft.Maps.Map(document.getElementById("map_canvas"), options);
		markersBing = {};
		infosBing = {};
	},
	plot: function(location, user) {
		var latLng = new Microsoft.Maps.Location(location.x, location.y);
		if (user.name in markersBing) {
			infosBing[user.name].setLocation(latLng);
			return markersBing[user.name].setLocation(latLng);
		} else {
			// create infobox with user profile
    		var info = new Microsoft.Maps.Infobox(
    			latLng, {
    			title: user.name + '<br/><img border="0" align="left" src="http://friendtracker.org/client/pics/'
    				+ user.name + '.png"/>',
    			visible: false,
    			width: 150,
    			height: 165,
    			showPointer: false,
    			offset: new Microsoft.Maps.Point(-75, 50)
    		});
    		infosBing[user.name] = info;

    		// create pushpin for a user
    		markersBing[user.name] = new Microsoft.Maps.Pushpin(latLng, {
    			text: user.name,
    			infobox: info,
    			typeName: 'pinCSS',
    			textOffset: new Microsoft.Maps.Point(-user.name.length*4/3, 40)
    		});

    		Microsoft.Maps.Events.addHandler(markersBing[user.name], 'click', function(e) {
    			infosBing[user.name].setOptions({
    				visible: false
    			});
    			info.setOptions({
    				visible: true
    			});
    		});

    		this.bingMap.entities.push(markersBing[user.name]);
    		this.bingMap.entities.push(info);

    		return markersBing[user.name];
    	}
	},
	plotSelf: function() {
		var selfLoc = new Microsoft.Maps.Location(myLat, myLong);
    	if(this.selfpin){
        	this.selfpin.setLocation(selfLoc);
    	} else{
        	this.selfpin = new Microsoft.Maps.Pushpin(selfLoc, {
            	text: "You",
              	typeName: 'pinCSS',
              	//textOffset: (0,50),
              	icon: 'images/me.png',
              	anchor: new Microsoft.Maps.Point(0,50)
          	});
        	this.bingMap.entities.push(this.selfpin);
    	}
	},
	centerOnSelf: function() {
		this.bingMap.setView({
			center: new Microsoft.Maps.Location(myLat, myLong)
		});
	},
    centerToLoc: function(lat,long) {
        this.bingMap.setView({
            center: new Microsoft.Maps.Location(lat, long);
        });
    }
};