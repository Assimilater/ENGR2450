#pragma once

#include <string>
#include <vector>

std::vector<std::string> Split(std::string, char);
std::vector<std::string> Split(std::string, const char*);
std::vector<std::string> Split(std::string, std::string);
std::vector<std::string> Split(std::string, std::vector<char>, bool);
