#pragma once

#include <string>
using std::string;
#include <map>
#include <vector>
using std::vector;

#include <iostream>


class GlobalDescriptionMap {
public:
	std::map<string, string> descs;
	const string at(string) const;
	void add(string key_fullname, string value_mnemonic);
	GlobalDescriptionMap();

	const void printDescriptionMap() const;
};

const class GlobalDescriptionMap GLOBAL_INSTRUCTION_DESCRIPTION_MAP = GlobalDescriptionMap();

