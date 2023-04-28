#include "main.h"
#include "program_config.h"

using namespace std;

static int board_height = TRIANGLE_GAME_DEFAULT_HEIGHT;

int main(int argc, char** argv) {
	//Configure Program - Parse Program Arguments
	if (!program_config::parse_args(argc, argv))
		return EXIT_FAILURE;

	//Run Game Loop
	game_loop(program_config::BoardHeight);

	return EXIT_SUCCESS;
}