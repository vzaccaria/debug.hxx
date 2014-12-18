#ifndef DEBUG_HXX
#define DEBUG_HXX

#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>
#include <functional>

static auto Debug = [](std::string moduleName) {

	auto h = 0;

	auto use_colors = std::getenv("DEBUG_COLORS");

	if (use_colors == NULL || (
		std::string(use_colors)!= "false" && 
		std::string(use_colors) != "no" && 
		std::string(use_colors) != "disabled")) {
		std::hash<std::string> hash_fn;
		h = hash_fn(moduleName) % 6;
	}

	int colors[] = { 6, 2, 3, 4, 5, 1 };

	return [=](std::string message) {

		auto env = std::getenv("DEBUG");
		bool shouldDebug = false;

		if (env != NULL) {
			std::regex re(env, std::regex_constants::ECMAScript | std::regex_constants::icase);
			if (std::regex_search(moduleName, re)) {
				std::cerr << " \u001b[9" << colors[h] << "m" << moduleName;
				std::cerr << " \u001b[0m" << message << "\u001b[3" << h << "m" << std::endl;
			}
		}
	};
};


#endif // DEBUG_HXX
 
