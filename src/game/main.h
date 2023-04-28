#pragma once
#ifndef __H_TRI_GAME_MAIN__
#define __H_TRI_GAME_MAIN__

#include <iostream>
#include <string>
#include <vector>


#include <util.h>
#include <board.h>

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

void play_game(int height) {
	auto board = TriangleGame::board(height);

	std::cout << board << std::endl << std::endl;

	int pegNumber = util::ask_for_number("Enter First Peg to Remove", 1, board.get_total_pegs());
	board.remove_peg(pegNumber);
		
	auto moves = board.get_all_moves();

	while (!moves.empty()) {
		std::cout << board << std::endl << std::endl;

		std::cout << "Avaliable Moves: " << move_list_to_str(moves) << std::endl;
		
		int fromPeg = util::ask_for_number("Select a Peg to Move", merge_lists(moves));
		int toPeg = util::ask_for_number("Move To", get_open_pegs_from(fromPeg, moves));
		
		board.move_peg(fromPeg, toPeg);

		moves = board.get_all_moves();
	}


	std::cout << board << std::endl;

	int left = board.get_total_pegs() - board.get_total_removed_pegs();

	std::cout << "Total Pegs Left: " << left << std::endl;

	std::string results = "";
	switch (left) {
		case 1: results = "You are a GENIUS"; break;
		case 2: results = "You are Pretty Smart!"; break;
		case 3: results = "You are Just Plain Dumb!"; break;
		default: results = "You are an EQ-NO-RA-MOOOSE!";
	}

	std::cout << std::endl << results << std::endl << std::endl;
}

void game_loop(int height) {
	do {
		play_game(height);
	} while (util::ask_yes_no("Do You want to Play Again?"));
}
#endif