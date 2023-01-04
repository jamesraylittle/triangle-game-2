#pragma once
#ifndef __H_TRI_GAME_UTIL__
#define __H_TRI_GAME_UTIL__

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include <ios>
#include <cctype>

namespace util {

	namespace validation_funcs {

		bool checkRange(int input, int min, int max) {
			return input >= min && input <= max;
		}

		bool inList(int input, const std::vector<int>& v) {
			for (const auto& e : v) {
				if (e == input)
					return true;
			}
			return false;
		}

		bool isBinary(char input, char trueChar, char falseChar) {
			return input == trueChar || input == falseChar;
		}

	}

	template <typename T>
	std::string vectorToStr(const std::vector<T>& v) {
		std::stringstream ss;
		ss << "[";
		for (int i = 0; i < v.size(); i++) {
			ss << v[i];
			if (i + 1 < v.size())
				ss << ", ";
		}
		ss << "]";
		return ss.str();
	}

	void cinClearIgnore() {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	template <typename T>
	T askUser(const std::string& question, std::function<bool(T)> isValid) {
		T input;
		do {
			std::cout << question << ": ";
			if (std::cin >> input) {
				if (isValid(input))
					break;
			}
			cinClearIgnore();

		} while (true);
		
		return input;
	}

	int askForNumber(const std::string& question, int min = INT_MIN, int max = INT_MAX) {
		std::stringstream ss;

		ss << question << " [" << min << "-" << max << "]";

		return askUser<int>(ss.str(), [min, max](int input) -> bool {
			return validation_funcs::checkRange(input, min, max);
		});
		
	}

	int askForNumber(const std::string& question, const std::vector<int>& list) {
		std::stringstream ss;

		ss << question << " " << vectorToStr(list);

		return askUser<int>(ss.str(), [list](int input) -> bool {
			return validation_funcs::inList(input, list);
		});
	}

	bool askYesNo(const std::string& question, char yesChar = 'y', char noChar = 'n') {
		std::stringstream ss;
		ss << question << " [y/n]";

		char lowerY = tolower(yesChar);
		char lowerN = tolower(noChar);

		auto response = askUser<char>(ss.str(), [lowerY, lowerN](char input) -> bool {
			return validation_funcs::isBinary(tolower(input), lowerY, lowerN);
		});

		return tolower(response) == lowerY;
	}

}


#endif