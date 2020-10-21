#include "User.h"
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

	for (int i = 0; i < 4; i++) {
		int k;
		switch (i) {
		case 0: k = user_ID;
			break;
		case 1: k = username.size();
			break;
		case 2: k = password.size();
			break;
		case 3: k = dialogs_ID.size();
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

	for (auto i = dialogs_ID.begin(); i != dialogs_ID.end(); i++) {
		int k = *i;
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
	int k = 0, u_s = 0, p_s, id_s;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		switch (k) {
		case 0: user_ID = (int)i->GetInt();
			break;
		case 1: u_s = (int)i->GetInt();
			break;
		case 2: p_s = (int)i->GetInt();
			break;
		case 3: id_s = (int)i->GetInt();
			break;
		}
		if (k > 3)
		{
			if (k < u_s + 4)
				username += (char)i->GetInt();
			else {
				if (k < p_s + u_s + 4)
					password += (char)i->GetInt();
				else
					dialogs_ID.insert((int)i->GetInt());
			}
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

	char new_pass_size[20], pass_size[20], id[20];
	itoa(new_pass.size(), new_pass_size, 10);
	itoa(old_pass.size(), pass_size, 10);
	itoa(user_ID, id, 10);

	new_pass = pass_size + old_pass + new_pass_size + new_pass + id;
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
	rapidjson::Document d;
	username = new_name;

	char new_name_size[20], pass_size[20], id[20];
	itoa(new_name.size(), new_name_size, 10);
	itoa(password.size(), pass_size, 10);
	itoa(user_ID, id, 10);

	new_name = pass_size + password + new_name_size + new_name + id;
	new_name = string_parce(new_name);
	rapidjson::StringStream s(new_name.c_str());
	d.ParseStream(s);
	client->send(2, &d);
}

void User::enter_the_dialog(int ID) {
	dialogs_ID.insert(ID);

	char pass_size[20], u_id[20], c_id[20];
	itoa(password.size(), pass_size, 10);
	itoa(user_ID, u_id, 10);
	itoa(ID, c_id, 10);

	rapidjson::Document d;
	std::string str = pass_size + password + u_id + c_id;
	str = string_parce(str);
	rapidjson::StringStream s(str.c_str());
	d.ParseStream(s);
	client->send(4, &d);
}
void User::get_out_of_dialog(int ID) {
	dialogs_ID.erase(ID);

	char pass_size[20], u_id[20], c_id[20];
	itoa(password.size(), pass_size, 10);
	itoa(user_ID, u_id, 10);
	itoa(ID, c_id, 10);

	rapidjson::Document d;
	std::string str = pass_size + password + u_id + c_id;
	str = string_parce(str);
	rapidjson::StringStream s(str.c_str());
	d.ParseStream(s);
	client->send(9, &d);
}
void User::send_message(Message message) {
	char pass_size[20], text_size[20], u_id[20], c_id[20], m_id[20];
	itoa(password.size(), pass_size, 10);
	itoa(message.get_text().size(), text_size, 10);
	itoa(user_ID, u_id, 10);
	itoa(message.get_dialog_ID(), c_id, 10);
	itoa(message.get_message_ID(), m_id, 10);

	rapidjson::Document d;
	std::string str = pass_size + password + text_size + message.get_text() + u_id + c_id + m_id;
	str = string_parce(str);
	rapidjson::StringStream s(str.c_str());
	d.ParseStream(s);
	client->send(5, &d);
};