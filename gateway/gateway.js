// serial gateway
const url = 'ws://websocksrv.herokuapp.com'
const WebSocket = require('ws');
const ws = new WebSocket(url);
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
ws.on('open', function() {
  console.log('Connected to ' + url)
})
ws.on('message', function(message) {
  console.log('gateway forwarding command to Arduino: ' + message)
  serial.write(message)
})



