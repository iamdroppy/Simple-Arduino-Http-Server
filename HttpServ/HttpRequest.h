#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <EthernetUdp.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>
#include <Dns.h>
#include <Dhcp.h>

#pragma once
//reads input from client.
class HttpRequest
{
public:
	HttpRequest(EthernetClient ethernetClient);
	~HttpRequest();

	HttpRequest* setHeaderCallback(void* headerCallback);

	void readHeader();
	void handleClient();

	String readHeaderKey();
	String readHeaderValue();
	String readLine();
	String readUntilSpace();

	bool connected();
private:
	EthernetClient _userClient;
	void* _headerCallback;
	String _header;
	String _content;
};

#endif