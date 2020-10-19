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
#include "Message.h"
#include <iostream>
#include "Network_client.h"

class User {
public:
	//User();
	User(std::string name = "", std::string pass = "", int ID = 0);

	rapidjson::Document user_parce();
	void user_unparce(rapidjson::Document *d);

	void send_message(Message text);
	bool is_password_correct(std::string pass);
	bool change_password(std::string old_pass, std::string new_pass);
	std::string get_username();
	int get_user_ID();
	std::vector <int> get_dialogs_ID();
	void change_username(std::string new_name);
	void change_user_ID(int new_ID);
	void add_dialog_ID(int ID);
	void delete_dialog_ID(int ID);
	void change_dialogs_ID(std::vector <int> IDs);

private:
	std::string password;
	std::string username;
	std::vector <int> dialogs_ID;
	int user_ID;
};