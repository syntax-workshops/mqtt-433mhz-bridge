var mqtt   = require('mqtt');
var config = require('./config');

var mqttUri     = 'mqtt://' + config.mqtt.hostname + ':' + config.mqtt.port;
var mqttOptions = {username: config.mqtt.username, password: config.mqtt.password};
var client      = mqtt.connect(mqttUri, mqttOptions);

var kaku = require('./build/Release/node-kaku');

client.on('message', function (topic, message) {
	var parts = topic.split("/");
	var device = Number(parts.pop());
	var address = parts.pop();
	var state = null;
	if(message == "on") {
		state = true;
	} else if(message == "off") {
		state = false;
	} else {
		throw 'Invalid message';
	}

	console.log("Broadcasting:", address, device, state);
	kaku.broadcast(address, device, state);
});

client.on('connect', function () {
	// Subscribe on everything in the MQTT namespace
	client.subscribe(config.mqtt.namespace + '/#');
	console.log("Subscribed to topic:", config.mqtt.namespace + '/#');
});
