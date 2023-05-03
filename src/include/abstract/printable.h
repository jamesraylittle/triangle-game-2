/**
 * @file printable.h
 * @author James Little <jlittle@brandonclark.com>
 * @brief Abstract class that provides a to_string method, and an overloaded
 * operator<< for derived classes.
 * @version 0.1
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef __H_TRIANGLE_ABSTRACT_PRINTABLE__
#define __H_TRIANGLE_ABSTRACT_PRINTABLE__

#include <string>
#include <ostream>

namespace TriangleGame::abstract {
	/**
	 * @brief Abstract class that provides a to_string method, and an overloaded
	 * operator<< for derived classes. 
	 * 
	 * Aimed to be used for printing derived classes.
	 * 
	 */
	class printable {
		public:
			/**
			 * @brief A pure virtual function of converting the object to a string,
			 * used by the friend method, operator<<.
			 * 
			 * @return std::string A string representing the derived class.
			 */
			virtual std::string to_string() const noexcept = 0;

			/**
			 * @brief Overloaded operator<< that calls the to_string method from
			 * the printable derived class.
			 * @param os The output stream object.
			 * @param p The printable derived class.
			 * @return std::ostream& The output stream
			 */
			friend std::ostream& operator<<(std::ostream& os, const printable& p) {
				os << p.to_string();
				return os;
			}


	};
}

#endif