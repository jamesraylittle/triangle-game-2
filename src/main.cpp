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

int main() {

	int height = askForNumber("Enter Triangle Height", 2, 10);
	
	auto board = TriangleGame::board(height);


	cout << board << endl;

	int firstPeg = askForNumber("Enter First Peg to Remove", 1, board.getTotalPegs());
	board.removePeg(firstPeg);
	
	cout << board << endl;
	
	int peg = askForNumber("Select a Peg to Move", 1, board.getTotalPegs());

	auto moves = board.getMoves(peg);
	cout << "Avaliable Moves: " << vectorToStr(moves) << endl;

	return EXIT_SUCCESS;

}