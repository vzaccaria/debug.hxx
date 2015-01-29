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
#include <sstream>
#include <cstdlib>
#include <regex>
#include <functional>
#include <vector>
#include <ctime>
#include <iomanip>
#include <chrono>

static void words(std::string str, std::vector<std::string>& res, const std::string& delim = " ") {
	std::size_t pos = 0;
	while( (pos = str.find(delim)) != std::string::npos) {
		res.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
	}
	res.push_back(str);
}

static const std::string sentence(const std::vector<std::string>& v, std::string delim = " ") {
	std::ostringstream s;
	const std::size_t l = v.size() - 1;
	for(std::size_t x = 0; x < l; ++x) {
		s << v[x] << delim;
	}
	s << v[l];
	return s.str();
}

static auto Debug = [](std::string moduleName) {

	auto h = 0;
	auto debug_colors = std::getenv("DEBUG_COLORS");
	auto debug_time = std::getenv("DEBUG_TIME");

	bool use_colors;
	bool use_time;

	auto name_to_be_hashed = moduleName;

	auto getBool = [](const char *e, bool def) -> bool {
		if(def) {
			return (e == NULL || (
				std::string(e) != "false" &&
				std::string(e) != "no" &&
				std::string(e) != "disabled"));
		} else {
			return (e != NULL && (
				std::string(e) == "true" ||
				std::string(e) == "yes" ||
				std::string(e) == "enabled"));
		}
	};

	use_colors = getBool(debug_colors, true);
	use_time = getBool(debug_time, false);


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
		std::regex star_re("\\*");
		std::string namespace_re = env;

		std::vector<std::string> namespaces;
		words(namespace_re, namespaces, ",");
		for_each(namespaces.begin(), namespaces.end(), [=](std::string & n) {
			n = "^" + n + "$";
		});
		namespace_re = sentence(namespaces, "|");
		namespace_re = std::regex_replace(namespace_re, star_re, ".*");

		std::regex re(namespace_re, std::regex_constants::ECMAScript | std::regex_constants::icase);
		shouldDebug = std::regex_search(moduleName, re);
	}
	return [=](std::string message) {

		int diff = 0;
		if(use_time) {
			auto get_ms = []() -> int {
				using namespace std::chrono;
				return duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch()).count();
			};
			static auto prev = get_ms();
			auto curr = get_ms();
			diff = curr - prev;
			prev = curr;
		}

#define _col_light(c, m) 	("\u001b[9" + std::to_string(c) + "m" + m + " \u001b[0m" )
#define _col_light_ms(c, m) 	("\u001b[9" + std::to_string(c) + "m" + m + "ms \u001b[0m" )


		if (!shouldDebug) { return false; }

		if (!use_colors) {
			std::cerr << " " << moduleName;
			std::cerr << " " << message;
		} else {
			std::cerr << _col_light(colors[h], moduleName);
			std::cerr << message;
		}
		if(use_time) {
			if(use_colors) {
				std::cerr << " +" << _col_light_ms(colors[h], std::to_string((diff))) << std::endl;
			} else {
				std::cerr << " +" << std::to_string((diff)) << "ms" << std::endl;
			}
		} else {
			std::cerr << std::endl;
		}
		return true;
	};
};

#define debugm(msg) Debug(std::string(__FILE__) + ":" + std::to_string(__LINE__))(msg)


#endif // DEBUG_HXX

