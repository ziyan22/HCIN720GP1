//Run this file with "node server.js"
var express = require('express');
var app = express();
var http       = require('http').Server(app);
var io         = require('socket.io')(http);
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;

app.use(express.static(__dirname + '/public'));
app.get('/', function(req, res){res.sendfile('testing.html');});

//Listen for incoming connections
http.listen(3000, function(){console.log("listening on port 3000");});

//Hook up the serial port
var serial = new SerialPort( '/dev/cu.usbmodem1421', {parser: serialport.parsers.readline('\n')});

//When the serial port is successfully opened...
serial.on('open', function()
{
	console.log("opened serial port");
	//When we get data from the serial port...
	serial.on('data', function(data)
	{
		console.log(data);
			console.log("got some data from PhotonO: ", data);
			//Send to the browser; 'data' is the name of the event
			io.emit('to browser', data);
	});
});

//Here's what happens when a connection is made from the browser
io.sockets.on('connection',
	function(socket)
	{
		console.log("someone connected");

		//Since the socket is open, we can now accept "to serial" messages
		// from the browser
		socket.on('to serial', function(data)
		{
			if(serial.isOpen())
			{
				serial.write(data);
				console.log("Send '" + data + "' to serial");
			}
			else
				console.log("Serial port not open");
		});
	}
);
