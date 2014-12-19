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

	auto use_colors = std::getenv("DEBUG_COLORS");

	if (use_colors == NULL || (
		std::string(use_colors) != "false" &&
		std::string(use_colors) != "no" &&
		std::string(use_colors) != "disabled")) {
		std::hash<std::string> hash_fn;
		h = hash_fn(moduleName) % 6;
	}

	int colors[] = { 6, 2, 3, 4, 5, 1 };

	return [=](std::string message) {

		auto env = std::getenv("DEBUG");

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

