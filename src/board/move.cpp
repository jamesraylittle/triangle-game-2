#include "move.h"

namespace TriangleGame {
	move::move(const peg& removedPeg) 
		: _from(peg()), _to(peg()), _removed(removedPeg) 
	{

	}

	move::move(const peg& fromPeg, const peg& toPeg, const peg& removedPeg)
		: _from(fromPeg), _to(toPeg), _removed(removedPeg) 
	{
		
	}

	move::move(const move& m) 
		: _from(m._from), _to(m._to), _removed(m._removed)
	{

	}

	move::move() 
		: _from(peg()), _to(peg()), _removed(peg())
	{

	}

	bool move::is_inital_move() const noexcept {
		return _from.is_empty() && _to.is_empty();
	}

	peg move::get_from() const {
		return _from;
	}

	peg move::get_to() const {
		return _to;
	}

	peg move::get_removed() const {
		return _removed;
	}

	std::string move::to_string() const noexcept {
		std::stringstream ss;
		if (!is_inital_move())
			ss << "Jumped peg [" << _from.get_number() << "], over peg [" << _removed.get_number() << "], to peg [" << _to.get_number() << "]";
		else
			ss << "Inital Peg Removed [" << _removed.get_number() << "]";
			
		return ss.str();
	}

}