//
// Created by stass on 21.03.2024.
//

#include "Tape.h"

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
