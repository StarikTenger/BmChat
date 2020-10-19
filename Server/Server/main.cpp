#define _CRT_NONSTDC_NO_DEPRECATE
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <rapidjson.h>
#include <vector>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include "Database.h"
#include "User.h"
#include "Message.h"

using namespace std;
using namespace sf;

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

rapidjson::Value::ValueIterator get_string(rapidjson::Value::ValueIterator beg, string* str)
{
    int k = beg->GetInt();
    beg++;
    for (int i = 0; i < k; i++, beg++)
        *str += (char)beg->GetInt();
}

int main() {

    /*                       ***Not Full Database test***
    Database d("C:\\Users\\mea25\\Desktop\\yu");
    int uid = d.new_user_ID(), cid = d.new_conversation_id(), uid2 = d.new_user_ID();
    d.create_user("Admin", "admin", uid);
    d.create_user("User", "user", uid2);
    User us, us2;
    rapidjson::Document doc = d.get_user(uid);
    us.user_unparce(&doc);
    doc = d.get_user(uid2);
    us2.user_unparce(&doc);
    d.create_conversation(us.get_user_ID(), "admin", "Development", cid);
    d.add_member(cid, uid2);
    d.add_message(us.get_user_ID(), "ain", cid, d.new_message_id(cid), "Hello im hacker");
    int mess_id = d.new_message_id(cid);
    d.add_message(us.get_user_ID(), "admin", cid, mess_id, "Hello world!!!");
    rapidjson::Document x = d.get_members(cid);
    for (auto i = x.Begin(); i != x.End(); i++)
        std::cout << i->GetInt() << " ";
    std::cout << "\n";
    Message k;
    k.message_unparce(&(d.get_message(cid, mess_id)));
    std::cout << k.get_dialog_ID() << " " << k.get_message_ID() << "\n" << k.get_text() << "\n" << k.get_user_ID() << "\n";*/
    //setlocale(LC_ALL, "");
    Database database;
    TcpListener listener;
    SocketSelector selector;
    vector<TcpSocket*> clients;

    listener.listen(53000);
    selector.add(listener);

    while (true) {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                TcpSocket* socket = new TcpSocket;
                listener.accept(*socket);
                clients.push_back(socket);
                selector.add(*socket);
            }
            else {
                for (int i = 0; i < clients.size(); i++) {
                    if (selector.isReady(*clients[i])) {
                        Packet packet, sendPacket;
                        if (clients[i]->receive(packet) == Socket::Done) {
                            int op_code;
                            rapidjson::Document doc;
                            packet >> op_code >> doc;
                            string username, password, conversation_name;
                            int user_id, conversation_id;
                            switch (op_code) {
                            case 0:
                                user_id = get_string(get_string(doc.Begin(), &username), &password)->GetInt();
                                database.create_user(username, password, user_id);
                                sendPacket << 1;
                                break;
                            case 1:
                                auto it = get_string(get_string(doc.Begin(), &password), &conversation_name);
                                user_id = it->GetInt();
                                it++;
                                conversation_id = it->GetInt();
                                database.create_conversation(user_id, password, conversation_name, conversation_id);
                                break;
                            case 2:
                                user_id = get_string(get_string(doc.Begin(), &username), &password)->GetInt();
                                database.change_username(user_id, password, username);
                                break;
                            case 3:
                                ;
                                break;
                            case 4:;
                                break;
                            case 5:;
                                break;
                            case 6:;
                                break;
                            case 7:;
                                break;
                            case 8:;
                                break;
                            case 9:;
                                break;
                            case 10:;
                                break;
                            case 11:;
                                break;
                            case 12:;
                                break;
                            case 13:;
                                break;
                            }
                            clients[i]->send(sendPacket);
                        }
                    }
                }
            }
        }
    }

    for (vector<TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
        delete* it;

    system("pause");
    return 0;
}