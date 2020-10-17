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
#include "Database.h"

class Network_database
{
public:
	Network_database();
	Network_database(Database* _database);
private:
	Database *database;
};

