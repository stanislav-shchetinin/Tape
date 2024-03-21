//
// Created by stass on 21.03.2024.
//

#ifndef YADRO_TAPE_H
#define YADRO_TAPE_H


#include "config.h"

class Tape {
private:
    const Config config;
    int cur_pos{};
    std::fstream file;
public:
    Tape(const Config& config,
         const std::string& tape_file): config(config) {
        file.open(tape_file);
    }
    int read();
    void shift_pos_left();
    void shift_pos_right();
    ~Tape() {
        file.close();
    }
};


#endif //YADRO_TAPE_H
