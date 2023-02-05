#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <netdb.h>
#include <unistd.h>
#include "data.h"

extern Data gData;

bool check(const std::string& str);
void replace_even(std::string& str);
int sum_odds(const std::string& str);
void* prepare_data(void*);
void* process_data(void*);

#endif