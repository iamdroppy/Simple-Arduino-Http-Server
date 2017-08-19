
#include "HttpServer.h"
#include "HttpRequest.h"

HttpServer* _server;

void setup() {
	Serial.begin(9600);
	Serial.println("Welcome to SAHS (Simple Arduino Http Server).");
	byte mac_address[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	IPAddress address = IPAddress(192, 168, 25, 133);
	Ethernet.begin(mac_address, address);
	beginServer();
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
	HttpRequest* request = _server->captureRequest();

	if (request) {
		request->handleClient();
		Serial.println("Client handled.");
	}
}
