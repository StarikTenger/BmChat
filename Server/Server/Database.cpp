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

void Database::create_user(std::string username, std::string password, int user_id) {

}

void Database::create_conversation(int user_id, std::string password, std::string conversation_name, int conversation_id) {

}

void Database::add_member(int conversation_id, int user_id) {

}

void Database::add_message(int user_id, std::string password, int conversation_id) {

}

rapidjson::Document Database::get_message(int conversation_id, int message_id) {

}

rapidjson::Document Database::get_members(int conversation_id) {

}

rapidjson::Document Database::get_user(int user_id) {

}

void Database::create_path(std::string path) {

}

int Database::check_password(std::string username, std::string password) {

}

int Database::set_data(std::string path, rapidjson::Document data) {

}

std::pair<int, rapidjson::Document> Database::get_data(std::string path) {

}