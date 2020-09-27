/*
       Servers operation codes
1:
	expected:
	returns:
2:
	expected:
	returns:
3:
	expected:
	returns:
4:
	expected:
	returns:
5:
	expected:
	returns:
...
*/
#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class Network_client
{
public:
	Network_client();
	Network_client(int port1 = 53000, std::string serverIP1 = "localhost");
	void change_port(int newport);
	int send(int operation_code, std::string data);
	std::pair<int, std::string> receive(int operation_code, std::string data);
private:
	int port;
	std::string serverIP;
	sf::TcpSocket socket;
	sf::Socket::Status status;
};

