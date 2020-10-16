#define _CRT_NONSTDC_NO_DEPRECATE
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <rapidjson.h>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include "Database.h"

int main() {
    Database a("C:\\Users\\mea25\\Desktop\\yu");
    a.create_user("Admin", "admin", a.new_user_ID());
    std::cout << a.check_password(0, "notadmin") << " " << a.check_password(0, "admin");
    return 0;
}