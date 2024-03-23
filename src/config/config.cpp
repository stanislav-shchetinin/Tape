//
// Created by stass on 21.03.2024.
//

#include "config.h"

Config read_config_file(const std::string& config_file) {
    using json = nlohmann::json;
    std::ifstream f(config_file);
    json data = json::parse(f);
    return Config{
            data["recording_delay"],
            data["read_delay"],
            data["tape_rewind_delay"],
            data["tape_shift_delay"]
    };
}