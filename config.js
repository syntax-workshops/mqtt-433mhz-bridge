var config = {};

config.debug = process.env.DEBUG || false;
config.mqtt  = {};

config.mqtt.namespace = process.env.MQTT_NAMESPACE || 'lights';
config.mqtt.hostname  = process.env.MQTT_HOSTNAME  || 'localhost';
config.mqtt.port      = process.env.MQTT_PORT      || 1883;
config.mqtt.username  = process.env.MQTT_USERNAME  || '';
config.mqtt.password  = process.env.MQTT_PASSWORD  || '';

module.exports = config;
