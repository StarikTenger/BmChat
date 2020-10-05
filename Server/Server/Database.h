#pragma once
#include <SFML/Network.hpp>
#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <string>

class Database {
public:
	Database();
	Database(std::string local_path);
	int check_password(std::string username, std::string password);
	int set_data(std::string path, rapidjson::Document data);
	std::pair<int, rapidjson::Document> get_data(std::string path);
private:
	std::string local_path; // path to server folder (any request to the system forms as request(local_path+path ...))
	void create_path(std::string path);//if path doesn't exist create path
};