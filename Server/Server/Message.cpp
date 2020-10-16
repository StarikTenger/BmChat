#include "Message.h"

Message::Message(){}
Message::Message(std::string _text, int _dialog_ID, int _user_ID, int _message_ID) {
	text = _text;
	dialog_ID = _dialog_ID;
	user_ID = _user_ID;
	message_ID = _message_ID;
}

rapidjson::Document Message::message_parce()
{
	std::string ans = "[";
	
	for (int i = 0; i < 3; i++) {
		int k;
		switch (i) {
		case 0: k = message_ID;
			break;
		case 1: k = dialog_ID;
			break; 
		case 2: k = user_ID;
			break;
		}
		char buff[5];
		itoa(k, buff, 10);
		ans += buff;
		ans += ',';
	}

	for (int i = 0; i < text.size(); i++) {
		int k = text[i];
		char buff[5];
		itoa(k, buff, 10);
		ans += buff;
		ans += ',';
	}
	ans[ans.size() - 1] = ']';

	rapidjson::Document doc;
	rapidjson::StringStream s(ans.c_str());
	doc.ParseStream(s);
	return doc;
}

void Message::message_unparce(rapidjson::Document* d)
{
	int k = 0;
	for (auto i = (*d).GetArray().Begin(); i != (*d).GetArray().End(); i++) {
		switch (k) {
		case 0: message_ID = (int)i->GetInt();
			break;
		case 1: dialog_ID = (int)i->GetInt();
			break;
		case 2: user_ID = (int)i->GetInt();
			break;
		}
		if (k > 2)
			text += (char)i->GetInt();
		k++;
	}
}

int Message::get_message_ID() {
	return message_ID;
}
int Message::get_dialog_ID() {
	return dialog_ID;
}
int Message::get_user_ID() {
	return user_ID;
}
std::string Message::get_text() {
	return text;
}

void Message::set_message_ID(int _message_ID) {
	message_ID = _message_ID;
}
void Message::set_dialog_ID(int _dialog_ID) {
	dialog_ID = _dialog_ID;
}
void Message::set_user_ID(int _user_ID) {
	user_ID = _user_ID;
}
void Message::set_text(std::string _text) {
	text = _text;
}