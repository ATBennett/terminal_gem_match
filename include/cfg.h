#ifndef CFG_H
#define CFG_H

#include <string>

namespace cfg
{
    bool importConfig(std::string);
    void writeConfig(std::string);

    //Game global settings
    extern int gem_width;
    extern int gem_height;

    extern int board_height;
    extern int board_width;

    extern int anim_frames;

    extern bool swap_back;

    extern int game_turns;

    extern int speed;

    extern int color_nuke;

}

#endif // CFG_H
