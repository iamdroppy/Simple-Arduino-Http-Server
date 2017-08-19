
#include "HttpServer.h"
#include "HttpRequest.h"

HttpServer* _server;

const int RedLed = 9;

void setup() {
	Serial.begin(9600);
	Serial.println("Hullo!");

	byte mac_address[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	IPAddress address = IPAddress(192, 168, 25, 133);

	Ethernet.begin(mac_address, address);
	
	pinMode(9, OUTPUT);
	pinMode(11, OUTPUT);
	beginServer();

}

static void headerCallback()
{
	Serial.println("Header Callback!");
}

void beginServer() {
	_server = new HttpServer(80);

	_server->setPinCallback(9, (PinCallback)OnAvailable);
	_server->setPinCallback(11, (PinCallback)OnProcessing);
	_server->begin();
}

void destroyServer() {
	delete _server;
	_server = nullptr;
}


void loop() {
	HttpRequest* request = _server->captureRequest()->setHeaderCallback(*headerCallback);

	if (request) {
		request->handleClient();
		Serial.println("OKAY!");
	}
}
