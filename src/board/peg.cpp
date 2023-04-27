#include "peg.h"

namespace TriangleGame {

	peg::peg()
	: _number(-1), _row(-1), _index(-1) 
	{

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

	peg::peg(const peg& p) {
		_row = p._row;
		_index = p._index;
		_number = p._number;
		_removed = p._removed;
		_atBegin = p._atBegin;
		_atMiddle = p._atMiddle;
		_atEnd = p._atEnd;
	}

	int peg::getNumber() const {
		return _number;
	}

	int peg::getRow() const {
		return _row;
	}

	int peg::getIndex() const {
		return _index;
	}

	bool peg::atBegin() const {
		return _atBegin;
	}

	bool peg::atEnd() const {
		return _atEnd;
	}

	bool peg::atMiddle() const {
		return _atMiddle;
	}

	const bool peg::remove() {
		if (_removed) return false;
		_removed = true;
		return true;
	}

	const bool peg::replace() {
		if (!_removed) return false;
		_removed = false;
		return true;
	}

	bool peg::isRemoved() const {
		return _removed;
	}

	std::string peg::to_string() const {
		if (_removed) return EMPTY_PEG_STR;
		std::stringstream ss;
		ss << _number;
		return ss.str();
	}

	bool peg::operator==(const peg& other) const {
		return _row == other.getRow()
			&& _index == other.getIndex();
	}

	bool peg::operator<(const peg& other) const {
		if (_row == other.getRow())
			return _index < other.getIndex();
		return _row < other.getRow();
	}

	bool peg::operator>(const peg& other) const {
		if (_row == other.getRow())
			return _index > other.getIndex();
		return _row > other.getRow();
	}

	bool peg::operator>=(const peg& other) const {
		return *(this) > other || *(this) == other;
	}

	bool peg::operator<=(const peg& other) const {
		return *(this) < other || *(this) == other;
	}

	std::ostream& operator<<(std::ostream& os, const peg& p) {
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
		_atEnd = _index == _row;
		_atBegin = _index == 0;
		int middle_idx = floor((_row + 1) / 2.0);
		_atMiddle = _index == middle_idx && _row % 2 == 0;
	}

}