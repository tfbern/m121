// serial port
const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const port = new SerialPort('COM3', { baudRate: 9600 })
const parser = new Readline()
port.pipe(parser)
port.write('SERVER READY\n')
parser.on('data', function (line) {
  // console.log(JSON.parse(line))
  if (line != -1) {
    console.log(`Arduino> ${line}`)
    // port.write("Hallo Arduino\r")
  }
})

const WebSocket = require('ws');
const wss = new WebSocket.Server({ port: 8080 });
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(message) {
    console.log('received: %s', message);
    port.write(message + "\r")
  });  
  ws.send('something');
  // serial events
  parser.on('data', function (line) {
    ws.send(line);
  })
});
