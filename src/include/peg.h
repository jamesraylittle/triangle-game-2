#pragma once
#ifndef __H_TRIANGLE_BOARD_PEG__
#define __H_TRIANGLE_BOARD_PEG__

#include <ostream>
#include <string>
#include <sstream>

#define EMPTY_PEG_STR "X"

namespace TriangleGame {

	class peg {
		public:
			peg();
			peg(int number, int row, int index);
			peg(int row, int index);
			peg(int number);

			int getNumber();
			int getRow();
			int getIndex();

			bool atBegin();
			bool atEnd();
			bool atMiddle();

			bool remove();
			bool replace();

			bool isRemoved();

			std::string to_string();

			friend std::ostream& operator<<(std::ostream& os, peg& p);

			static int FindLastPegNumber(int row);
			static int FindPegNumber(int row, int index);
			static void LocatePeg(int pegNumber, int& row, int& index, int maxHeight = 5);

		private:
			int _row;
			int _index;
			int _number;
			bool _atEnd;
			bool _atBegin;
			bool _removed;


			void _init_peg();
	};

}


#endif