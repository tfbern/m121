// Web server
const express = require('express')
const app = express()
const webroot = __dirname + '/../client'
app.use(express.static(webroot))
app.listen(80, console.log("Serving GUI on port 80"))


// WebSocket server
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 81 });
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(data) {
    wss.clients.forEach(function each(client) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(data);
      }
    });
  });
});

// test comment 1
// serial gateway
const ws = new WebSocket('ws://localhost:81');
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const serial = new SerialPort('COM3', { baudRate: 9600 })
const parser = new Readline()
// forwarding messages from serial to websocket
serial.pipe(parser)
parser.on('data', function (line) {
  try {
    var obj = JSON.parse(line)
    ws.send(line);
  } catch(err) {
    // console.log(err)
    console.log('gateway parse error: skipping malformed data')
  }
})
// forwarding messages from websocket to serial
ws.on('message', function(message) {
  console.log('gateway forwarding command to Arduino: ' + message)
  serial.write(message + "\r")
})



