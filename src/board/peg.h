#pragma once
#ifndef __H_TRIANGLE_BOARD_PEG__
#define __H_TRIANGLE_BOARD_PEG__

#include <ostream>
#include <string>
#include <sstream>
#include <cmath>

#define EMPTY_PEG_STR "X"

namespace TriangleGame {

	class peg {
		public:
			peg();
			peg(int number, int row, int index);
			peg(int row, int index);
			peg(int number);

			//copy constructor
			peg(const peg& p);//= delete;

			int getNumber() const;
			int getRow() const;
			int getIndex() const;

			bool atBegin() const;
			bool atEnd() const;
			bool atMiddle() const;

			const bool remove();
			const bool replace();

			bool isRemoved() const;

			std::string to_string() const;

			bool operator==(const peg& other) const;
			bool operator<(const peg& other) const;
			bool operator>(const peg& other) const;
			bool operator>=(const peg& other) const;
			bool operator<=(const peg& other) const;
			
			friend std::ostream& operator<<(std::ostream& os, const peg& p);
			

			static int FindLastPegNumber(int row);
			static int FindPegNumber(int row, int index);
			static void LocatePeg(int pegNumber, int& row, int& index, int maxHeight = 5);

		private:
			int _row;
			int _index;
			int _number;
			bool _atEnd;
			bool _atBegin;
			bool _atMiddle;
			bool _removed;


			void _init_peg();
	};

}


#endif