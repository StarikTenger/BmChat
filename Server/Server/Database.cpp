#include "Database.h"

Database::Database() {}

Database::Database(std::string _local_path) {
	local_path = _local_path;
	max_user_id = 0;
	max_conversation_id = 0;
}

int Database::new_user_ID() {
	return max_user_id++;
}

int Database::new_conversation_id() {
	return max_conversation_id++;
}

std::string Database::array_parce(std::vector<int> *v){
	std::string ans = "[";
	for (int i = 0; i < (*v).size(); i++) {
		char buff[5];
		itoa((*v)[i], buff, 10);
		ans += buff;
		ans += ',';
	}
	ans[ans.size() - 1] = ']';
	return ans;
}

std::vector<int> Database::array_unparce(rapidjson::Document *d){
	std::vector<int> ans;
	if (!((*d).IsArray()))
		return ans;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		ans.push_back(i->GetInt());
	}
	return ans;
}

std::string Database::string_parce(std::string str)
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

std::string Database::string_unparce(rapidjson::Document* d)
{
	std::string ans = "";
	if (!((*d).IsArray()))
		return ans;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		ans += (char)i->GetInt();
	}
	return ans;
}

void Database::create_path(std::string path) {
	std::string now;
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
			_mkdir(now.c_str());
		now += path[i];
	}
}

int Database::set_data(std::string path, rapidjson::Document *data) {
	path = local_path + path;
	create_path(path);
	FILE* fp = fopen(path.c_str(), "wb"); // non-Windows use "w"
	
	char writeBuffer[10000];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	(*data).Accept(writer);

	fclose(fp);
	return 1;
}

int Database::get_data(std::string path, rapidjson::Document *d) {
	path = local_path + path;
	FILE* fp = fopen(path.c_str(), "rb"); // non-Windows use "r"
	if (fp == 0)
		return 0;

	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	(*d).ParseStream(is);

	fclose(fp);
	return 1;
}

int Database::check_password(int user_id, std::string password) {
	std::string path = "\\Users\\";
	char u_id[20];
	itoa(user_id, u_id, 10);
	path += u_id;
	path += "\\password.json";
	rapidjson::Document doc;
	int ans = get_data(path, &doc);
	if (!ans)
		return 0;
	std::string pass = string_unparce(&doc);
	return (pass == password);
}

void Database::create_user(std::string username, std::string password, int user_id) {
	char u_id[20];
	itoa(user_id, u_id, 10);
	std::string path = "\\Users\\", lp;
	path += u_id;

	lp = path +"\\username.json";
	rapidjson::Document data;
	username = string_parce(username);
	rapidjson::StringStream s(username.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	rapidjson::Document data2;
	lp = path + "\\password.json";
	password = string_parce(password);
	rapidjson::StringStream s2(password.c_str());
	data2.ParseStream(s2);
	set_data(lp, &data2);
}

void Database::add_member(int conversation_id, int user_id) {
	char u_id[20], c_id[20];
	itoa(conversation_id, c_id, 10);
	itoa(user_id, u_id, 10);
	
	std::string path = "\\Users\\", lp;
	lp = path + u_id + "\\Conversations.json";
	create_path(local_path + lp);
	rapidjson::Document d;
	get_data(lp, &d);
	std::vector<int> conversations_list = array_unparce(&d);
	bool was = false;
	for (int i = 0; i < conversations_list.size(); i++)
		if (conversations_list[i] == conversation_id)
			was = true;
	if (!was)
	{
		rapidjson::Document data;
		conversations_list.push_back(conversation_id);
		std::string parced = array_parce(&conversations_list);
		rapidjson::StringStream s(parced.c_str());
		data.ParseStream(s);
		set_data(lp, &data);
	}

	path = "\\Conversations\\";
	lp = path + c_id + "\\Users.json";
	create_path(local_path + lp);
	rapidjson::Document d2;
	get_data(lp, &d2);
	std::vector<int> users_list = array_unparce(&d2);
	was = false;
	for (int i = 0; i < users_list.size(); i++)
		if (users_list[i] == user_id)
			was = true;
	if (!was)
	{
		rapidjson::Document data2;
		users_list.push_back(user_id);
		std::string parced2 = array_parce(&users_list);
		rapidjson::StringStream s2(parced2.c_str());
		data2.ParseStream(s2);
		set_data(lp, &data2);
	}
}

void Database::create_conversation(int user_id, std::string password, std::string conversation_name, int conversation_id) {
	if (check_password(user_id, password) == 0)
		return;

	char c_id[20];
	itoa(conversation_id, c_id, 10);
	std::string path = "\\Conversations\\", lp;
	path += c_id;

	lp = path + "\\conversation_name.json";
	rapidjson::Document data;
	conversation_name = string_parce(conversation_name);
	rapidjson::StringStream s(conversation_name.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	add_member(conversation_id, user_id);
}
void Database::add_message(int user_id, std::string password, int conversation_id, int message_id, std::string text) {
	if (check_password(user_id, password) == 0)
		return;

	char c_id[20], u_id[20], m_id[20];
	itoa(conversation_id, c_id, 10);
	itoa(user_id, u_id, 10);
	itoa(message_id, m_id, 10);
	std::string path = "\\Conversations\\", lp;
	path += c_id;
	path += "\\Messages\\";
	path += m_id;
	
	rapidjson::Document data;
	lp = path + "\\User_id.json";
	std::string id = string_parce(u_id);
	rapidjson::StringStream s(id.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	rapidjson::Document data2;
	lp = path + "\\Text.json";
	text = string_parce(text);
	rapidjson::StringStream s2(text.c_str());
	data2.ParseStream(s2);
	set_data(lp, &data2);

}

rapidjson::Document Database::get_message(int conversation_id, int message_id) {
	char c_id[20], m_id[20];
	itoa(conversation_id, c_id, 10);
	itoa(message_id, m_id, 10);

	std::string path = "\\Conversations\\", lp;
	path += c_id;
	path += "\\Messages\\";
	path += m_id;
	
	rapidjson::Document data;
	lp = path + "\\User_id.json";
	if (!get_data(lp, &data))
		return data;
	std::string id = string_unparce(&data);
	int user_id = atoi(id.c_str());

	rapidjson::Document data2;
	lp = path + "\\Text.json";
	if (!get_data(lp, &data2))
		return data2;
	std::string text = string_unparce(&data2);

	Message m(text, conversation_id, user_id, message_id);
	return m.message_parce();
}

rapidjson::Document Database::get_members(int conversation_id) {
	char c_id[20];
	itoa(conversation_id, c_id, 10);

	std::string path = "\\Conversations\\", lp;
	lp = path + c_id + "\\Users.json";
	create_path(local_path + lp);
	rapidjson::Document d2;
	get_data(lp, &d2);

	return d2;
}

rapidjson::Document Database::get_user(int user_id) {
	char u_id[20];
	itoa(user_id, u_id, 10);

	std::string path = "\\Users\\", lp;
	path += u_id;

	lp = path + "\\Username.json";
	rapidjson::Document data1;
	get_data(lp, &data1);

	lp = path + "\\Password.json";
	rapidjson::Document data2;
	get_data(lp, &data2);

	lp = path + "\\Conversations.json";
	create_path(local_path + lp);
	rapidjson::Document data3;
	get_data(lp, &data3);
	
	User us(string_unparce(&data1), string_unparce(&data2), user_id);
	us.change_dialogs_ID(array_unparce(&data3));

	return us.user_parce();
}