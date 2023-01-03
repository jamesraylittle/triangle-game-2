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

#include "include/peg.h"

#define EMPTY_PEG -1


namespace TriangleGame {

	class board {
		public:
			board(int height);

			int getTotalPegs();
			int getTotalRemovedPegs();
			int getHeight();

			bool getPeg(int row, int index, peg& p);
			bool getPeg(int pegNumber, peg& p);
			
			bool addPeg(int row, int index);
			bool addPeg(int pegNumber);
			bool addPeg(const peg& p);

			bool removePeg(int row, int index);
			bool removePeg(int pegNumber);
			bool removePeg(const peg& p);
			

			bool validateMove(const peg& fromPeg, const peg& toPeg);

			bool isPegRemoved(int pegNumber);

			bool movePeg(const peg& fromPeg, const peg& toPeg);
			bool movePeg(int fromPeg, int toPeg);

			std::map<int, std::vector<int>> getAllMoves();
			std::vector<int> getMoves(const peg& toPeg);

			std::string to_string();

			friend std::ostream& operator<<(std::ostream& os, board& b);

		private:
			const void _init_pegs();
			
			const void _add_move(const peg& fromPeg, const peg& toPeg, std::vector<int>& moves);

			bool _validate(int row, int index);

			void _find_middle_peg(const peg& fromPeg, const peg& toPeg, peg& middle);

			int _height;
			int _total_pegs;
			std::vector<std::vector<peg>> _pegs;
			int _total_pegs_removed;

	};

}

#endif