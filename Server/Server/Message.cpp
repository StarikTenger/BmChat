#include "Message.h"

Message::Message(){}
Message::Message(std::string _text, int _dialog_ID, int _user_ID, int _message_ID) {
	text = _text;
	dialog_ID = _dialog_ID;
	user_ID = _user_ID;
	message_ID = _message_ID;
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