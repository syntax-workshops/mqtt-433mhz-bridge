# mqtt-433mhz-bridge

Node.js program that translates MQTT messages to 433mhz radio broadcasts

## Installation on Raspberry pi

```
# Install dependencies
$ sudo apt-get update && sudo apt-get upgrade
$ sudo apt-get install git-core mosquitto supervisor

# Install wiringPi system-wide
$ git clone git://git.drogon.net/wiringPi
$ cd wiringPi && ./build

# Install node.js
$ curl -sL https://deb.nodesource.com/setup_4.x | sudo -E bash -
$ sudo apt-get install -y nodejs

# Almost there...
$ git clone https://github.com/syntax-workshops/mqtt-433mhz-bridge.git
$ cd mqtt-433mhz-bridge
$ npm install
$ sudo ln -s ./supervisor.conf /etc/supervisor/conf.d/mqtt-433mhz-bridge.conf
$ sudo supervisorctl update
$ sudo supervisorctl start mqtt-433mhz-bridge
```

Now you can send 433mhz broadcasts over MQTT! For example:

`mosquitto_pub -h raspberrypi.local -t lights/M/1 -m on`

# Acknowledgements & license

This software includes a modified copy of the [RemoteSwitch library](https://bitbucket.org/fuzzillogic/433mhzforarduino/wiki/Home) by Randy Simons.
Because RemoteSwitch is licensed under GPLv3, this program has the same license.
