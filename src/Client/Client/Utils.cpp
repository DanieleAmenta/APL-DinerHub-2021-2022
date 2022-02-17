#include "Utils.h"

/**
* Returns the string, based on the order status code
*/
string getOrderStatus(int status) {
	switch (status) {
	case 0: return "Created";
		break;
	case 1: return "Ready to Pickup";
		break;
	case 2: return "Collected";
		break;
	default: return "Unknown";
		break;
	}
}

/**
* Returns the string, based on the dish type
*/
string getDishType(int type) {
	switch (type) {
	case 0: return "Appetizer";
		break;
	case 1: return "First Course";
		break;
	case 2: return "Second Course";
		break;
	case 3: return "Dessert";
		break;
	case 4: return "Drink";
		break;
	default: return "Unknown";
		break;
	}
}

/**
* SHA256 Encoding
*/
string sha256(const string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();
}

string currentISO8601TimeUTC() {
	auto now = chrono::system_clock::now();
	auto itt = chrono::system_clock::to_time_t(now);
	ostringstream ss;
	ss << put_time(gmtime(&itt), "%FT%TZ");
	return ss.str();
}