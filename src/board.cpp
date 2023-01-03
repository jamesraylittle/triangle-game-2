#include "include/board.h"
#include <iostream>
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

	int board::getHeight() {
		return _height;
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

	bool board::addPeg(const peg& p) {
		return addPeg(p.getRow(), p.getIndex());
	}

	bool board::removePeg(int row, int index) {
		if (!_pegs[row][index].remove()) return false;
			
		_total_pegs_removed++;
		return true;
	}

	bool board::removePeg(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index);
		return removePeg(row, index);
	}

	bool board::removePeg(const peg& p) {
		return removePeg(p.getRow(), p.getIndex());
	}

	bool board::validateMove(const peg& fromPeg, const peg& toPeg) {	
		if (fromPeg.isRemoved()) return false;
		if (!toPeg.isRemoved()) return false;

		//validate jump
		auto dist = -1;
		if (fromPeg.getRow() == toPeg.getRow()) {
			dist = abs(fromPeg.getIndex() - toPeg.getIndex());
		} else {
			dist = abs(fromPeg.getRow() - toPeg.getRow());
		}
		if (dist != 2) return false;

		peg middle;
		_find_middle_peg(fromPeg, toPeg, middle);
		return !middle.isRemoved();
	}

	bool board::isPegRemoved(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index);
		return _pegs[row][index].isRemoved();
	}

	bool board::movePeg(const peg& fromPeg, const peg& toPeg) {
		if (!validateMove(fromPeg, toPeg)) return false;

		removePeg(fromPeg);
		addPeg(toPeg);

		//remove jumped peg.
		peg middle;
		_find_middle_peg(fromPeg, toPeg, middle);
		removePeg(middle);

		return true;
	}

	bool board::movePeg(int fromPeg, int toPeg) {
		peg f, t;
		getPeg(fromPeg, f);
		getPeg(toPeg, t);
		return movePeg(f, t);
	}

	std::map<int, std::vector<int>> board::getAllMoves() {
		auto m = std::map<int, std::vector<int>>();
		int pegNum = 1;
		int last = peg::FindLastPegNumber(_height);

		for (int i = 1; i <= last; i++) {
			peg p;
			if (!getPeg(i, p))
				continue;

			if (!p.isRemoved())
				continue;

			auto moves = getMoves(p);
			if (moves.empty())
				continue;

			m[p.getNumber()] = moves;
		}

		return m;
	}

	std::vector<int> board::getMoves(const peg& toPeg) {
		auto moves = std::vector<int>();

		int index = toPeg.getIndex();
		int row = toPeg.getRow();

		//check above:
		int aboveRow = row - 2;
		if (aboveRow >= 0) {

			if (toPeg.atBegin()) {
				_add_move(_pegs[aboveRow][0], toPeg, moves);
			} else if (toPeg.atEnd()) {
				_add_move( _pegs[aboveRow][aboveRow], toPeg, moves);
			} else {
				if (index - 2 >= 0)
					_add_move(_pegs[aboveRow][index - 2], toPeg, moves);
				if (index <= aboveRow) 
					_add_move(_pegs[aboveRow][index], toPeg, moves);
				if (index + 2 <= aboveRow)
					_add_move(_pegs[aboveRow][index + 2], toPeg, moves);
			}

		}

		//check current row:
		if (index - 2 >= 0)
			_add_move(_pegs[row][index - 2], toPeg, moves);

		if (index + 2 <= row)
			_add_move(_pegs[row][index + 2], toPeg, moves);

		//check below:
		int belowRow = row + 2;
		if (belowRow < _height) {

			if (toPeg.atBegin()) {
				_add_move(_pegs[belowRow][0], toPeg, moves);
				_add_move(_pegs[belowRow][2], toPeg, moves);
			} else if (toPeg.atEnd()) {
				_add_move(_pegs[belowRow][belowRow - 2], toPeg, moves);
				_add_move(_pegs[belowRow][belowRow], toPeg, moves);
			} else {
				_add_move(_pegs[belowRow][index], toPeg, moves);
				if (index + 2 < belowRow)
					_add_move(_pegs[belowRow][index + 2], toPeg, moves);
			}

		}
		
		return moves;
	}

	std::string board::to_string() {
		if (_pegs.empty()) return "";
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
	const void board::_init_pegs() {
		for (int row = 0; row < _height; row++) {
			auto row_p = std::vector<peg>();

			int e_pos = peg::FindLastPegNumber(row + 1);
			int s_pos = e_pos - row;

			for (int i = s_pos; i <=  e_pos; i++) 
				row_p.push_back(peg(i, row, (row) - (e_pos - i)) );

			_pegs.push_back(row_p);

		}

	}

	const void board::_add_move(const peg& fromPeg, const peg& toPeg, std::vector<int>& moves) {
		if (!validateMove(fromPeg, toPeg))
			return;

		moves.push_back(fromPeg.getNumber());
	}

	bool board::_validate(int row, int index) {
		if (row < 0 || row >= _height) return false;
		if (index < 0 || index >= (row+1)) return false;

		return true;
	}

	void board::_find_middle_peg(const peg& fromPeg, const peg& toPeg, peg& middlePeg) {
		if (fromPeg.getRow() == toPeg.getRow()) { //same row
			int idx = fromPeg > toPeg
				? fromPeg.getIndex()
				: toPeg.getIndex();

			middlePeg = _pegs[fromPeg.getRow()][idx - 1];
			return;
		}

		if (fromPeg.getIndex() == toPeg.getIndex()) {
			int row = fromPeg > toPeg
				? fromPeg.getRow()
				: toPeg.getRow();
			middlePeg = _pegs[row - 1][fromPeg.getIndex()];
			return;
		}

		middlePeg = fromPeg > toPeg
			? _pegs[fromPeg.getRow() - 1][fromPeg.getIndex() - 1]
			: _pegs[toPeg.getRow() - 1][toPeg.getIndex() - 1];
	}


} 