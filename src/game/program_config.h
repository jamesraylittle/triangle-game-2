#pragma once
#ifndef __H_TRI_GAME_PROGRAM_CONFIG__
#define __H_TRI_GAME_PROGRAM_CONFIG__

#include <iostream>
#include <tclap/CmdLine.h>
#include <triangle-game-config.h>

#include <peg.h>

namespace program_config {

	static int BoardHeight = TRIANGLE_GAME_DEFAULT_HEIGHT;

	class RangeContraint : public TCLAP::Constraint<int> {
		public:
			RangeContraint(int min, int max) 
				: _min(min), _max(max) 
			{

			}

			RangeContraint(int min)
				: _min(min), _max(INT_MAX)
			{

			}

			virtual std::string description() const {
				std::stringstream ss;
				ss << "Value must be between " << _min << " and " << _max;
				return ss.str();
			}

			virtual std::string shortID() const { 
				return "int";
			}

			virtual bool check(const int& value) const {
				return value >= _min && value <= _max;
			}

			std::string to_string() const {
				std::stringstream ss;
				ss << "[" << _min << ", " << _max << "]";
				return ss.str();
			}

		private:
			int _min;
			int _max;

	};

	std::string get_game_info() {
		std::stringstream ss;
		ss << "Welcome to the Triangle Peg Game!" << std::endl;
		ss << "Written by James Little <james@jameslittle.org>" << std::endl << std::endl;

		ss << "Game Description:" << std::endl;
		ss << "==============================================================" << std::endl;
		ss << "The goal of the game is to remove the most amount of pegs from the board." << std::endl;
		ss << "The least amount of pegs on a board is 1." << std::endl;
		ss << std::endl;
		ss << "Pegs can be removed by jumping over an existing peg into an empty peg hole." << std::endl;
		ss << "If there are no valid moves left, the game is over." << std::endl;
		ss << std::endl;
		ss << "The board is in the shape of a triangle, with a typical height of " << TRIANGLE_GAME_DEFAULT_HEIGHT << std::endl;
		ss << "However, the height can be adjusted with the --height option." << std::endl;
		ss << std::endl;
		ss << "This program was inspired by the \"Triangle Game\" from Cracker Barrel" << std::endl; 
		ss << "Also known as \"Peg Solitaire\"." << std::endl;
		ss << std::endl;

		ss << "Game Instructions:" << std::endl;
		ss << "==============================================================" << std::endl;
		ss << "1. First select a starting peg hole, by select a peg to remove." << std::endl;
		ss << "2. Next, select a peg number to move." << std::endl;
		ss << "3. Next, select a peg hole number to move to." << std::endl;
		ss << "4. Repeat steps 2 and 3 until there are no valid moves left." << std::endl;
		ss << std::endl;
		ss << "Note: The pegs are numbered, and empty peg holes are represented by a \"" << EMPTY_PEG_STR << "\"." << std::endl;

		return ss.str();
	}
	

	bool parse_args(int argc, char** argv) {
		try { 
			TCLAP::CmdLine cmd(get_game_info(), ' ', TRIANGLE_GAME_VERSION);
			//Setup Program Arguments
			
			//--- Height of the Game Board
			RangeContraint heightArgRange(TRIANGLE_GAME_MIN_ALLOW_HEIGHT, TRIANGLE_GAME_MAX_ALLOW_HEIGHT);
			std::stringstream h_ss;
			h_ss << "Hight of the Game Board. Valid Values: " << heightArgRange.to_string();
			
			TCLAP::ValueArg<int> heightArg("t", "height", h_ss.str(), false, TRIANGLE_GAME_DEFAULT_HEIGHT, &heightArgRange, cmd);
			//cmd.add(heightArg);
			//--------------------------------


			//Parse Program Arguments
			cmd.parse(argc, argv);

			//Preform Action on those values
			BoardHeight = heightArg.getValue();

		} catch (TCLAP::ArgException &e) {
			std::cerr << "Error: " << e.error() << ", Argument: " << e.argId() << std::endl;
			return false;
		}

		return true;
	}

}

#endif