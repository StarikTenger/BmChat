#pragma once
#include <string>

class Message {
	std::string text = ""; // Text value

	int message_ID = 0; // Own ID
	int dialog_ID = 0; // Dialog ID
	int user_ID = 0; // User ID

public:
	Message();
	Message(std::string _text, int _dialog_ID, int _user_ID, int _message_ID);

	int get_message_ID();
	int get_dialog_ID();
	int get_user_ID();
	std::string get_text();

	void set_message_ID(int _message_ID);
	void set_dialog_ID(int _dialog_ID);
	void set_user_ID(int _user_ID);
	void set_text(std::string _text);
};

