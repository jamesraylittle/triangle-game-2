#include <iostream>
#include <string>
#include <vector>
#include <ios>
#include <limits>
#include <sstream>

#include "include/board.h"

using namespace std;

int askForNumber(const string& question, int min = INT_MIN, int max = INT_MAX) {
	int input;
	while (true) {
		cout << question << " [" << min << "-" << max << "]: ";	

		if (cin >> input) {
			if (input >= min && input <= max)
				break;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}
	
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return input;
}

std::string vectorToStr(const std::vector<int>& v) {
	std::stringstream ss;
	ss << "[";
	for (int i = 0; i < v.size(); i++) {
		ss << v[i];
		if (i + 1 < v.size())
			ss << ", ";
	}
	ss << "]";
	return ss.str();
}

std::string moveListToStr(int pegNumber, const std::vector<int>& moves) {
	std::stringstream ss;
	ss << vectorToStr(moves) << " => " << pegNumber;
	return ss.str();
}

int main() {

	int height = askForNumber("Enter Triangle Height", 2, 10);
	
	auto board = TriangleGame::board(height);


	cout << board << endl;

	int pegNumber = askForNumber("Enter First Peg to Remove", 1, board.getTotalPegs());
	board.removePeg(pegNumber);
		
	do {
		//Display Board
		cout << board << endl;
		//auto moves = board.getMoves(peg);
		//cout << "Avaliable Moves: " << moveListToStr(peg, moves) << endl;

		int fromPeg = askForNumber("Select a Peg to Move", 1, board.getTotalPegs());
		
		if (board.isPegRemoved(fromPeg)) {
			cout << "\t" << "Peg [" << fromPeg << "] has already been removed." << endl;
			continue;
		}

		int toPeg = askForNumber("Move To", 1, board.getTotalPegs());
		if (!board.isPegRemoved(toPeg)) {
			cout << "\t" << "Cannot Move Peg [" << fromPeg << "] to ["<< toPeg << "], becuase [" << toPeg << "] is not open." << endl;
			continue;
		}

		board.movePeg(fromPeg, toPeg);
		
		
	} while (board.getTotalRemovedPegs() < board.getTotalPegs());

	return EXIT_SUCCESS;

}