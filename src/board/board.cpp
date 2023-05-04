#include "board.h"
#include <iostream>
namespace TriangleGame {

	board::board(int height)
		: _height(height), _history(move_history())
		{
			_total_pegs = peg::FindLastPegNumber(height);
			_total_pegs_removed = 0;
			_init_pegs();
		}

	int board::get_total_pegs() {
		return _total_pegs;
	}

	int board::get_total_removed_pegs() {
		return _total_pegs_removed;
	}

	int board::get_height() {
		return _height;
	}

	bool board::get_peg(int row, int index, peg& p) {
		if (!_validate(row, index)) return false;
		p = _pegs[row][index];
		return true;
	}

	bool board::get_peg(int pegNumber, peg& p) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index, _height);
		return get_peg(row, index, p);
	}

	bool board::add_peg(int row, int index) {
		//validate
		if (!_validate(row, index)) return false;
		if (!_pegs[row][index].replace()) return false;

		_total_pegs_removed--;
		return true;
	}

	bool board::add_peg(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index, _height);
		return add_peg(row, index);
	}

	bool board::add_peg(const peg& p) {
		return add_peg(p.get_row(), p.get_index());
	}

	bool board::remove_peg(int row, int index) {
		if (!_pegs[row][index].remove()) return false;
		_total_pegs_removed++;
		return true;
	}

	bool board::remove_peg(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index);
		return remove_peg(row, index);
	}

	bool board::remove_peg(const peg& p) {
		return remove_peg(p.get_row(), p.get_index());
	}

	bool board::validate_move(const peg& fromPeg, const peg& toPeg) {	
		if (fromPeg.is_removed()) return false;
		if (!toPeg.is_removed()) return false;

		//validate jump
		auto dist = -1;
		if (fromPeg.get_row() == toPeg.get_row()) {
			dist = abs(fromPeg.get_index() - toPeg.get_index());
		} else {
			dist = abs(fromPeg.get_row() - toPeg.get_row());
		}
		if (dist != 2) return false;

		peg middle;
		_find_middle_peg(fromPeg, toPeg, middle);
		return !middle.is_removed();
	}

	bool board::is_peg_removed(int pegNumber) {
		int row, index;
		peg::LocatePeg(pegNumber, row, index);
		return _pegs[row][index].is_removed();
	}

	bool board::remove_inital_peg(int pegNumber) {
		if (!remove_peg(pegNumber))
			return false;

		_history.add_move(pegNumber);
		return true;
	}

	bool board::go_back() {
		move m;
		if (!_history.try_get_move(_history.get_index(), m))
			return false;

		if (m.is_inital_move()) {
			add_peg(m.get_removed());
		} else {
			add_peg(m.get_from());
			add_peg(m.get_removed());
			remove_peg(m.get_to());
		}

		_history.go_back();
		return true;
	}

	bool board::move_peg(const peg& fromPeg, const peg& toPeg) {
		if (!validate_move(fromPeg, toPeg)) return false;

		remove_peg(fromPeg);
		add_peg(toPeg);

		//remove jumped peg.
		peg middle;
		_find_middle_peg(fromPeg, toPeg, middle);
		remove_peg(middle);

		_history.add_move(fromPeg, toPeg, middle);

		return true;
	}

	bool board::move_peg(int fromPegNumber, int toPegNumber) {
		peg f, t;
		get_peg(fromPegNumber, f);
		get_peg(toPegNumber, t);
		return move_peg(f, t);
	}

	t_open_moves board::get_all_moves() {
		auto m = t_open_moves();
		int pegNum = 1;
		int last = peg::FindLastPegNumber(_height);

		for (int i = 1; i <= last; i++) {
			peg p;
			if (!get_peg(i, p))
				continue;

			if (!p.is_removed())
				continue;

			auto moves = get_moves(p);
			if (moves.empty())
				continue;

			m[p.get_number()] = moves;
		}

		return m;
	}

	t_moves board::get_moves(const peg& toPegNumber) {
		auto moves = t_moves();

		int index = toPegNumber.get_index();
		int row = toPegNumber.get_row();

		//check above:
		int aboveRow = row - 2;
		if (aboveRow >= 0) {

			if (toPegNumber.at_begin()) {
				_add_move(_pegs[aboveRow][0], toPegNumber, moves);
			} else if (toPegNumber.at_end()) {
				_add_move( _pegs[aboveRow][aboveRow], toPegNumber, moves);
			} else {
				if (index - 2 >= 0)
					_add_move(_pegs[aboveRow][index - 2], toPegNumber, moves);
				if (index <= aboveRow) 
					_add_move(_pegs[aboveRow][index], toPegNumber, moves);
				if (index + 2 <= aboveRow)
					_add_move(_pegs[aboveRow][index + 2], toPegNumber, moves);
			}

		}

		//check current row:
		if (index - 2 >= 0)
			_add_move(_pegs[row][index - 2], toPegNumber, moves);

		if (index + 2 <= row)
			_add_move(_pegs[row][index + 2], toPegNumber, moves);

		//check below:
		int belowRow = row + 2;
		if (belowRow < _height) {

			if (toPegNumber.at_begin()) {
				_add_move(_pegs[belowRow][0], toPegNumber, moves);
				_add_move(_pegs[belowRow][2], toPegNumber, moves);
			} else if (toPegNumber.at_end()) {
				_add_move(_pegs[belowRow][belowRow - 2], toPegNumber, moves);
				_add_move(_pegs[belowRow][belowRow], toPegNumber, moves);
			} else {
				_add_move(_pegs[belowRow][index], toPegNumber, moves);
				if (index + 2 < belowRow)
					_add_move(_pegs[belowRow][index + 2], toPegNumber, moves);
			}

		}
		
		return moves;
	}

	move_history board::get_move_history() const {
		return _history;
	}

	std::string board::to_string() const noexcept {
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

	//--------------------------------------------------
	// Private Methods
	//--------------------------------------------------

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

	const void board::_add_move(const peg& fromPeg, const peg& toPeg, t_moves& moves) {
		if (!validate_move(fromPeg, toPeg))
			return;

		moves.push_back(fromPeg.get_number());
	}

	bool board::_validate(int row, int index) {
		if (row < 0 || row >= _height) return false;
		if (index < 0 || index >= (row+1)) return false;

		return true;
	}

	void board::_find_middle_peg(const peg& fromPeg, const peg& toPeg, peg& middlePeg) {
		if (fromPeg.get_row() == toPeg.get_row()) { //same row
			int idx = fromPeg > toPeg
				? fromPeg.get_index()
				: toPeg.get_index();

			middlePeg = _pegs[fromPeg.get_row()][idx - 1];
			return;
		}

		if (fromPeg.get_index() == toPeg.get_index()) {
			int row = fromPeg > toPeg
				? fromPeg.get_row()
				: toPeg.get_row();
			middlePeg = _pegs[row - 1][fromPeg.get_index()];
			return;
		}

		middlePeg = fromPeg > toPeg
			? _pegs[fromPeg.get_row() - 1][fromPeg.get_index() - 1]
			: _pegs[toPeg.get_row() - 1][toPeg.get_index() - 1];
	}


} 