#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <rapidjson.h>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>

int main() {
    rapidjson::Value json_val;
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    doc.SetObject();

    std::string name = "Hello world!!!";

    json_val.SetString(name.c_str(), allocator);
    doc.AddMember("name", json_val, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    //doc.Accept(buffer);

    /*const std::string& str = buffer.GetString();
    std::cout << "Serialized:" << std::endl;
    std::cout << str << std::endl;
    /*sf::TcpSocket socket;
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
    }*/
    return 0;
}