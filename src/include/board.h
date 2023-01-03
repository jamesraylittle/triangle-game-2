#pragma once
#ifndef __H_TRIANGLE_BOARD__
#define __H_TRIANGLE_BOARD__

#include <vector>
#include <ostream>
#include <sstream>
#include <string>
#include <iomanip>

#define EMPTY_PEG -1
#define EMPTY_PEG_STR "X"

namespace TriangleGame {

	class board {
		public:
			board(int height);

			int getTotalPegs();
			int getTotalRemovedPegs();

			void removePeg(int pegNumber);
			std::vector<int> getMoves(int pegNumber);

			std::string to_string();

			friend std::ostream& operator<<(std::ostream& os, board& b);

		private:
			void _init_pegs();
			int _get_last_peg_number(int row);
			void _locate_peg(int pegNumber, int& row, int& index);

			int _height;
			int _total_pegs;
			int _pegs_removed;
			std::vector<std::vector<int>> _pegs;

	};

}

#endif