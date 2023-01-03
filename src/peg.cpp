#include "include/peg.h"

namespace TriangleGame {

	peg::peg()
	: _number(-1), _row(-1), _index(-1) 
	{
		_removed = true;
		_atEnd = false;
		_atBegin = false;
	}

	peg::peg(int number, int row, int index)
		: _number(number), _row(row), _index(index) 
	{
		_init_peg();
	}

	peg::peg(int row, int index)
		: _row(row), _index(index) 
	{
		_number = peg::FindPegNumber(row, index);
		_init_peg();
	}

	peg::peg(int number)
		: _number(number)
	{
		peg::LocatePeg(number, _row, _index);
		_init_peg();
	}

	int peg::getNumber() {
		return _number;
	}

	int peg::getRow() {
		return _row;
	}

	int peg::getIndex() {
		return _index;
	}

	bool peg::atBegin() {
		return _atBegin;
	}

	bool peg::atEnd() {
		return _atEnd;
	}

	bool peg::atMiddle() {
		return !_atBegin && !_atEnd;
	}

	bool peg::remove() {
		if (_removed) return false;
		_removed = true;
		return true;
	}

	bool peg::replace() {
		if (!_removed) return false;
		_removed = false;
		return true;
	}

	bool peg::isRemoved() {
		return _removed;
	}

	std::string peg::to_string() {
		if (_removed) return EMPTY_PEG_STR;
		std::stringstream ss;
		ss << _number;
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& os, peg& p) {
		os << p.to_string();
		return os;
	}

	//Public Static Methods
	int peg::FindLastPegNumber(int row) {
		return (row * (row + 1)) / 2;
	}

	int peg::FindPegNumber(int row, int index) {
		return peg::FindLastPegNumber(row) - (row - index);
	}

	void peg::LocatePeg(int pegNumber, int& row, int& index, int maxHeight) {
		int last = 0;
		for (int i = 0; i < maxHeight; i++) {
			last = FindLastPegNumber(i+1);
			if (pegNumber <= last) {
				row = i;
				break;
			}
		}
		index = pegNumber - (last - row + 1) + 1;
	}

	//Private Methods

	void peg::_init_peg() {
		_removed = false;
		_atEnd = peg::FindLastPegNumber(_row) == _number;
		_atBegin = peg::FindPegNumber(_row, _index) == _number;
	}

}