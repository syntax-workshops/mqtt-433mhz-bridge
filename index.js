var mqtt   = require('mqtt');
var client = mqtt.connect('mqtt://test.mosquitto.org');
var config = require('./config');

var mqttUri     = 'mqtt://' + config.mqtt.hostname + ':' + config.mqtt.port;
var mqttOptions = {username: config.mqtt.username, password: config.mqtt.password};
var client      = mqtt.connect(mqttUri, mqttOptions);

client.on('message', function (topic, message) {
});

client.on('connect', function () {
    // Subscribe on everything in the MQTT namespace
    client.subscribe(config.mqtt.namespace + '/#');
});
