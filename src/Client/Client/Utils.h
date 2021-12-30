#pragma once
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>

using namespace std;

const string serverUrl = "http://localhost:5276/api";
const string serverStatsUrl = "";

string getOrderStatus(int status);

string getDishType(int type);

string sha256(const string str);