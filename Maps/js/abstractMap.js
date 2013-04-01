var g_map = null;

var AbstractMap = function() {};
AbstractMap.prototype = {
	init: function() {
		throw new Error("Unsupported operation on an abstract class.");
	},
	plot: function(location, user) {
		throw new Error("Unsupported operation on an abstract class.");
	},
	plotSelf: function() {
		throw new Error("Unsupported operation on an abstract class.");
	},
	centerOnSelf: function() {
		throw new Error("Unsupported operation on an abstract class.");
	},
	centerToLoc: function(lat,long) {
		throw new Error("Unsupported operation on an abstract class");
	}
};
AbstractMap.getCurrentMap = function() {
	return g_map;
}