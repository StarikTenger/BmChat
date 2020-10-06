#include "Network_client.h"

sf::Packet& operator <<(sf::Packet& packet, const rapidjson::Document& doc)
{
	doc.
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, rapidjson::Document& doc)
{
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

int Network_client::send(int operation_code, rapidjson::Document data) {
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

//std::pair<int, rapidjson::Document> Network_client::receive(int operation_code, rapidjson::Document data) {
//	sf::Packet pack;
//	pack << operation_code << data;
//	if (socket.send(pack) != sf::Socket::Done)
//		std::cout << "sending error: please repeat later\n";
//	if (socket.receive(pack) != sf::Socket::Done)
//		std::cout << "recive error: server is unavailable\n";
//	int server_answer;
//	rapidjson::Document message;
//	pack >> server_answer;
//	return std::make_pair(server_answer, /*message*/);
//}
