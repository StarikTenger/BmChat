#include "Network_client.h"
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

int Network_client::send(int operation_code, std::string data) {
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

std::pair<int, std::string> Network_client::receive(int operation_code, std::string data) {
	sf::Packet pack;
	pack << operation_code << data;
	if (socket.send(pack) != sf::Socket::Done)
		std::cout << "sending error: please repeat later\n";
	if (socket.receive(pack) != sf::Socket::Done)
		std::cout << "recive error: server is unavailable\n";
	int server_answer;
	std::string message;
	pack >> server_answer;
	return make_pair(server_answer, message);
}
