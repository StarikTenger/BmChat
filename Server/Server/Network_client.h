/*
       Servers operation codes
0: create new user
	expected: (username, password, ID)
	returns:  if (input correct) {return 1;} else {return 0;}

1: create new conversation
	expected: (password, conversation name, user_ID, conversation_ID)
	returns:  if (input correct) {return 1;} else {return 0;}

2: set new username
	expected: (password, new_username, user_id)
	returns: if ((input correct) && (password correct) && (username have permission to change information)) {return 1;} else {return 0;} 

3: set new password
	expected: (password, new_password, user_id)
	returns:  if (input correct) {return 1;} else {return 0;}

4: enter the dialog
	expected: (password, user_id, conversation_id)
	returns:

5: send message
	expected: (password, text, user_id, conversation_id, message_id)
	returns:

6: get new user id
	expected: 
	returns:  new user id

7: get new conversation id
	expected: 
	returns:  new conversation id

8: get new message id
	expected: (conversation_id)
	returns:  new message id

9: get out of the dialog
	expected: (password, user_id, conversation_id)
	returns:

10: login
	expected: (password, username)
	returns: user

11: get user
	expected: (password, user_id)
	returns:
...
*/
#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#include <SFML/Network.hpp>
#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <filereadstream.h>
#include <filewritestream.h>
#include <writer.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <vector>
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
	int send(int operation_code, rapidjson::Document *data);
	int receive(int operation_code, rapidjson::Document *data, rapidjson::Document *ans);
private:
	int port;
	std::string serverIP;
	sf::TcpSocket socket;
	sf::Socket::Status status;
	void sendDoc(sf::Packet* packet, const rapidjson::Document* doc);
	void getDoc(sf::Packet* packet, rapidjson::Document* doc);
};

