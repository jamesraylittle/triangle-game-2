#include <iostream>
#include <string>
#include <vector>

#include <util.h>
#include <board.h>
#include <triangle-game-config.h>

#include <tclap/CmdLine.h>

using namespace std;


std::string moveListToStr(int pegNumber, const TriangleGame::t_moves& moves);
std::string moveListToStr(const TriangleGame::t_open_moves& m);
TriangleGame::t_moves mergeLists(TriangleGame::t_open_moves& m);
TriangleGame::t_moves getOpenPegsFrom(int fromPeg, const TriangleGame::t_open_moves& m);
void playGame(int height);

int main(int argc, char** argv) {

	try {
		TCLAP::CmdLine cmd(TRIANGLE_GAME_NAME, ' ', TRIANGLE_GAME_VERSION);

		cmd.parse(argc, argv);

	} catch (TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	do {
		
		playGame(TRIANGLE_GAME_DEFAULT_HEIGHT);

	} while (util::ask_yes_no("Do You want to Play Again?"));


	return EXIT_SUCCESS;
}

std::string moveListToStr(int pegNumber, const TriangleGame::t_moves& moves) {
	std::stringstream ss;
	ss << util::vector_to_str(moves) << " => " << pegNumber;
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

	int pegNumber = util::ask_for_number("Enter First Peg to Remove", 1, board.get_total_pegs());
	board.remove_peg(pegNumber);
		
	auto moves = board.get_all_moves();

	while (!moves.empty()) {
		cout << board << endl << endl;

		cout << "Avaliable Moves: " << moveListToStr(moves) << endl;
		
		int fromPeg = util::ask_for_number("Select a Peg to Move", mergeLists(moves));
		int toPeg = util::ask_for_number("Move To", getOpenPegsFrom(fromPeg, moves));
		
		board.move_peg(fromPeg, toPeg);

		moves = board.get_all_moves();
	}


	cout << board << endl;

	int left = board.get_total_pegs() - board.get_total_removed_pegs();

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