#pragma once
#include "Message.h"
#include <vector>

class Dialog {
	std::string name = "";

	int dialog_ID = 0;
	std::vector<int> messages_ID; // All messages in order

};

