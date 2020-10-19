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
#include "Message.h"

class Database {
public:
	Database();
	Database(std::string local_path);
	int new_user_ID();
	int new_conversation_id();
	int new_message_id(int conversation_id);
	void create_user(std::string username, std::string password, int user_id);
	int check_password(int user_id, std::string password);
	int change_username(int user_id, std::string _password, std::string _new_username);
	int change_password(int user_id, std::string password, std::string new_pass);
	void create_conversation(int user_id, std::string password, std::string conversation_name, int conversation_id);
	void add_member(int conversation_id, int user_id);
	void add_message(int user_id, std::string password, int conversation_id, int message_id, std::string text);
	rapidjson::Document get_message(int conversation_id, int message_id);
	rapidjson::Document get_members(int conversation_id);
	rapidjson::Document get_user(int user_id);
private:
	std::string local_path; // path to server folder (any request to the system forms as request(local_path+path ...))
	int max_user_id, max_conversation_id;
	void create_path(std::string path);
	int set_data(std::string path, rapidjson::Document *data);
	int get_data(std::string path, rapidjson::Document* data);
	std::string string_parce(std::string str);
	std::string string_unparce(rapidjson::Document* d);
	std::string array_parce(std::vector<int>* v);
	std::vector<int> array_unparce(rapidjson::Document* d);
};