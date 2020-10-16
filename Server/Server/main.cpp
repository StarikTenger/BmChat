#define _CRT_NONSTDC_NO_DEPRECATE
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <rapidjson.h>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include "Database.h"

std::string string_parce(std::string str)
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

std::string string_unparce(rapidjson::Document *d)
{
    std::string ans = "";
    for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
        ans += (char)i->GetInt();
    }
    return ans;
}

int main() {
    /*Database a("C:\\Users\\mea25\\Desktop\\yu");
    a.create_user("Admin", "admin", a.new_user_ID());
    std::cout << a.check_password(0, "not_admin") << " " << a.check_password(0, "admin");*/
    std::string hello = string_parce("Admin");
    const char* json = hello.c_str();
    rapidjson::StringStream s(json);
    rapidjson::Document d;
    d.ParseStream(s);
    hello = string_unparce(&d);
    std::cout << hello;
    return 0;
}