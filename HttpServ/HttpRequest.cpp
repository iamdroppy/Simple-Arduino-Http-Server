#include "HttpRequest.h"


HttpRequest::HttpRequest(EthernetClient ethernetClient)
{
	_userClient = ethernetClient;
}

HttpRequest::~HttpRequest()
{
}

HttpRequest* HttpRequest::setHeaderCallback(void* headerCallback)
{
	_headerCallback = headerCallback;
	return this;
}

void HttpRequest::handleClient()
{
	readHeader();
}

void HttpRequest::readHeader()
{
	String header;
	int maxLines = 32;

	Serial.println("Starting to read header.");
	for (int lines = 0; lines < maxLines; lines++)
	{
		if (!_userClient.connected() || !_userClient.available())
			break;

		if (lines == 0)
		{
			String verb = readUntilSpace();
			String uri = readUntilSpace();
			_userClient.println("VERB: "+ verb + "\r\nUri: " + uri);

			_userClient.stop();

			if (verb == "GET") {
				// fake large response..
				if (uri == "/largeresponse")
					delay(5000);
			}
		}
		else {
		}
	}
}

String HttpRequest::readLine()
{
	return _userClient.readStringUntil('\n');
}

String HttpRequest::readUntilSpace()
{
	return _userClient.readStringUntil(' ');
}

bool HttpRequest::connected()
{
	return _userClient.connected();
}