/**
 * @file util.h
 * @author James Little <james@jameslittle.org>
 * @brief The file serves as a general utility header for the game, and its libraries. 
 * @version 0.1
 * @date 2023-04-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef __H_TRI_GAME_UTIL__
#define __H_TRI_GAME_UTIL__

#include <iostream>
#include <sstream>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include <ios>
#include <cctype>

namespace util {

	/**
	 * @brief Contains functions used to validate user input.
	 * 
	 */
	namespace validation_funcs {

		/**
		 * @brief Checks if a number is within a range
		 * A number is range if it is greater than or equal to the minimum, 
		 * and less than or equal to the maximum.
		 * 
		 * @param input The number to check
		 * @param min The minimum value
		 * @param max The maximum value
		 * @return true If the number is in range
		 * @return false If the number is not in range
		 */
		bool check_range(int input, int min, int max) {
			return input >= min && input <= max;
		}

		/**
		 * @brief Checks if a number is in a list.
		 * 
		 * @param input The number to check, the needle
		 * @param v The list to check, the haystack
		 * @return true If the number is in the list
		 * @return false If the number is not in the list
		 */
		bool in_list(int input, const std::vector<int>& v) {
			for (const auto& e : v) {
				if (e == input)
					return true;
			}
			return false;
		}

		/**
		 * @brief Checks if a character is the same as the trueChar, or the falseChar.
		 * 
		 * @param input The character to check
		 * @param trueChar The character that represents the true value
		 * @param falseChar The character that represents the false value
		 * @return true If the character is a binary value
		 * @return false If the character is not a binary value
		 */
		bool is_binary(char input, char trueChar, char falseChar) {
			return input == trueChar || input == falseChar;
		}

	}

	/**
	 * @brief Creates a string representation of a vector.
	 * 
	 * @tparam T The type of the elements in the vector
	 * @param v The vector to convert to a string
	 * @return std::string The string representation of the vector
	 */
	template <typename T>
	std::string vector_to_str(const std::vector<T>& v) {
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

	/**
	 * @brief Clears the cin buffer, and ignores the rest of the line.
	 * 
	 */
	void cin_clear_ignore() {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	/**
	 * @brief Asks the user a question, via std::cout,
	 * then executes the isValid function on the input.
	 * 
	 * If the input is invalid, then the question is asked again,
	 * until a valid input is given.
	 * 
	 * @tparam T The type of the expected input from the user.
	 * @param question The question to ask the user
	 * @param isValid The function used to validate the input from the user.
	 * @return T The valid input from the user.
	 * @see ask_for_number
	 */
	template <typename T>
	T ask_user(const std::string& question, std::function<bool(T)> isValid) {
		T input;
		do {
			std::cout << question << ": ";
			if (std::cin >> input) {
				if (isValid(input))
					break;
			}
			cin_clear_ignore();

		} while (true);
		
		return input;
	}

	/**
	 * @brief Asks the user for a number, within a range.
	 * 
	 * @param question The question to ask the user
	 * @param min The minimum value
	 * @param max The maximum value
	 * @return int The valid input from the user
	 * @see ask_user
	 * @see ask_for_number
	 * @see validation_funcs::check_range
	 */
	int ask_for_number(const std::string& question, int min = INT_MIN, int max = INT_MAX) {
		std::stringstream ss;

		ss << question << " [" << min << "-" << max << "]";

		return ask_user<int>(ss.str(), [min, max](int input) -> bool {
			return validation_funcs::check_range(input, min, max);
		});
		
	}

	/**
	 * @brief Asks the user for a number, that is within a list.
	 * 
	 * @param question The question to ask the user
	 * @param list The list of valid numbers
	 * @return int The valid input from the user
	 * @see ask_user
	 * @see ask_for_number
	 * @see validation_funcs::in_list
	 */
	int ask_for_number(const std::string& question, const std::vector<int>& list) {
		std::stringstream ss;

		ss << question << " " << vector_to_str(list);

		return ask_user<int>(ss.str(), [list](int input) -> bool {
			return validation_funcs::in_list(input, list);
		});
	}

	/**
	 * @brief Asks the user a yes or no question.
	 * 
	 * @param question The question to ask the user
	 * @param yesChar The character that represents the true, or Yes value
	 * @param noChar The character that represents the false, or No value
	 * @return true If the user answered yes
	 * @return false If the user answered no
	 * @see ask_user
	 * @see validation_funcs::is_binary
	 */
	bool ask_yes_no(const std::string& question, char yesChar = 'y', char noChar = 'n') {
		std::stringstream ss;
		ss << question << " [y/n]";

		char lowerY = tolower(yesChar);
		char lowerN = tolower(noChar);

		auto response = ask_user<char>(ss.str(), [lowerY, lowerN](char input) -> bool {
			return validation_funcs::is_binary(tolower(input), lowerY, lowerN);
		});

		return tolower(response) == lowerY;
	}

}


#endif