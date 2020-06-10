const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('//COM4', { baudRate: 115200 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);

app.get('/', function(req, res){
  res.sendFile(__dirname +'/index.html');
});

/*
io.on('connection', function(socket){
  socket.emit('chat message', function(data){
    console.log('message: ' + data);
  });
});

parser.on('data', data =>{
  console.log('got word from arduino:', data);
});
*/

parser.on('data', data =>{
  io.emit('data', data);
});

io.on('connection', function(socket){
  socket.on('data', function(data){
    io.emit('data', data);
  });
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
