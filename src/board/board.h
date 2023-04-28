/**
 * @file board.h
 * @author James Little <james@jameslittle.org>
 * @brief This file contains the board class, which represents the game board.
 * @version 0.1
 * @date 2023-04-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifndef __H_TRIANGLE_BOARD__
#define __H_TRIANGLE_BOARD__

#include <vector>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>

#include "peg.h"

#define EMPTY_PEG -1 //!< The number representation of an empty peg


namespace TriangleGame {

	typedef std::vector<int> t_moves; //!< A list of moves a peg can make
	typedef std::map<int, t_moves> t_open_moves; //!< A map of peg numbers to a list of moves that peg can make
	typedef std::vector<std::vector<peg> > t_board; //!< A 2D vector of pegs, representing the game board

	/**
	 * @brief The Board Class, represents the game board.
	 * The game board is a triangle, with each row having one more peg than the last.
	 * The height of the board is the number of rows the game board has.
	 * 
	 * The board is first created with all pegs filled, the user then selects the intital peg to
	 * be removed. The game is then played by moving pegs to empty spaces, removing the peg that
	 * was jumped over.
	 * 
	 * A Peg can only jump over another peg if the peg being jumped over is not removed.
	 * The game is over when there are no remaning moves left.
	 * 
	 */
	class board {
		public:
			/**
			 * @brief Construct a new board object with the given height.
			 * 
			 * @param height The height of the board, the number of rows.
			 */
			board(int height);

			/**
			 * @brief Returns the Total Pegs the board has.
			 * The total number of pegs depends on the board height.
			 * 
			 * @return int The total number of pegs.
			 */
			int get_total_pegs();

			/**
			 * @brief Returns the Total Pegs Removed from the board.
			 * 
			 * @return int The total number of pegs removed.
			 */
			int get_total_removed_pegs();

			/**
			 * @brief Returns the height of the board.
			 * 
			 * @return int The height of the board.
			 */
			int get_height();

			/**
			 * @brief Get the Peg object from the given row and index.
			 * If the input parameters row, or index is invalid
			 * then false is returned.
			 * 
			 * @param row The row to get the peg from.
			 * @param index The index to get the peg from.
			 * @param p The peg to return.
			 * @return true If the row, and index values are valid.
			 * @return false If the row, and index values are invalid or out of range.
			 * @see get_peg(int pegNumber, peg& p)
			 */
			bool get_peg(int row, int index, peg& p);

			/**
			 * @brief Get the Peg object from the given peg number.
			 * If the input parameter, peg number, is invalid
			 * then false is returned.
			 * 
			 * @param pegNumber The peg number to get the peg from.
			 * @param p The peg to return.
			 * @return true If the peg number is valid
			 * @return false If the peg number is invalid or out of range.
			 * @see get_peg(int row, int index, peg& p)
			 */
			bool get_peg(int pegNumber, peg& p);
			
			/**
			 * @brief Add a peg to the board at the given row and index.
			 * If the input parameters row, or index is invalid then
			 * false is returned. If a peg already exists at the given
			 * row and index then false is returned.
			 * @param row The row to add the peg to.
			 * @param index The index to add the peg to.
			 * @return true If the peg was added successfully.
			 * @return false If the peg was not added successfully.
			 * @see add_peg(int pegNumber)
			 * @see add_peg(const peg& p)
			 */
			bool add_peg(int row, int index);

			/**
			 * @brief Add a peg to the board at the given peg number.
			 * The row and index of the peg is calculated from the peg number.
			 * Then an attempt to add the peg to the board is made.
			 * 
			 * @param pegNumber The peg number to add the peg to.
			 * @return true If the peg was added successfully.
			 * @return false If the peg was not added successfully.
			 * @see add_peg(int row, int index)
			 * @see add_peg(const peg& p)
			 */
			bool add_peg(int pegNumber);

			/**
			 * @brief Adds the given peg to the board at the
			 * given peg's row and index.
			 * 
			 * @param p The peg to be added to the board.
			 * @return true If the peg was added successfully.
			 * @return false If the peg was not added successfully.
			 * @see add_peg(int row, int index)
			 * @see add_peg(int pegNumber)
			 */
			bool add_peg(const peg& p);

			/**
			 * @brief Removes the peg from the board at the given row and index.
			 * If the peg has not already been removed then True is returned,
			 * otherwise False is returned.
			 * 
			 * @param row The row to remove the peg from.
			 * @param index The index to remove the peg from.
			 * @return true If the peg was removed successfully.
			 * @return false If the peg was not removed successfully.
			 * @see remove_peg(int pegNumber)
			 * @see remove_peg(const peg& p)
			 */
			bool remove_peg(int row, int index);

			/**
			 * @brief Removes the peg from the board at the given peg number.
			 * The row and index of the peg is calculated from the peg number.
			 * If the peg has not already been removed then True is returned,
			 * otherwise False is returned.
			 * 
			 * @param pegNumber The peg number of the peg to remove.
			 * @return true If the peg was removed successfully.
			 * @return false If the peg was not removed successfully.
			 * @see remove_peg(int row, int index)
			 * @see remove_peg(const peg& p)
			 */
			bool remove_peg(int pegNumber);

			/**
			 * @brief Removes the given peg from the board, at the 
			 * given peg's row and index.
			 * If the peg has not already been removed then True is returned,
			 * otherwise False is returned.
			 * 
			 * @param p The peg to remove from the board.
			 * @return true If the peg was removed successfully.
			 * @return false If the peg was not removed successfully.
			 */
			bool remove_peg(const peg& p);
			
			/**
			 * @brief Determinds if the given fromPeg is able to move to the given
			 * toPeg. A valid move is one where the fromPeg is not missing, the toPeg is missing, 
			 * and the fromPeg and toPeg are adjacent and the middle peg is removed.
			 * 
			 * @param fromPeg The peg to move to the toPeg.
			 * @param toPeg The peg where the fromPeg is to be moved to.
			 * @return true If the move is valid.
			 * @return false If the movie is invalid.
			 * @see move_peg(const peg& fromPeg, const peg& toPeg)
			 * @see move_peg(int fromPegNumber, int toPegNumber)
			 */
			bool validate_move(const peg& fromPeg, const peg& toPeg);

			/**
			 * @brief Given a valid peg number, determinds if the peg is missing.
			 * 
			 * @param pegNumber The number of the peg, to check if it is missing.
			 * @return true If the peg is missing.
			 * @return false If the peg is not missing.
			 */
			bool is_peg_removed(int pegNumber);

			/**
			 * @brief Moves the given fromPeg to the toPeg.
			 * The move is first validated, if the move is valid then
			 * the move operation is preformed and true is returned.
			 * 
			 * If the move is invalid then false is returned.
			 * 
			 * @param fromPeg The peg to move to the toPeg.
			 * @param toPeg The peg where the fromPeg is to be moved to.
			 * @return true If the move was successful.
			 * @return false If the move was unsuccessful.
			 * @see validate_move(const peg& fromPeg, const peg& toPeg)
			 * @see move_peg(int fromPegNumber, int toPegNumber)
			 */
			bool move_peg(const peg& fromPeg, const peg& toPeg);

			/**
			 * @brief Moves the given fromPeg number to the toPeg number.
			 * The move is first validated, if the move is valid then
			 * the move operation is preformed and true is returned.
			 * 
			 * If the move is invalid then false is returned.
			 * 
			 * @param fromPeg The peg number to move to the toPeg number.
			 * @param toPeg The peg number where the fromPeg is to be moved to.
			 * @return true If the move was successful.
			 * @return false If the move was unsuccessful.
			 * @see validate_move(const peg& fromPeg, const peg& toPeg)
			 * @see move_peg(const peg& fromPeg, const peg& toPeg)
			 */
			bool move_peg(int fromPegNumber, int toPegNumber);

			/**
			 * @brief Returns all the legal, avaliable moves left on the board.
			 * 
			 * @return t_open_moves The avaliable moves left on the board.
			 * @see t_open_moves
			 * @see get_moves(const peg& toPeg)
			 */
			t_open_moves get_all_moves();

			/**
			 * @brief Returns all the legal, avaliable moves left on the board for
			 * the given peg number.
			 * 
			 * @param toPegNumber The peg number to get the avaliable moves for.
			 * @return t_moves The avaliable moves left on the board for the given peg number.
			 * @see t_moves
			 * @see get_all_moves()
			 */
			t_moves get_moves(const peg& toPegNumber);

			/**
			 * @brief Creates a string representation of the board.
			 * 
			 * @return std::string The string representation of the board.
			 */
			std::string to_string();

			/**
			 * @brief Creates a string representation of the board, then appends
			 * the string to the given ostream.
			 * 
			 * @param os The ostream to append the string representation of the board to.
			 * @param b The board to create the string representation of.
			 * @return std::ostream& The ostream with the string representation of the board appended to it.
			 */
			friend std::ostream& operator<<(std::ostream& os, board& b);

		private:
			int _height; //!< The height of the board.
			int _total_pegs; //!< The total number of pegs on the board.
			t_board _pegs; //!< The board of pegs.
			int _total_pegs_removed; //!< The total number of pegs removed from the board.

			/**
			 * @brief Initializes the board with the given height.
			 * Calculates the total number of pegs on the board, and
			 * initializes the board with the pegs.
			 */
			const void _init_pegs();
			
			/**
			 * @brief Determinds if the move is valid, 
			 * if so, the move is added to the moves vector.
			 * 
			 * @param fromPeg The peg to move from.
			 * @param toPeg The peg to move to.
			 * @param moves The vector of moves to add the move to.
			 */
			const void _add_move(const peg& fromPeg, const peg& toPeg, t_moves& moves);

			/**
			 * @brief Validates that the given row and index are valid.
			 * A row is valid when it is greater than or equal to 0 and less than the height.
			 * A index is valid when it is greater than or equal to 0 and less than or equal to the row.
			 * 
			 * @param row The row to validate.
			 * @param index The index to validate.
			 * @return true If the row and index are valid.
			 * @return false If the row or index are invalid.
			 */
			bool _validate(int row, int index);

			/**
			 * @brief Locates the peg that is in the middle of the given fromPeg and toPeg.
			 * 
			 * @param fromPeg The peg to move from.
			 * @param toPeg The peg to move to.
			 * @param middle The return peg that is in the middle of the fromPeg and toPeg.
			 */
			void _find_middle_peg(const peg& fromPeg, const peg& toPeg, peg& middle);
	};

}

#endif