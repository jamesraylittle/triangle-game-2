#include "move_history.h"

namespace TriangleGame {

	move_history::move_history() 
		: _index(-1), _history(t_history_container())
	{

	}

	t_history_index move_history::add_move(const move& m) {
		_history[++_index] = m;
		return _index;
	}

	t_history_index move_history::add_move(const peg& fromPeg, const peg& toPeg, const peg& removedPeg) {
		return add_move(move(fromPeg, toPeg, removedPeg));
	}

	t_history_index move_history::add_move(const peg& removedPeg) {
		return add_move(move(removedPeg));
	}

	t_history_index move_history::go_back() {
		if (_index == -1) return _index;
		_history.erase(_index--);
		return _index;
	}

	t_history_index move_history::get_index() const {
		return _index;
	}

	bool move_history::try_get_move(t_history_index index, move& m) const {
		try {
			m = _history.at(index);
		} catch(const std::exception& e) {
			return false;
		}
		return true;
	}

	std::size_t move_history::size() const noexcept {
		return _history.size();
	}

	std::string move_history::to_string() const noexcept {
		std::stringstream ss;
		for (auto& kv : _history) {
			ss << kv.first << ".\t" << kv.second.to_string() << std::endl;
		}
		return ss.str();
	}

}