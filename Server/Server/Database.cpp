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
	
	char writeBuffer[65536];
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
	const char* buff = doc.GetString();
	std::string pass = buff;
	return (pass == password);
}

void Database::create_user(std::string username, std::string password, int user_id) {
	char u_id[20];
	itoa(user_id, u_id, 10);
	std::string path = "\\Users\\", lp;
	path += u_id;

	lp = path +"\\username.json";
	rapidjson::Document data;
	username = "[" + username + "]";
	rapidjson::StringStream s(username.c_str());
	data.ParseStream(s);
	set_data(lp, &data);

	rapidjson::Document data2;
	lp = path + "\\password.json";
	rapidjson::StringStream s2(password.c_str());
	data2.ParseStream(s2);
	set_data(lp, &data2);

}

//void Database::create_conversation(int user_id, std::string password, std::string conversation_name, int conversation_id) {
//
//}
//
//void Database::add_member(int conversation_id, int user_id) {
//
//}
//
//void Database::add_message(int user_id, std::string password, int conversation_id) {
//
//}
//
//rapidjson::Document Database::get_message(int conversation_id, int message_id) {
//
//}
//
//rapidjson::Document Database::get_members(int conversation_id) {
//
//}
//
//rapidjson::Document Database::get_user(int user_id) {
//
//}