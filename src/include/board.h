#pragma once
#ifndef __H_TRIANGLE_BOARD__
#define __H_TRIANGLE_BOARD__

#include <vector>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "include/peg.h"

#define EMPTY_PEG -1


namespace TriangleGame {

	class board {
		public:
			board(int height);

			int getTotalPegs();
			int getTotalRemovedPegs();

			bool getPeg(int row, int index, peg& p);
			bool getPeg(int pegNumber, peg& p);
			
			bool addPeg(int row, int index);
			bool addPeg(int pegNumber);
			bool addPeg(peg p);

			bool removePeg(int row, int index);
			bool removePeg(int pegNumber);
			bool removePeg(peg p);
			

			bool isPegRemoved(int pegNumber);

			void movePeg(peg fromPeg, peg toPeg);
			void movePeg(int fromPeg, int toPeg);

			//std::vector<peg> getMoves(int pegNumber);

			std::string to_string();

			friend std::ostream& operator<<(std::ostream& os, board& b);

		private:
			void _init_pegs();
			
			void _build_move_list(peg p, std::vector<peg>& moves);

			bool _validate(int row, int index);

			int _height;
			int _total_pegs;
			std::vector<std::vector<peg>> _pegs;
			int _total_pegs_removed;

	};

}

#endif