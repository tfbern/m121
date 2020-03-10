// serial gateway
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const serial = new SerialPort('COM3', { baudRate: 115200 })
const parser = new Readline()
serial.pipe(parser)
// debug serial traffic
parser.on('data', function (line) {
  // console.log(line)
})

// WebSocket server
const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 81 });
wss.on('connection', function connection(ws) {
  // on receive client message
  ws.on('message', function incoming(message) {
    // console.log('Forwarding command to Arduino: %s', message);
    serial.write(message + "\r")
  });  
  // on serial event
  parser.on('data', function (line) {
    try {
      var obj = JSON.parse(line)
      ws.send(JSON.stringify(obj));
    } catch(err) {
      // console.log(err)
      console.log('parse error: skipping malformed data')
    }
  })
});


// Web server
const express = require('express')
const app = express()
const webroot = __dirname + '/../client'
app.use(express.static(webroot))
app.listen(80, console.log("Serving GUI on port 80"))