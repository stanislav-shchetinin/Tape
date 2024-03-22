//
// Created by stass on 22.03.2024.
//

#include "TapeSort.h"

#include <iostream>

TapeSort::TapeSort(const Tape& tape_in,
         const Tape& tape_out,
         const std::vector<int> &ram,
         const Config& config_add)
        : tape_in(tape_in)
        , tape_out(tape_out)
        , ram(ram)
        , config_add(config_add) {}

void TapeSort::sort(const std::string& output_name) {

    Tape tape_add(config_add, tape_in.get_len());
    size_t last_pos = 0;
    size_t cnt_num = tape_in.get_len() / OFFSET;
    bool is_add = true;
    int size_add = 0;
    int size_out = 0;

    while (last_pos < cnt_num) {
        size_t par_pos = last_pos;
        for (; last_pos < std::min(par_pos + ram.size(), cnt_num); ++last_pos) {
            ram[last_pos - par_pos] = tape_in.read();
            tape_in.shift_pos_right();
        }
        std::sort(ram.begin(), ram.begin() + static_cast<int>(last_pos - par_pos));

        if (is_add) {
            size_add = 0;
            tape_out.rewind();
            tape_add.rewind();
            size_t cur_pos_ram = 0;

            while (tape_out.get_cur_pos() / OFFSET < size_out
            && (cur_pos_ram < ram.size() && cur_pos_ram < last_pos - par_pos)) {
                int vo = tape_out.read();
                int vr = ram[cur_pos_ram];

                if (vo < vr) {
                    tape_add.write(vo);
                    tape_out.shift_pos_right();
                } else {
                    tape_add.write(vr);
                    ++cur_pos_ram;
                }
                tape_add.shift_pos_right();
                ++size_add;
            }

            while (tape_out.get_cur_pos() / OFFSET < size_out) {
                int vo = tape_out.read();
                tape_add.write(vo);
                tape_out.shift_pos_right();
                tape_add.shift_pos_right();
                ++size_add;
            }

            while (cur_pos_ram < ram.size() && cur_pos_ram < last_pos - par_pos) {
                int vr = ram[cur_pos_ram];
                tape_add.write(vr);
                ++cur_pos_ram;
                tape_add.shift_pos_right();
                ++size_add;
            }
            is_add = false;

        } else {

            size_out = 0;
            tape_out.rewind();
            tape_add.rewind();
            size_t cur_pos_ram = 0;

            while (tape_add.get_cur_pos() / OFFSET < size_add
                   && (cur_pos_ram < ram.size() && cur_pos_ram < last_pos - par_pos)) {
                int va = tape_add.read();
                int vr = ram[cur_pos_ram];

                if (va < vr) {
                    tape_out.write(va);
                    tape_add.shift_pos_right();
                } else {
                    tape_out.write(vr);
                    ++cur_pos_ram;
                }
                tape_out.shift_pos_right();
                ++size_out;
            }

            while (tape_add.get_cur_pos() / OFFSET < size_add) {
                int vo = tape_add.read();
                tape_out.write(vo);
                tape_add.shift_pos_right();
                tape_out.shift_pos_right();
                ++size_out;
            }

            while (cur_pos_ram < ram.size() && cur_pos_ram < last_pos - par_pos) {
                int vr = ram[cur_pos_ram];
                tape_out.write(vr);
                ++cur_pos_ram;
                tape_out.shift_pos_right();
                ++size_out;
            }
            is_add = true;
        }

    }
    std::ofstream out(output_name);
    if (is_add) {
        write_file(tape_out, out);
    } else {
        write_file(tape_add, out);
    }

}

