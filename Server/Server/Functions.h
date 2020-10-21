#pragma once
sf::Packet& operator <<(sf::Packet& packet, rapidjson::Document& doc)
{
	packet << (doc.Size());
	for (auto i = doc.GetArray().Begin(); i != doc.GetArray().End(); i++) {
		packet << (i->GetInt());
	}
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, rapidjson::Document& doc)
{
	int len, k;
	packet >> len;
	std::string arr = "[";
	for (int i = 0; i < len; i++) {
		packet >> k;
		char buff[20];
		itoa(k, buff, 10);
		arr += buff;
		arr += ",";
	}
	arr[arr.size() - 1] = ']';
	rapidjson::StringStream s(arr.c_str());
	doc.ParseStream(s);
	return packet;
}