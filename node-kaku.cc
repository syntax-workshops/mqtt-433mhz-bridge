#include <node.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include "RemoteTransmitter.cpp"

using namespace std;

namespace nodekaku {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

	void Broadcast(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		// Check the number of arguments passed.
		if (args.Length() != 3) {
			// Throw an Error that is passed back to JavaScript
			isolate->ThrowException(Exception::TypeError(
						String::NewFromUtf8(isolate, "Wrong number of arguments")));
			return;
		}

		// Check the argument types
		if (!args[0]->IsString() || !args[1]->IsNumber() || !args[2]->IsBoolean()) {
			isolate->ThrowException(Exception::TypeError(
						String::NewFromUtf8(isolate, "Wrong argument types")));
			return;
		}



		int pin_out = 15; // Pin out using wiringPi pin numbering scheme (15 = TxD / BCM GPIO 14, see https://projects.drogon.net/raspberry-pi/wiringpi/pins/)
		int device = args[1]->NumberValue();
		String::Utf8Value address_str(args[0]);
		char address = (*address_str)[0];
		bool state = args[2]->BooleanValue();

		//printf("device %i, address %c, state %d\n", device, address, state);


    // setup pin and make it low
	pinMode(pin_out, OUTPUT);
	digitalWrite(pin_out, LOW);
	KaKuTransmitter kaKuSwitch(pin_out);
	
	kaKuSwitch.sendSignal(address, device, state);
	}

	void Init(Local<Object> exports) {

	if(wiringPiSetup() == -1)
	{
		Isolate* isolate = Isolate::GetCurrent();
			isolate->ThrowException(Exception::TypeError( String::NewFromUtf8(isolate, "WiringPi setup failed. Maybe you haven't installed it yet?")));
			return;
	}
		NODE_SET_METHOD(exports, "broadcast", Broadcast);
	}

	NODE_MODULE(nodekaku, Init)

}

