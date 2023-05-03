#pragma once
#ifndef __H_TRIANGLE_MOVE__
#define __H_TRIANGLE_MOVE__

#include <sstream>

#include "peg.h"
#include "../include/abstract/printable.h"

namespace TriangleGame {

	class move : public abstract::printable {
		public:
			move(const peg& removedPeg);
			move(const peg& fromPeg, const peg& toPeg, const peg& removedPeg);
			move(const move& m);
			move();

			bool is_inital_move() const noexcept;

			peg get_from() const;
			peg get_to() const;
			peg get_removed() const;

			std::string to_string() const noexcept;

		private:
			peg _from;
			peg _to;
			peg _removed;
	};

}

#endif