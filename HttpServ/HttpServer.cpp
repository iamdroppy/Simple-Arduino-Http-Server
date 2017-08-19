#include "HttpServer.h"

HttpServer::HttpServer(int port)
{
	_ethernetServer = new EthernetServer(port);
}

HttpServer::~HttpServer()
{
	delete _ethernetServer;
	_ethernetServer = nullptr;
	delete _ipAddr;
	_ipAddr = nullptr;
}

bool HttpServer::begin()
{
	_ethernetServer->begin();
	Serial.print("server is at ");
	Serial.println(Ethernet.localIP());
}

void HttpServer::setPinCallback(int pin, PinCallback callbackType)
{
	pinMode(pin, OUTPUT); // sets pin as output mode.

	if (callbackType == (PinCallback)OnAvailable)
		_onAvailablePin = pin;
	else if (callbackType == (PinCallback)OnProcessing)
		_onProcessingPin = pin;
}

HttpRequest* HttpServer::captureRequest()
{
	EthernetClient client = getEthernetServer()->available();

	if (client)
	{
		setPin(&_onAvailablePinStats, _onAvailablePin, LOW);
		setPin(&_onProcessingPin, _onProcessingPin, HIGH);
		if (client.connected()) {
			if (client.available()) {
				return new HttpRequest(client);
			}
		}
	}

	setPin(&_onAvailablePinStats, _onAvailablePin, HIGH);
	setPin(&_onProcessingPin, _onProcessingPin, LOW);

	return nullptr;
}

void HttpServer::setPin(int* statsPtr, int pin, int stats)
{
	if (statsPtr != &stats)
	{
		statsPtr = &stats;
		digitalWrite(pin, stats);
	}
}

EthernetServer* HttpServer::getEthernetServer()
{
	return _ethernetServer;
}