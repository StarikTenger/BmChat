#define _CRT_NONSTDC_NO_DEPRECATE
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <rapidjson.h>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include "Database.h"
#include "User.h"

int main() {
    Database d("C:\\Users\\mea25\\Desktop\\yu");
    int uid = d.new_user_ID(), cid = d.new_conversation_id(), uid2 = d.new_user_ID();
    d.create_user("Admin", "admin", uid);
    d.create_user("User", "user", uid2);
    User us("", "", uid), us2("", "", uid2);
    rapidjson::Document doc = d.get_user(uid);
    us.user_unparce(&doc);
    doc = d.get_user(uid2);
    us2.user_unparce(&doc);
    d.create_conversation(us.get_user_ID(), "admin", "Development", cid);
    d.add_member(cid, uid2);
    d.add_message(us.get_user_ID(), "ain", cid, 0, "Hello im hacker");
    d.add_message(us.get_user_ID(), "admin", cid, 0, "Hello world!!!");
    return 0;
}