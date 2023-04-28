/**
 * @file peg.h
 * @author James Little <james@jameslittle.org>
 * @brief This file contains the peg class, which represents a single peg on the board.
 * @version 0.1
 * @date 2023-04-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef __H_TRIANGLE_BOARD_PEG__
#define __H_TRIANGLE_BOARD_PEG__

#include <ostream>
#include <string>
#include <sstream>
#include <cmath>

#define EMPTY_PEG_STR "X" //!< The string representation of an empty peg

namespace TriangleGame {

	/**
	 * @brief Peg Class, a peg is a single piece on the board
	 * a peg can be moved to a different row, and index, or removed
	 * completely from the board.
	 */
	class peg {
		public:
			/**
			 * @brief Construct a new empty peg object
			 * 
			 */
			peg();

			/**
			 * @brief Construct a new peg with the given number 
			 * at the specified row and index.
			 * 
			 * @param number The inital number of the peg
			 * @param row The row of the peg
			 * @param index The index of the peg
			 */
			peg(int number, int row, int index);

			/**
			 * @brief Construct a new peg at the specified row and index.
			 * 
			 * @param row The row of the peg
			 * @param index The index of the peg
			 */
			peg(int row, int index);

			/**
			 * @brief Construct a new peg object with the given number
			 * 
			 * @param number The inital number of the peg.
			 */
			peg(int number);

			/**
			 * @brief Construct a new peg object from another peg object
			 * 
			 * @param p The peg to make a copy from
			 */
			peg(const peg& p);//= delete;

			/**
			 * @brief Returns the inital Peg number.
			 * 
			 * @return int The number of the peg.
			 */
			int get_number() const;

			/**
			 * @brief Returns the current row of the Peg.
			 * 
			 * @return int The row number of the peg.
			 */
			int get_row() const;

			/**
			 * @brief Returns the current index of the Peg.
			 * 
			 * @return int The current index of the peg.
			 */
			int get_index() const;

			/**
			 * @brief Determinds if the peg is currently located
			 * at the beginning of the row.
			 * 
			 * @return true True if the peg is at the beginning of the row.
			 * @return false False otherwise.
			 */
			bool at_begin() const;

			/**
			 * @brief Determinds if the peg is currently located
			 * at the end of the row.
			 * 
			 * @return true True if the peg is at the end of the row.
			 * @return false False otherwise.
			 */
			bool at_end() const;

			/**
			 * @brief Determinds if the peg is currently located
			 * in the middle of row.
			 * 
			 * @return true True if the peg is in the middle of the row.
			 * @return false False otherwise.
			 */
			bool at_middle() const;

			/**
			 * @brief Removes the peg from the board.
			 * The peg can be removed from the board if it is not already.
			 * 
			 * 
			 * @return true True if the peg was able to be removed.
			 * @return false False otherwise.
			 */
			const bool remove();

			/**
			 * @brief Replaces the peg back on the board, 
			 * if it had previously been removed.
			 * 
			 * @return true True if the peg was able to be replaced.
			 * @return false False otherwise.
			 */
			const bool replace();

			/**
			 * @brief Determinds if the peg has been removed from the board.
			 * 
			 * @return true True if the peg has been removed.
			 * @return false False otherwise.
			 */
			bool is_removed() const;

			/**
			 * @brief Creates a string representation of the peg.
			 * Returns the string "X" if the peg has been removed,
			 * otherwise returns the peg number.
			 * 
			 * @return std::string The string representation of the peg.
			 */
			std::string to_string() const;

			/**
			 * @brief Compares the row and index with another peg.
			 * 
			 * @param other The other peg to compare against.
			 * @return true True if the pegs are equal. 
			 * @return false False otherwise.
			 */
			bool operator==(const peg& other) const;

			/**
			 * @brief Compares the row and index with another peg.
			 * 
			 * @param other The other peg to compare against.
			 * @return true True if this peg is less than the other peg.
			 * @return false False otherwise.
			 */
			bool operator<(const peg& other) const;

			/**
			 * @brief Compares the row and index with another peg.
			 * 
			 * @param other The other peg to compare against.
			 * @return true True if this peg is greater than the other peg.
			 * @return false False otherwise.
			 */
			bool operator>(const peg& other) const;

			/**
			 * @brief Compares the row and index with another peg.
			 * 
			 * @param other The other peg to compare against.
			 * @return true True if this peg is greater than or equal to the other peg.
			 * @return false False otherwise.
			 */
			bool operator>=(const peg& other) const;

			/**
			 * @brief Compares the row and index with another peg.
			 * 
			 * @param other The other peg to compare against.
			 * @return true True if this peg is less than or equal to the other peg.
			 * @return false False otherwise.
			 */
			bool operator<=(const peg& other) const;
			
			/**
			 * @brief Creates a string representation of the peg, 
			 * then appends it to the ostream.
			 * 
			 * @param os The ostream to append the string representation to.
			 * @param p The peg to create a string representation of.
			 * @return std::ostream& The ostream with the string representation appended.
			 */
			friend std::ostream& operator<<(std::ostream& os, const peg& p);
			
			/**
			 * @brief Calculates the the last peg number for a given row.
			 * 
			 * @param row The row to calculate the last peg number for.
			 * @return int The last peg number for the given row.
			 */
			static int FindLastPegNumber(int row);

			/**
			 * @brief Calculates the peg number for a given row and index.
			 * 
			 * @param row The row of the peg.
			 * @param index The index of the peg.
			 * @return int The peg number for the given row and index.
			 */
			static int FindPegNumber(int row, int index);

			/**
			 * @brief Calculates the row and index for a given peg number.
			 * 
			 * @param pegNumber The peg number to locate the row and index for.
			 * @param row A reference to the row to be set.
			 * @param index A reference to the index to be set.
			 * @param maxHeight The maximum height of the board.
			 */
			static void LocatePeg(int pegNumber, int& row, int& index, int maxHeight = 5);

		private:
			int _row; //!< The row of the peg.
			int _index; //!< The index of the peg.
			int _number; //!< The peg number.
			bool _atEnd; //!< Flag determinds if the peg is at the end of the row.
			bool _atBegin; //!< Flag determinds if the peg is at the beginning of the row.
			bool _atMiddle; //!< Flag determinds if the peg is in the middle of the row.
			bool _removed; //!< Flag determinds if the peg has been removed.

			/**
			 * @brief Initializes the peg.
			 * Setups the flags for the peg.
			 */
			void _init_peg();
	};

}


#endif