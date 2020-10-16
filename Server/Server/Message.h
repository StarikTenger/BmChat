#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#include <SFML/Network.hpp>
#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <string>
#include <fstream>
#include "User.h"
#include <cstdio>
#include <filereadstream.h>
#include <filewritestream.h>
#include <writer.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
#include <vector>

class Message {
	std::string text = ""; // Text value

	int message_ID = 0; // Own ID
	int dialog_ID = 0; // Dialog ID
	int user_ID = 0; // User ID

public:
	Message();
	Message(std::string _text, int _dialog_ID, int _user_ID, int _message_ID);

	rapidjson::Document message_parce();
	void message_unparce(rapidjson::Document *d);

	int get_message_ID();
	int get_dialog_ID();
	int get_user_ID();
	std::string get_text();

	void set_message_ID(int _message_ID);
	void set_dialog_ID(int _dialog_ID);
	void set_user_ID(int _user_ID);
	void set_text(std::string _text);
};

