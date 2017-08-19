#include "HttpRequest.h"


HttpRequest::HttpRequest(EthernetClient ethernetClient)
{
	_userClient = ethernetClient;
}

HttpRequest::~HttpRequest()
{
	// TODO: disconnect client.
	delete &_userClient;
}

void HttpRequest::handleClient()
{
	readHeader();
}

void HttpRequest::readHeader()
{
	String header;
	int maxHeaders = 32;

	for (int lines = 0; lines < maxHeaders; lines++)
	{
		if (!_userClient.connected() || !_userClient.available())
			break;

		if (lines == 0)
		{
			String verb = readUntilSpace();
			String uri = readUntilSpace();
			_userClient.println("VERB: "+ verb + "\r\nUri: " + uri);

			if (verb == "GET") {
				// fake large response..
				if (uri == "/largeresponse")
					delay(5000);
			}

			_userClient.stop();
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