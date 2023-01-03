#include "include/board.h"

namespace TriangleGame {

	board::board(int height)
		: _height(height) 
		{
			_total_pegs = peg::FindLastPegNumber(height);
			_total_pegs_removed = 0;
			_init_pegs();
		}

	int board::getTotalPegs() {
		return _total_pegs;
	}

	int board::getTotalRemovedPegs() {
		return _total_pegs_removed;
	}

	bool board::getPeg(int row, int index, peg& p) {
		if (!_validate(row, index)) return false;
		p = _pegs[row][index];
		return true;
	}

	bool board::getPeg(int pegNumber, peg& p) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index, _height);
		return getPeg(row, index, p);
	}

	bool board::addPeg(int row, int index) {
		//validate
		if (!_validate(row, index)) return false;
		if (!_pegs[row][index].replace()) return false;

		_total_pegs_removed--;
		return true;
	}

	bool board::addPeg(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index, _height);
		return addPeg(row, index);
	}

	bool board::addPeg(peg p) {
		return addPeg(p.getRow(), p.getIndex());
	}

	bool board::removePeg(int row, int index) {
		if (!_validate(row, index)) return false;
		if (!_pegs[row][index].remove()) return false;
			
		_total_pegs_removed++;
		return true;
	}

	bool board::removePeg(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index);
		return removePeg(row, index);
	}

	bool board::removePeg(peg p) {
		return removePeg(p.getRow(), p.getIndex());
	}

	bool board::isPegRemoved(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index);
		return _pegs[row][index].isRemoved();
	}

	void board::movePeg(peg fromPeg, peg toPeg) {

		int dist = fromPeg.getRow() - toPeg.getRow();

		if (dist == 0) { //same row

		} else if (dist > 0) { //fromPeg is jump up to toPeg
			removePeg(fromPeg.getRow() - 1, fromPeg.getIndex());
		} else { //dist < 0: fromPeg is jumping down to toPeg

		}

		removePeg(fromPeg);
		addPeg(toPeg);
	}

	void board::movePeg(int fromPeg, int toPeg) {
		peg f, t;
		getPeg(fromPeg, f);
		getPeg(toPeg, t);
		movePeg(f, t);
	}
/*
	std::vector<peg> board::getMoves(int pegNumber) {
		int row, index;
		_locate_peg(pegNumber, row, index);
		auto moves = std::vector<int>();

		bool pegAtStart = index == 0;
		bool pegAtEnd = index == (_pegs[row].size() - 1);

		if (_pegs[row].size() > 2) {
			if (index == 0)
				_build_move_list(_pegs[row][index + 2], moves);
			else 
				_build_move_list(_pegs[row][index + 2], moves);
		}

		if (row - 2 >= 0) {
			auto above = _pegs[row - 2];

			if (pegAtStart || pegAtEnd) {
				_build_move_list(above[0], moves);
			} else {
				_build_move_list(above[above.size() - 1], moves);
			}

		}

		if (row + 2 < _height) {
			auto below = _pegs[row + 2];
			if (pegAtEnd) { 
				_build_move_list(below[below.size() - index - 1], moves);
				_build_move_list(below[below.size() - 1], moves);
			} else if (pegAtStart) {
				_build_move_list(below[0], moves);
				_build_move_list(below[index + 2], moves);
			} else {
				_build_move_list(below[index], moves);
				_build_move_list(below[index + 2], moves);
			}
				
			
			
		}

		return moves;
	}*/

	std::string board::to_string() {
		std::stringstream ss;

		
		for (int row = 0; row < _height; row++) {

			//print spaces
			ss << std::left << std::setw(_height * (_height - row)) << " "; 
			
			auto pos = _pegs[row];
			for (int i = 0; i < pos.size(); i++) {

				ss << std::left << std::setw(_height * 2);
				
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
			auto row_p = std::vector<peg>();

			int e_pos = peg::FindLastPegNumber(row + 1);
			int s_pos = e_pos - row;

			for (int i = s_pos; i <=  e_pos; i++) 
				row_p.push_back( peg(i, row, (row+1) - (e_pos - i)) );

			_pegs.push_back(row_p);

		}

	}

	void board::_build_move_list(peg p, std::vector<peg>& moves) {
		if (p.isRemoved()) return;

		moves.push_back(p);
	}

	bool board::_validate(int row, int index) {
		if (row < 0 || row >= _height) return false;
		if (index < 0 || index >= (row+1)) return false;

		return true;
	}


} 