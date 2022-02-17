#pragma once
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <openssl/sha.h>

using namespace std;

const string serverUrl = "http://localhost:5276/api";
const string serverPingUrl = "http://localhost:5276/ping";

const string serverStatsUrl = "http://127.0.0.1:5000";

string getOrderStatus(int status);

string getDishType(int type);

string sha256(const string str);

string currentISO8601TimeUTC();