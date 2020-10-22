#include "Database.h"

Database::Database() {}

Database::Database(std::string _local_path) {
	local_path = _local_path;
	max_user_id = 0;
	max_conversation_id = 0;
}

std::string Database::get_ASCII_string(std::string str) {
	std::string ans;
	for (int i = 0; i < str.size(); i++)
	{
		char buff[5];
		itoa(str[i], buff, 10);
		ans += buff;
		ans += 'p';
	}
	return ans;
}

int Database::new_user_ID() {
	return max_user_id++;
}

int Database::new_conversation_id() {
	return max_conversation_id++;
}

std::string Database::set_parce(std::set<int> *v) {
	std::string ans = "[";
	for (auto i = (*v).begin(); i != (*v).end(); i++) {
		char buff[5];
		itoa(*i, buff, 10);
		ans += buff;
		ans += ',';
	}
	ans[ans.size() - 1] = ']';
	return ans;
}

std::set <int> Database::set_unparce(rapidjson::Document *d) {
	std::set<int> ans;
	if (!((*d).IsArray()))
		return ans;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		ans.insert(i->GetInt());
	}
	return ans;
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
	path += "\\Password.json";
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

	lp = path +"\\Username.json";
	rapidjson::Document data;
	username = string_parce(username);
	rapidjson::StringStream s(username.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	rapidjson::Document data2;
	lp = path + "\\Password.json";
	password = string_parce(password);
	rapidjson::StringStream s2(password.c_str());
	data2.ParseStream(s2);
	set_data(lp, &data2);

	rapidjson::Document data3;
	lp = "\\Users\\IDs\\" + get_ASCII_string(username) + ".json";
	std::string num = "[";
	num += u_id;
	num += "]";
	rapidjson::StringStream s3(num.c_str());
	data3.ParseStream(s3);
	set_data(lp, &data3);
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
	std::set<int> conversations_list = set_unparce(&d);
	conversations_list.insert(conversation_id);
	rapidjson::Document data;
	std::string parced = set_parce(&conversations_list);
	rapidjson::StringStream s(parced.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	path = "\\Conversations\\";
	lp = path + c_id + "\\Users.json";
	create_path(local_path + lp);
	rapidjson::Document d2;
	get_data(lp, &d2);
	std::set<int> users_list = set_unparce(&d2);
	users_list.insert(user_id);
	rapidjson::Document data2;
	std::string parced2 = set_parce(&users_list);
	rapidjson::StringStream s2(parced2.c_str());
	data2.ParseStream(s2);
	set_data(lp, &data2);
}

void Database::create_conversation(int user_id, std::string password, std::string conversation_name, int conversation_id) {
	if (check_password(user_id, password) == 0)
		return;

	char c_id[20];
	itoa(conversation_id, c_id, 10);
	std::string path = "\\Conversations\\", lp;
	path += c_id;

	lp = path + "\\Max_message_id.json";
	rapidjson::Document d;
	std::string num = "[0]";
	rapidjson::StringStream s1(num.c_str());
	d.ParseStream(s1);
	set_data(lp, &d);

	lp = path + "\\Conversation_name.json";
	rapidjson::Document data;
	conversation_name = string_parce(conversation_name);
	rapidjson::StringStream s(conversation_name.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	add_member(conversation_id, user_id);
}

int Database::new_message_id(int conversation_id) {
	char c_id[20];
	itoa(conversation_id, c_id, 10);
	std::string path = "\\Conversations\\", lp;
	path += c_id;

	lp = path + "\\Max_message_id.json";
	rapidjson::Document d;
	std::vector<int> ans = { 0 };
	if (get_data(lp, &d))
		ans = array_unparce(&d);
	ans[0]++;
	std::string arr = array_parce(&ans);
	rapidjson::StringStream s(arr.c_str());
	d.ParseStream(s);
	set_data(lp, &d);
	return ans[0] - 1;
}

int Database::add_message(int user_id, std::string password, int conversation_id, int message_id, std::string text) {
	if (check_password(user_id, password) == 0)
		return 0;

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
	return 1;
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
	
	User us(string_unparce(&data1), string_unparce(&data2), user_id, NULL, set_unparce(&data3));
	return us.user_parce();
}

int Database::change_username(int user_id, std::string _password, std::string _new_username) {
	char u_id[20];
	itoa(user_id, u_id, 10);

	rapidjson::Document d;
	std::string path = "\\Users\\", lp;
	path += u_id;

	if (!check_password(user_id, _password))
		return 0;

	rapidjson::Document data1, data2, data3;

	lp = path + "\\Username.json";
	get_data(lp, &data3);
	std::string username = string_unparce(&data3);

	std::string path1;
	path1 += "\\Users\\IDs\\" + get_ASCII_string(username) + ".json";
	std::string path2;
	path2 += "\\Users\\IDs\\" + get_ASCII_string(_new_username) + ".json";
	std::string num = "[-1]";
	num = string_parce(num);
	rapidjson::StringStream s1(num.c_str());
	data2.ParseStream(s1);
	get_data(path1, &data1);
	set_data(path1, &data2);
	set_data(path2, &data1);

	rapidjson::Document data;
	_new_username = string_parce(_new_username);
	rapidjson::StringStream s(_new_username.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	return 1;
}

int Database::change_password(int user_id, std::string password, std::string new_pass) {
	char u_id[20];
	itoa(user_id, u_id, 10);

	rapidjson::Document d;
	std::string path = "\\Users\\", lp;
	path += u_id;

	if (!check_password(user_id, password))
		return 0;

	lp = path + "\\Password.json";
	rapidjson::Document data;
	new_pass = string_parce(new_pass);
	rapidjson::StringStream s(new_pass.c_str());
	data.ParseStream(s);
	set_data(lp, &data);
	
	return 1;
}

int Database::delete_member(int user_id, std::string password, int conversation_id) {
	char u_id[20], c_id[20];
	itoa(conversation_id, c_id, 10);
	itoa(user_id, u_id, 10);

	if (!check_password(user_id, password))
		return 0;

	std::string path = "\\Users\\", lp;
	lp = path + u_id + "\\Conversations.json";
	create_path(local_path + lp);
	rapidjson::Document d;
	get_data(lp, &d);
	std::set<int> conversations_list = set_unparce(&d);
	conversations_list.erase(conversation_id);
	rapidjson::Document data;
	std::string parced = set_parce(&conversations_list);
	rapidjson::StringStream s(parced.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	path = "\\Conversations\\";
	lp = path + c_id + "\\Users.json";
	create_path(local_path + lp);
	rapidjson::Document d2;
	get_data(lp, &d2);
	std::set<int> users_list = set_unparce(&d2);
	users_list.erase(user_id);
	rapidjson::Document data2;
	std::string parced2 = set_parce(&users_list);
	rapidjson::StringStream s2(parced2.c_str());
	data2.ParseStream(s2);
	set_data(lp, &data2);
	return 1;
}

int Database::get_user_id(std::string username) {
	rapidjson::Document data;
	std::string path = "\\Users\\IDs\\";
	path += get_ASCII_string(username) + ".json";
	if (get_data(path, &data) == 0)
		return -1;
	return array_unparce(&data)[0];
}

rapidjson::Document Database::login(std::string username, std::string password) {
	int id = get_user_id(username);
	rapidjson::Document d;

	std::cout << "\n**" << id << "**\n";

	if (id == -1 || check_password(id, password) == 0)
		return d;

	std::cout << "\n**" << id << "**\n";
	return get_user(id);
}