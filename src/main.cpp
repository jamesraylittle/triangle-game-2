#include <iostream>
#include <string>
#include <vector>
#include <ios>
#include <limits>
#include <sstream>

#include "include/board.h"

using namespace std;

#define DEFAULT_TRI_HEIGHT 5

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

bool askYesNo(const string& question) {
	char input;
	while (true) {
		cout << question << "[Y/N]: ";
		if (cin >> input) {
			if (input == 'Y' || input == 'y' || input == 'N' || input == 'n')
				break;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return input == 'Y' || input == 'y';
}

std::string vectorToStr(std::vector<int> v) {
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

std::string moveListToStr(int pegNumber, std::vector<int>& moves) {
	std::stringstream ss;
	ss << vectorToStr(moves) << " => " << pegNumber;
	return ss.str();
}

std::string moveListToStr(std::map<int, std::vector<int>>& m) {
	std::stringstream ss;
	int i = 0;
	for (auto it = m.begin(); it != m.end(); ++it){
		ss << moveListToStr(it->first, it->second);
		if (i+1 < m.size())
			ss << ", ";
		i++;
	}
	return ss.str();
}

bool hasPosition(int peg, const std::map<int, std::vector<int>>& m) {
	for (const auto [key, value] : m) {

		for (const auto& pos : value) {
			if (pos == peg)
				return true;
		}

	}
	return false;
}

int main() {

	bool playAgain = false;
	do {
		//int height = askForNumber("Enter Triangle Height", 2, 10);
		int height = DEFAULT_TRI_HEIGHT;
		auto board = TriangleGame::board(height);
		cout << board << endl;


		int pegNumber = askForNumber("Enter First Peg to Remove", 1, board.getTotalPegs());
		board.removePeg(pegNumber);
			
		auto moves = board.getAllMoves();
		while (!moves.empty()) {
			//Display Board
			cout << board << endl;
			cout << "Avaliable Moves: " << moveListToStr(moves) << endl;
			
			int fromPeg = askForNumber("Select a Peg to Move", 1, board.getTotalPegs());
			
			if (!hasPosition(fromPeg, moves)) {
				cout << "\t" << "Unable to Move Peg [" << fromPeg << "], no avaliable positions open." << endl;
				continue;
			}

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
			moves = board.getAllMoves();
			
			
		}

		cout << board << endl;

		int left = board.getTotalPegs() - board.getTotalRemovedPegs();

		cout << "Total Pegs Left: " << left << endl;

		std::string results = "";
		switch (left) {
			case 1: results = "You are a GENIUS"; break;
			case 2: results = "You are Pretty Smart!"; break;
			case 3: results = "You are Just Plain Dumb!"; break;
			default: results = "You are an EQ-NO-RA-MOOOSE!";
		}

		cout << endl << results << endl << endl;

		playAgain = askYesNo("Do You want to Play Again?");
	} while (playAgain);

	return EXIT_SUCCESS;

}