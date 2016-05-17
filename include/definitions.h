//Definitions for game settings, in time I hope to phase this out with a menu ingame.

//Tells the program the size of the gems implemented in Gem.cpp and BasicGems.cpp.
#define GEM_HEIGHT 3
#define GEM_WIDTH 5

#define ANIM_LENGTH 5

//Defines how large to make the maximum grid size(no issues found with larger sizes, but may run into performance problems)
#define MAX_BOARD_HEIGHT 32
#define MAX_BOARD_WIDTH 32

//Tells the program how large to make the GemBoard.
#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

//Number of game turns.
#define GAME_TURNS 30

//How fast to play animations (1 is fastest, 0 is instant).
#define SPEED 3

//Define the number of the color nuke gem (must be higher than 7)
#define COLOR_NUKE 8

//Define whether the gems should swap back if there is no match
#define SWAP_BACK true
