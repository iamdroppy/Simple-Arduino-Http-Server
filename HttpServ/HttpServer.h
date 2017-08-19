#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dns.h>
#include <Dhcp.h>
#include <SPI.h>
#include "HttpRequest.h"

enum PinCallback { OnAvailable, OnProcessing };

#pragma once
class HttpServer
{
public:
	HttpServer(int port);
	virtual ~HttpServer();
	bool begin();
	void setPinCallback(int pin, PinCallback callbackType);
	HttpRequest* captureRequest();
	EthernetServer* getEthernetServer();

private:
	int _onAvailablePin = 0;
	int _onAvailablePinStats = LOW;
	int _onProcessingPin = 0;
	int _onProcessingPinStats = LOW;
	void setPin(int* statsPtr, int pin, int stats);
	IPAddress* _ipAddr;
	EthernetServer* _ethernetServer;
};

#endif