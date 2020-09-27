#include <SFML/Network.hpp>
#include <iostream>
#include <string>
int main() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost" , 53000);
    if (status != sf::Socket::Done)
    {
        std::cout << "connection error";
    }
    sf::Packet data;
    int d = 1;
    data << d;
    if (socket.send(data) != sf::Socket::Done)
    {
        std::cout << "sending error";
    }
    return 0;
}