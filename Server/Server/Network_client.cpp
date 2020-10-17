#include "Network_client.h"

sf::Packet& operator <<(sf::Packet& packet, rapidjson::Document& doc)
{
	packet << (doc.Size());
	for (auto i = doc.GetArray().Begin(); i != doc.GetArray().End(); i++) {
		packet << (i->GetInt());
	} 
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, rapidjson::Document& doc)
{
	int len, k;
	packet >> len;
	std::string arr = "[";
	for (int i = 0; i < len; i++) {
		packet >> k;
		char buff[20];
		itoa(k, buff, 10);
		arr += buff;
		arr += ",";
 	}
	arr[arr.size() - 1] = ']';
	rapidjson::StringStream s(arr.c_str());
	doc.ParseStream(s);
	return packet;
}

Network_client::Network_client() {}

Network_client::Network_client(int port1, std::string serverIP1) {
	port = port1;
	serverIP = serverIP1;
	status = socket.connect(serverIP, port);
	if (status != sf::TcpSocket::Done)
		std::cout << "connection error: server is unavailable\n";
}

void Network_client::change_port(int newport) {
	port = newport;
	status = socket.connect(serverIP, port);
	if (status != sf::TcpSocket::Done)
		std::cout << "connection error: server is unavailable\n";
}

int Network_client::send(int operation_code, rapidjson::Document *data) {
	sf::Packet pack;
	pack << operation_code << data;
	if (socket.send(pack) != sf::Socket::Done)
		std::cout << "sending error: please repeat later\n";
	if (socket.receive(pack) != sf::Socket::Done)
		std::cout << "recive error: server is unavailable\n";
	int server_answer;
	pack >> server_answer;
	return server_answer;
}

int Network_client::receive(int operation_code, rapidjson::Document *data, rapidjson::Document *ans) {
	sf::Packet pack;
	pack << operation_code << data;
	if (socket.send(pack) != sf::Socket::Done)
		std::cout << "sending error: please repeat later\n";
	if (socket.receive(pack) != sf::Socket::Done)
		std::cout << "recive error: server is unavailable\n";
	int server_answer;
	pack >> server_answer >> (*ans);
	return server_answer;
}
