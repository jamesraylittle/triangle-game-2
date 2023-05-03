#pragma once
#ifndef __H_TRIANGLE_MOVE_HISTORY__
#define __H_TRIANGLE_MOVE_HISTORY__

#include <map>
#include <sstream>

#include "move.h"
#include "../include/abstract/printable.h"

typedef unsigned int t_history_index;
typedef std::map<t_history_index, TriangleGame::move> t_history_container;

namespace TriangleGame {
	class move_history : public abstract::printable {
		public:
			move_history();

			t_history_index add_move(const move& m);

			t_history_index add_move(const peg& fromPeg, const peg& toPeg, const peg& removedPeg);

			t_history_index add_move(const peg& removedPeg);

			t_history_index get_index() const;

			bool try_get_move(t_history_index index, move& m) const;

			std::string to_string() const noexcept;

		private:
			t_history_index _index;
			t_history_container _history;




	};
}

#endif