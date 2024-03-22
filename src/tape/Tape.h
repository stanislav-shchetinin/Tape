//
// Created by stass on 21.03.2024.
//

#ifndef YADRO_TAPE_H
#define YADRO_TAPE_H


#include "config.h"

class Tape {
private:
    static int tapes_count;
    const Config config;
    int cur_pos{};
    std::fstream file;
    std::string file_name;
public:
    Tape(const Config& config,
         const std::string& tape_file);
    Tape(const Tape& other);
    Tape& operator=(const Tape& tape) = delete;
    int read();
    void write(int);
    void shift_pos_left();
    void shift_pos_right();
    void rewind();
    ~Tape() {
        file.close();
    }
};


#endif //YADRO_TAPE_H
