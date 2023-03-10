#include <iostream>
#include <string>
#include <vector>

#include "include/util.h"
#include "include/board.h"

using namespace std;

#define DEFAULT_TRI_HEIGHT 5

std::string moveListToStr(int pegNumber, const TriangleGame::t_moves& moves);
std::string moveListToStr(const TriangleGame::t_open_moves& m);
TriangleGame::t_moves mergeLists(TriangleGame::t_open_moves& m);
TriangleGame::t_moves getOpenPegsFrom(int fromPeg, const TriangleGame::t_open_moves& m);
void playGame(int height);

int main() {

	do {
		
		playGame(DEFAULT_TRI_HEIGHT);

	} while (util::askYesNo("Do You want to Play Again?"));

	return EXIT_SUCCESS;
}

std::string moveListToStr(int pegNumber, const TriangleGame::t_moves& moves) {
	std::stringstream ss;
	ss << util::vectorToStr(moves) << " => " << pegNumber;
	return ss.str();
}

std::string moveListToStr(const TriangleGame::t_open_moves& m) {
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

TriangleGame::t_moves mergeLists(TriangleGame::t_open_moves& m) {
	auto v = TriangleGame::t_moves();
	for (auto it = m.begin(); it != m.end(); ++it) {

		auto list = it->second;
		for (const auto& e : list) {
			
			if (std::find(v.begin(), v.end(), e) == v.end())
				v.push_back(e);
		}

	}
	std::sort(v.begin(), v.end());
	return v;
}

TriangleGame::t_moves getOpenPegsFrom(int fromPeg, const TriangleGame::t_open_moves& m) {
	auto v = std::vector<int>();
	for (auto it = m.begin(); it != m.end(); ++it) {
		auto list = it->second;
		if (std::find(list.begin(), list.end(), fromPeg) != list.end())
			v.push_back(it->first);

	}
	return v;
}

void playGame(int height) {
	auto board = TriangleGame::board(height);

	cout << board << endl;

	int pegNumber = util::askForNumber("Enter First Peg to Remove", 1, board.getTotalPegs());
	board.removePeg(pegNumber);
		
	auto moves = board.getAllMoves();

	while (!moves.empty()) {
		cout << board << endl << endl;

		cout << "Avaliable Moves: " << moveListToStr(moves) << endl;
		
		int fromPeg = util::askForNumber("Select a Peg to Move", mergeLists(moves));
		int toPeg = util::askForNumber("Move To", getOpenPegsFrom(fromPeg, moves));
		
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

}