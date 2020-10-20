#include "User.h"
//User::User() {
//	username = "";
//	password = "";
//	user_ID = 0;
//}
User::User(std::string name, std::string pass, int ID, Network_client *_client, std::set<int> dialogs_ids) {
	username = name;
	password = pass;
	user_ID = ID;
	client = _client;
	dialogs_ID = dialogs_ids;
}

std::string User::string_parce(std::string str)
{
	std::string ans = "[";
	for (int i = 0; i < str.size(); i++) {
		int k = str[i];
		char buff[5];
		itoa(k, buff, 10);
		ans += buff;
		ans += ',';
	}
	ans[ans.size() - 1] = ']';
	return ans;
}

std::string User::string_unparce(rapidjson::Document* d)
{
	std::string ans = "";
	if (!((*d).IsArray()))
		return ans;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		ans += (char)i->GetInt();
	}
	return ans;
}


rapidjson::Document User::user_parce() {
	std::string ans = "[";

	for (int i = 0; i < 2; i++) {
		int k;
		switch (i) {
		case 0: k = user_ID;
			break;
		case 1: k = username.size();
			break;
		}
		char buff[5];
		itoa(k, buff, 10);
		ans += buff;
		ans += ',';
	}

	for (int i = 0; i < username.size(); i++) {
		int k = username[i];
		char buff[5];
		itoa(k, buff, 10);
		ans += buff;
		ans += ',';
	}

	for (int i = 0; i < password.size(); i++) {
		int k = password[i];
		char buff[5];
		itoa(k, buff, 10);
		ans += buff;
		ans += ',';
	}

	ans[ans.size() - 1] = ']';

	rapidjson::Document doc;
	rapidjson::StringStream s(ans.c_str());
	doc.ParseStream(s);
	return doc;
}
void User::user_unparce(rapidjson::Document* d) {
	int k = 0, u_s = 0;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		switch (k) {
		case 0: user_ID = (int)i->GetInt();
			break;
		case 1: u_s = (int)i->GetInt();
			break;
		}
		if (k > 1)
		{
			if (k < u_s + 2)
				username += (char)i->GetInt();
			else
				password += (char)i->GetInt();
		}
		k++;
	}
}

bool User::is_password_correct (std::string pass) {
	return (pass == password);
}
bool User::change_password(std::string old_pass, std::string new_pass) {
	if (is_password_correct(old_pass))
		password = new_pass;
	rapidjson::Document d;
	new_pass = string_parce(new_pass);
	rapidjson::StringStream s(new_pass.c_str());
	d.ParseStream(s);
	client->send(3, &d);
	return is_password_correct(new_pass);
}
std::string User::get_username() {
	return username;
}
int User::get_user_ID() {
	return user_ID;
}
std::set <int> User::get_dialogs_ID() {
	return dialogs_ID;
}
void User::change_username(std::string new_name) {
	username = new_name;
	rapidjson::Document d;
	new_name = string_parce(new_name);
	rapidjson::StringStream s(new_name.c_str());
	d.ParseStream(s);
	client->send(2, &d);
}

void User::enter_the_dialog(int ID) {
	dialogs_ID.insert(ID);

	//обращение к серверу с целью обновления информации о dialogs_ID пользователя
}
void User::get_out_of_dialog(int ID) {
	dialogs_ID.erase(ID);
	//обращение к серверу с целью обновления информации о dialogs_ID пользователя
}
void User::send_message(Message text) {
	//обращение к серверу с целью создания нового сообщения
}