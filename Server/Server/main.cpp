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
#include "Message.h"

int main() {
        /*                       ***Full Database test***
        Database d("C:\\Users\\mea25\\Desktop\\yu");
        int uid = d.new_user_ID(), cid = d.new_conversation_id(), uid2 = d.new_user_ID();
        d.create_user("Admin", "admin", uid);
        d.create_user("User", "user", uid2);
        User us, us2;
        rapidjson::Document doc = d.get_user(uid);
        us.user_unparce(&doc);
        doc = d.get_user(uid2);
        us2.user_unparce(&doc);
        d.create_conversation(us.get_user_ID(), "admin", "Development", cid);
        d.add_member(cid, uid2);
        d.add_message(us.get_user_ID(), "ain", cid, d.new_message_id(cid), "Hello im hacker");
        int mess_id = d.new_message_id(cid);
        d.add_message(us.get_user_ID(), "admin", cid, mess_id, "Hello world!!!");
        rapidjson::Document x = d.get_members(cid);
        for (auto i = x.Begin(); i != x.End(); i++)
            std::cout << i->GetInt() << " ";
        std::cout << "\n";
        Message k;
        k.message_unparce(&(d.get_message(cid, mess_id)));
        std::cout << k.get_dialog_ID() << " " << k.get_message_ID() << "\n" << k.get_text() << "\n" << k.get_user_ID() << "\n";*/

    return 0;
}