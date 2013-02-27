$ = (id) ->
  document.getElementById id

Socket = undefined
Socket = WebSocket  if typeof (WebSocket) is "function"
Socket = MozWebSocket  if typeof (MozWebSocket) is "function"
Socket::sendJSON = (j) ->
  json = JSON.stringify(j)
  @send json

Socket::decodeJSON = (j) ->
  # {"SUBSCRIBE":["message","testusr3","43.5046929966,-80.5312201434"]}
  json = JSON.parse(j.data)["SUBSCRIBE"]
  return false if not (json[0] is "message")
  coordinates = json[2].split(',')
  data =
    user: new User(json[1])
    location:
      x: parseFloat(coordinates[0])
      y: parseFloat(coordinates[1])

  data

class User
   constructor: (@name) ->
     @color = '#'+Math.floor(Math.random()*16777215).toString(16)

window.Socket = Socket

window.User = User