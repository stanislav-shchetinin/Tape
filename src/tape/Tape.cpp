//
// Created by stass on 21.03.2024.
//
#include "Tape.h"

int Tape::tapes_count = 0;

Tape::Tape(const Config& config)
        : config(config)
        , num_tape(++tapes_count) {

    std::string name_tape_file = "../tmp/" + std::to_string(tapes_count);
    file_name = name_tape_file;
    std::ofstream of(name_tape_file);
    of.close();

    file.open(name_tape_file);
}

Tape::Tape(const Config& config,
     const std::string& tape_file) : Tape(config) {

    std::ifstream from(tape_file);
    std::string cur_num;

    while (from >> cur_num) {
        std::string spaces(OFFSET - cur_num.size(), ' ');
        cur_num += spaces;
        file << cur_num;
    }

    file.clear();
    file.seekp(0);
}

Tape::Tape(const Config &config, size_t n) : Tape(config) {
    std::string spaces(n, ' ');
    for (size_t i = 0; i < n; ++i) {
        if (i % OFFSET == 0) spaces[i] = '0';
    }
    file << spaces;
    file.clear();
    file.seekp(0);
}

Tape::Tape(const Tape &other)
        : config(other.config)
        , cur_pos(other.cur_pos)
        , file(other.file_name)
        , num_tape(other.num_tape){
    file.seekp(cur_pos);
}

void Tape::shift_pos_left() {
    op_time += config.tape_shift_delay;
    if (cur_pos == 0) return;
    bool is_digit = false;
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
    file.clear();
    file.seekp(cur_pos);
}

void Tape::shift_pos_right() {
    op_time += config.tape_shift_delay;
    bool is_space = false;
    int old_pos = cur_pos;
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
    }
    file.clear();
    file.seekp(cur_pos);
}

int Tape::read() const {
    op_time += config.read_delay;
    int x;
    file >> x;
    file.clear();
    file.seekp(cur_pos);
    return x;
}

void Tape::write(int x) {
    op_time += config.recording_delay;
    std::string spaces(OFFSET, ' ');
    file << spaces;
    file.seekp(cur_pos);
    file << x;
    file.clear();
    file.seekp(cur_pos);
}

void Tape::rewind() {
    op_time += config.tape_rewind_delay;
    file.clear();
    file.seekp(0);
    cur_pos = 0;
}

size_t Tape::get_len() const {
    file.seekg(0, std::ios_base::end);
    size_t size = file.tellg();
    file.clear();
    file.seekp(cur_pos);
    return size;
}

int Tape::get_cur_pos() const {
    return cur_pos;
}

void write_file(Tape &tape, std::ofstream &out) {
    int x;
    tape.file.seekp(0);
    while (tape.file >> x) {
        out << x << " ";
    }
    tape.file.clear();
    tape.file.seekp(tape.cur_pos);
}

int Tape::get_op_time() const {
    return op_time;
}

void Tape::reset_op_time() const {
    op_time = 0;
}
