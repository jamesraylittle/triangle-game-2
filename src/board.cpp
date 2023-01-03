#include "include/board.h"

namespace TriangleGame {

	board::board(int height)
		: _height(height) 
		{
			_total_pegs = _get_last_peg_number(height);
			_pegs_removed = 0;
			_init_pegs();
		}

	int board::getTotalPegs() {
		return _total_pegs;
	}

	int board::getTotalRemovedPegs() {
		return _pegs_removed;
	}

	void board::removePeg(int pegNumber) {
		int row, index;
		_locate_peg(pegNumber, row, index);
		_pegs[row][index] = EMPTY_PEG;
		_pegs_removed++;
	}

	std::vector<int> board::getMoves(int pegNumber) {
		int row, index;
		_locate_peg(pegNumber, row, index);
		auto moves = std::vector<int>();

		bool pegAtStart = index == 0;
		bool pegAtEnd = index == (_pegs[row].size() - 1);

		if (_pegs[row].size() > 2) {
			if (index == 0)
				moves.push_back(_pegs[row][index + 2]);
			else 
				moves.push_back(_pegs[row][index - 2]);
		}

		if (row - 2 >= 0) {
			auto above = _pegs[row - 2];

			if (pegAtStart || pegAtEnd) {
				moves.push_back(above[0]);
			} else {
				moves.push_back(above[above.size() - 1]);
			}

		}

		if (row + 2 < _height) {
			auto below = _pegs[row + 2];
			if (pegAtEnd) { 
				moves.push_back(below[below.size() - index - 1]);
				moves.push_back(below[below.size() - 1]);
			} else if (pegAtStart) {
				moves.push_back(below[0]);
				moves.push_back(below[index + 2]);
			} else {
				moves.push_back(below[index]);
				moves.push_back(below[index + 2]);
			}
				
			
			
		}

		return moves;
	}

	std::string board::to_string() {
		std::stringstream ss;

		
		for (int row = 0; row < _height; row++) {

			//print spaces
			ss << std::left << std::setw(_height * (_height - row)) << " "; 
			
			auto pos = _pegs[row];
			for (int i = 0; i < pos.size(); i++) {

				ss << std::left << std::setw(_height * 2);
				

				if (pos[i] == EMPTY_PEG) { 
					ss << EMPTY_PEG_STR;
					continue;
				}	
				ss << pos[i];
			}


			ss << std::endl << std::endl;

		}
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& os, board& b) {
		os << b.to_string();
		return os;
	}


	//PRIVATE
	void board::_init_pegs() {
		for (int row = 0; row < _height; row++) {
			auto row_p = std::vector<int>();

			int e_pos = _get_last_peg_number(row + 1);
			int s_pos = e_pos - row;

			for (int i = s_pos; i <=  e_pos; i++) 
				row_p.push_back(i);

			_pegs.push_back(row_p);

		}

	}

	int board::_get_last_peg_number(int row) {
		return (row * (row + 1)) / 2;
	}

	void board::_locate_peg(int pegNumber, int& row, int& index) {
		int rl = 0;
		for (int i = 0; i < _height; i++) {
			rl = _get_last_peg_number(i + 1);

			if (pegNumber <= rl) {
				row = i;
				break;
			}

		}

		index = pegNumber - ( rl - row + 1) + 1;
	}


} 