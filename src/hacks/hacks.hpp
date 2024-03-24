#pragma once

#include <iostream>

class Hacks {
public:
	inline static void setModEnabled(std::string modName, bool enabled) {
		modsEnabled[modName] = enabled;
	};

	inline static bool getModEnabled(std::string modName) {
		return modsEnabled[modName];
	};

private:
	inline static std::map<std::string, bool> modsEnabled{
		{ "noclip-hack", false }
	};
};