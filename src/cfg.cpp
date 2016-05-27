#include "../include/cfg.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace cfg
{

    int gem_width = 5;
    int gem_height = 3;

    int board_height = 8;
    int board_width = 8;

    int anim_frames = 5;

    bool swap_back = true;

    int game_turns = 30;

    int speed = 3;

    int color_nuke = 8;

    bool importConfig(std::string config_name)
    {
        std::ifstream if_config;
        if_config.open(config_name);
        if(if_config.good())
        {
            std::stringstream buffer;
            buffer << if_config.rdbuf();
            if_config.close();

            std::istringstream is_config(buffer.str()); //Creating a new input string stream from the buffer
            std::string line;

            std::unordered_map<std::string, int> config_map;

            while(std::getline(is_config, line))    //Iterating through each line using \n as a delimiter
            {
                std::istringstream is_line(line);    //Creating a new input string stream from the line
                std::string key;
                if( std::getline(is_line, key, '='))    //Splitting the line using = as a delimiter, returning the key
                {
                    std::string value_string;
                    if( std::getline( is_line, value_string) ) //Gets the next half of the string (skips if invalid)
                    {
                        int value = std::stoi(value_string);
                        config_map.insert(std::unordered_map<std::string,int>::value_type(key,value));
                    }
                }
            }
            //Horrible code to read the map and set all the config values
            bool any_failed = false;
            if(config_map.count("gem_width") == 1)
                gem_width = config_map.at("gem_width");
            else
                any_failed = true;

            if(config_map.count("gem_height") == 1)
                gem_height = config_map.at("gem_height");
            else
                any_failed = true;

            if(config_map.count("board_height") == 1)
                board_height = config_map.at("board_height");
            else
                any_failed = true;

            if(config_map.count("board_width") == 1)
                board_width = config_map.at("board_width");
            else
                any_failed = true;

            if(config_map.count("anim_frames") == 1)
                anim_frames = config_map.at("anim_frames");
            else
                any_failed = true;

            if(config_map.count("swap_back") == 1)
            {
                int tmp = config_map.at("swap_back");
                if(tmp == 1)
                    swap_back = true;
                else if(tmp == 0)
                    swap_back = false;
                else
                    any_failed = true;
            }
            else
                any_failed = true;

            if(config_map.count("game_turns") == 1)
                game_turns = config_map.at("game_turns");
            else
                any_failed = true;

            if(config_map.count("speed") == 1)
                speed = config_map.at("speed");
            else
                any_failed = true;

            if(config_map.count("color_nuke") == 1)
                color_nuke = config_map.at("color_nuke");
            else
                any_failed = true;

            if(!any_failed)
                return true;

            else
                return false;
        }
        else
            return false;   //False denotes the file was unsuccessfully read
    }

    void writeConfig(std::string config_name)
    {
        std::ofstream config_file(config_name);
        config_file << "gem_width" << "=" << gem_width << std::endl;
        config_file << "gem_height" << "=" << gem_height << std::endl;
        config_file << "board_height" << "=" << board_height << std::endl;
        config_file << "board_width" << "=" << board_width << std::endl;
        config_file << "anim_frames" << "=" << anim_frames << std::endl;
        config_file << "swap_back" << "=" << swap_back << std::endl;
        config_file << "game_turns" << "=" << game_turns << std::endl;
        config_file << "speed" << "=" << speed << std::endl;
        config_file << "color_nuke" << "=" << color_nuke << std::endl;
        config_file.close();
    }
}
