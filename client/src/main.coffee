markers = {}
plot = (location, user) ->

  # set the location...
  latLng = new google.maps.LatLng(location.x, location.y)

  # ...and add the Marker to your map
  if user.name of markers
    markers[user.name].setPosition(latLng)
  else
    markers[user.name] = new StyledMarker(
      styleIcon: new StyledIcon(StyledIconTypes.MARKER,
        color: user.color
      )
      position: latLng
      map: map
    )

initialize = ->
  options =
    center: new google.maps.LatLng(43.4879158266,-80.5462864345)
    mapTypeId: google.maps.MapTypeId.ROADMAP
    zoom: 15

  window.map = new google.maps.Map(document.getElementById("map_canvas"), options)
  host = "198.58.106.27"
  port = 8080
  socket = new WebSocket("ws://" + host + ":" + port + "/")
  socket.onopen = ->
    for i in [1..20]
      socket.sendJSON {"SUBSCRIBE": "testusr#{i}"}
  socket.onmessage = (message) ->
    data = this.decodeJSON(message)
    if data
      plot(data.location, data.user)

window.map = undefined
google.maps.event.addDomListener window, "load", initialize
