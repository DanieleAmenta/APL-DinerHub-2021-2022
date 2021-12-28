#pragma once
#include <iostream>
#include <stdio.h>
using namespace std;

const string serverUrl = "http://localhost:5276/api";
const string serverStatsUrl = "";

string getOrderStatus(int status);

string getDishType(int type);