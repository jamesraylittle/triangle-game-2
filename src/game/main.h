#pragma once
#ifndef __H_TRI_GAME_MAIN__
#define __H_TRI_GAME_MAIN__

#include <iostream>
#include <string>
#include <vector>


#include <util.h>
#include <board.h>

const std::string GAME_ACTIONS_QUESTION = "Select (J)ump, (U)ndo Previous Move, (V)iew History, (Q)uit";
const std::vector<char> GAME_ACTIONS = {
	'J',	// Jump Peg
	'U',	// Undo Previous Move
	'V',	// View History
	'Q' 	// Quit Game
};

std::string move_list_to_str(int pegNumber, const TriangleGame::t_moves & moves) {
	std::stringstream ss;
	ss << util::vector_to_str(moves) << " => " << pegNumber;
	return ss.str();
}

std::string move_list_to_str(const TriangleGame::t_open_moves& m) {
	std::stringstream ss;
	int i = 0;
	for (auto it = m.begin(); it != m.end(); ++it){
		ss << move_list_to_str(it->first, it->second);
		if (i+1 < m.size())
			ss << ", ";
		i++;
	}
	return ss.str();
}


TriangleGame::t_moves merge_lists(TriangleGame::t_open_moves& m) {
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

TriangleGame::t_moves get_open_pegs_from(int fromPeg, const TriangleGame::t_open_moves& m) {
	auto v = std::vector<int>();
	for (auto it = m.begin(); it != m.end(); ++it) {
		auto list = it->second;
		if (std::find(list.begin(), list.end(), fromPeg) != list.end())
			v.push_back(it->first);

	}
	return v;
}

std::string get_game_result(int total_pegs_left) {
	switch (total_pegs_left) {
		case 1:  return "You are a GENIUS"; 
		case 2:  return "You are Pretty Smart!"; 
		case 3:  return "You are Just Plain Dumb!"; 
		default: return "You are an EQ-NO-RA-MOOOSE!";
	}
}

void initalize_game(TriangleGame::board& board) {
	//Show Game Board
	std::cout << board << std::endl << std::endl;

	//Ask for First Peg to Remove
	int pegNumber = util::ask_for_number("Enter First Peg to Remove", 1, board.get_total_pegs());
	board.remove_inital_peg(pegNumber);
}

void play_game(int height) {
	//Init Game Board	 
	auto board = TriangleGame::board(height);

	initalize_game(board);
		
	//Priming Reed Pattern
	//Get All Moves
	auto moves = board.get_all_moves();

	//************************
	//* Game Loop            *
	//************************
	while (!moves.empty()) {
		//Show Game Board
		std::cout << board << std::endl << std::endl;

		//Show Avaliable Moves
		std::cout << "Avaliable Moves: " << move_list_to_str(moves) << std::endl << std::endl;

		//Ask for Action
		char action = util::ask_for_option<char>(GAME_ACTIONS_QUESTION, GAME_ACTIONS, util::format_funcs::char_to_upper);

		//Perform Action
		if (action == 'J') { //Jump Peg
				int fromPeg = util::ask_for_number("Select a Peg to Move", merge_lists(moves));
				int toPeg = util::ask_for_number("Move To", get_open_pegs_from(fromPeg, moves));
				board.move_peg(fromPeg, toPeg);

		} else if (action == 'U') { // Undo Previous Move
			std::cout << "Undo Previous Move" << std::endl;
			board.go_back();

			//If the user undos the inital move, re-initalize the game
			//which is asking for the first peg to be removed.
			if (board.get_move_history().size() == 0) 
				initalize_game(board);

		} else if (action == 'V') { // View History
			std::cout << "-------- Move History --------" << std::endl << board.get_move_history() << std::endl;

		} else { // Quit Game
			std::cout << "Quitting Game" << std::endl;
			return;
		}

		//Get All Moves
		moves = board.get_all_moves();
	}

	//************************
	//* Post Game Results    *
	//************************
	 
	//Show Final Board
	std::cout << board << std::endl;

	//Show Move History
	std::cout << "-------- Move History --------" << std::endl << board.get_move_history() << std::endl;

	//Calcualte Total Pegs Left, and Show Results
	int left = board.get_total_pegs() - board.get_total_removed_pegs();
	std::cout << "Total Pegs Left: " << left << std::endl;

	//Show Game Results
	std::string results = get_game_result(left);
	std::cout << std::endl << results << std::endl << std::endl;
}

void game_loop(int height) {
	do {
		play_game(height);
	} while (util::ask_yes_no("Do You want to Play Again?"));
}
#endif