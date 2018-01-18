var osc = require("osc"),
    WebSocket = require("ws");

var getIPAddresses = function () {
    var os = require("os"),
    interfaces = os.networkInterfaces(),
    ipAddresses = [];

    for (var deviceName in interfaces){
        var addresses = interfaces[deviceName];

        for (var i = 0; i < addresses.length; i++) {
            var addressInfo = addresses[i];

            if (addressInfo.family === "IPv4" && !addressInfo.internal) {
                ipAddresses.push(addressInfo.address);
            }
        }
    }

    return ipAddresses;
};

/*
    OSC to/from Lemur Bounce Interface
*/
var udp = new osc.UDPPort({
    localAddress: "127.0.0.1",
    localPort: 7000,
    remoteAddress: "127.0.0.1",
    remotePort: 57121
});

udp.on("ready", function () {
    var ipAddresses = getIPAddresses();
    console.log("Interface:");
    ipAddresses.forEach(function (address) {
        console.log("Listening on", address + ":" + udp.options.localPort);
    });
    console.log("Sending to", udp.options.remoteAddress + ":" + udp.options.remotePort);
    console.log("");
});

udp.open();

var wss = new WebSocket.Server({
    port: 8081
});

wss.on("connection", function (socket) {
    console.log("A Web Socket connection has been established! (Interface)");
    var socketPort = new osc.WebSocketPort({
        socket: socket
    });

    var relay = new osc.Relay(udp, socketPort, {
        raw: true
    });
});

var express = require('express');
var app = express();
var path = require('path');

app.use(express.static( __dirname + '/web'));

app.get('/', function (req, res) {
  res.sendFile(path.join(__dirname, 'web', 'index.html'));
});

app.listen(3000, function () {
  console.log('Node server is listening on port 3000!');
});