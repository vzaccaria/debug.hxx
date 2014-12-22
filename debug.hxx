/*
Copyright (C) 2014 Vittorio Zaccaria

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#ifndef DEBUG_HXX
#define DEBUG_HXX

#include <string>
#include <iostream>
#include <cstdlib>
#include <regex>
#include <functional>

static auto Debug = [](std::string moduleName) {

	auto h = 0;
    auto debug_colors = std::getenv("DEBUG_COLORS");

	bool use_colors;
    
	auto name_to_be_hashed = moduleName;

	if (debug_colors == NULL || (
		std::string(debug_colors) != "false" &&
		std::string(debug_colors) != "no" &&
		std::string(debug_colors) != "disabled")) {
		use_colors = true;
	}
	else {
		use_colors = false;
	}

	if(use_colors) {
		std::hash<std::string> hash_fn;
		if(name_to_be_hashed.find(':') != (std::string::npos)) {
			name_to_be_hashed.erase(name_to_be_hashed.find(':'));
		}
		h = hash_fn(name_to_be_hashed) % 6;
	}

	int colors[] = { 6, 2, 3, 4, 5, 1 };

	auto env = std::getenv("DEBUG");
	bool shouldDebug = false;
	if (env != NULL) {
		std::regex re(env, std::regex_constants::ECMAScript | std::regex_constants::icase);
		shouldDebug = std::regex_search(moduleName, re);
	}
	return [=](std::string message) {
		if (!shouldDebug) { return false; }
		if (!use_colors) {
			std::cerr << " " << moduleName;
			std::cerr << " " << message << std::endl;	
		} else {
			std::cerr << " \u001b[9" << colors[h] << "m" << moduleName;
			std::cerr << " \u001b[0m" << message << "\u001b[3" << h << "m" << std::endl;
		}
		return true;
	};
};

#define debugm(msg) Debug(std::string(__FILE__) + ":" + std::to_string(__LINE__))(msg)


#endif // DEBUG_HXX

