#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Message.h"

class User {
public:
	User();
	User(std::string name = "deleted", std::string pass = "admin", int ID = 0);
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