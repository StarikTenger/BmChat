/*
       Servers operation codes
0: create new user
	expected: (username, password, ID)
	returns:  if ((input correct) && (username is available)) {return 1;} else {return 0;}

1: create new conversation
	expected: (username, password, conversation name)
	returns:

2: set information
	expected: (username, password, file addres (ex. BmChatServer\Users\Username\password.json), newinformation)
	returns: if ((input correct) && (password correct) && (username have permission to change information)) {return 1;} else {return 0;} 
3: 
	expected:
	returns:
4:
	expected:
	returns:
5:
	expected:
	returns:
6:
	expected:
	returns:
...
*/
#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <rapidjson.h>
#include <document.h>
#include <memorybuffer.h>

class Network_client
{
public:
	Network_client();
	Network_client(int port1 = 53000, std::string serverIP1 = "localhost");
	void change_port(int newport);
	int send(int operation_code, rapidjson::Document data);
	std::pair<int, rapidjson::Document> receive(int operation_code, rapidjson::Document data);
private:
	int port;
	std::string serverIP;
	sf::TcpSocket socket;
	sf::Socket::Status status;
};

