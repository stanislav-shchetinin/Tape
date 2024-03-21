//
// Created by stass on 21.03.2024.
//

#ifndef YADRO_CONFIG_H
#define YADRO_CONFIG_H

#include <fstream>
#include <string>
#include "json.hpp"

struct Config {
    int recording_delay;
    int read_delay;
    int tape_rewind_delay;
    int tape_shift_delay;
};

Config read_config_file(const std::string& config_file);

#endif //YADRO_CONFIG_H
