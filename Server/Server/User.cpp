#include "User.h"
User::User() {}
User::User(std::string name, std::string pass, int ID) {
	username = name;
	password = pass;
	user_ID = ID;
}
bool User::is_password_correct (std::string pass) {
	return (pass == password);
}
bool User::change_password(std::string old_pass, std::string new_pass) {
	if (is_password_correct(old_pass))
		password = new_pass;
	return is_password_correct(new_pass);
	//обращение к серверу с целью обновления информации о password пользователя
}
std::string User::get_username() {
	return username;
}
int User::get_user_ID() {
	return user_ID;
}
std::vector <int> User::get_dialogs_ID() {
	return dialogs_ID;
}
void User::change_username(std::string new_name) {
	username = new_name;
	//обращение к серверу с целью обновления информации о username пользователя
}
void User::change_user_ID(int new_ID) {
	user_ID = new_ID;
	//обращение к серверу с целью обновления информации о user_ID пользователя
}
void User::add_dialog_ID(int ID) {
	dialogs_ID.push_back(ID);
	//обращение к серверу с целью обновления информации о dialogs_ID пользователя
}
void User::delete_dialog_ID(int ID) {
	for (auto it = dialogs_ID.begin(); it != dialogs_ID.end(); it++)
		if (*it == ID)
			dialogs_ID.erase(it);
	//обращение к серверу с целью обновления информации о dialogs_ID пользователя
}
void User::change_dialogs_ID(std::vector <int> IDs) {
	dialogs_ID = IDs;
	//обращение к серверу с целью обновления информации о dialogs_ID пользователя
}
void User::send_message(Message text) {
	//обращение к серверу с целью создания нового сообщения
}