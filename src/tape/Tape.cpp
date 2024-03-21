//
// Created by stass on 21.03.2024.
//
#include "Tape.h"

#define MAX_DIGIT_IN_INT 10

int Tape::tapes_count = 0;

Tape::Tape(const Config& config,
     const std::string& tape_file): config(config) {
    ++tapes_count;
    std::ifstream from(tape_file);
    std::string name_tape_file = "../tmp/" + std::to_string(tapes_count);

    std::ofstream of(name_tape_file);
    of.close();

    file.open(name_tape_file);

    std::string cur_num;

    while (from >> cur_num) {
        std::string spaces(MAX_DIGIT_IN_INT - cur_num.size() + 1, ' ');
        cur_num += spaces;
        file << cur_num;
    }

    file.seekp(0);

}

void Tape::shift_pos_left() {
    if (cur_pos == 0) return;
    bool is_digit = false;
    file.clear();
    for (file.seekp(--cur_pos); cur_pos > 0; --cur_pos) {

        char c;
        file.get(c);

        if (c == ' ' && is_digit) {
            break;
        } else if (c != ' ') {
            is_digit = true;
        }
        file.seekp(cur_pos);

    }
}

void Tape::shift_pos_right() {
    bool is_space = false;
    int old_pos = cur_pos;
    file.clear();
    for (; file.peek() != EOF; ++cur_pos) {

        char c;
        file.get(c);

        if (c != ' ' && is_space) {
            file.seekp(cur_pos);
            break;
        } else if (c == ' ') {
            is_space = true;
        }

    }
    if (file.peek() == EOF) {
        cur_pos = old_pos;
        file.clear();
        file.seekp(cur_pos);
    }
}

int Tape::read() {
    int x;
    file >> x;
    file.seekp(cur_pos);
    return x;
}

void Tape::write(int x) {
    file << x;
    file.seekp(cur_pos);
}
