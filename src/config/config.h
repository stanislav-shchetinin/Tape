//
// Created by stass on 21.03.2024.
//

#ifndef YADRO_CONFIG_H
#define YADRO_CONFIG_H

#include <fstream>
#include <string>
#include "json.hpp"

struct Config {
    const int recording_delay;
    const int read_delay;
    const int tape_rewind_delay;
    const int tape_shift_delay;
};

Config read_config_file(const std::string& config_file);

#endif //YADRO_CONFIG_H
