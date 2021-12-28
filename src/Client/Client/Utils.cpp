#include "Utils.h"

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