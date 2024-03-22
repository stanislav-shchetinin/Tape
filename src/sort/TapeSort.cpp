//
// Created by stass on 22.03.2024.
//

#include "TapeSort.h"

TapeSort::TapeSort(const Tape& tape_in,
         const Tape& tape_out,
         const std::vector<int> &ram,
         const Config& config_add)
        : tape_in(tape_in)
        , tape_out(tape_out)
        , ram(ram)
        , config_add(config_add) {}


void TapeSort::two_point_merge(std::vector <int>& ram,
                     size_t size_ram,
                     Tape& tape_read, int& size_tape_read,
                     Tape& tape_write, int& size_tape_write) {

    size_tape_write = 0;
    tape_read.rewind();
    tape_write.rewind();
    size_t cur_pos_ram = 0;

    while (tape_read.get_cur_pos() / OFFSET < size_tape_read
           && (cur_pos_ram < ram.size() && cur_pos_ram < size_ram)) {
        int vo = tape_read.read();
        int vr = ram[cur_pos_ram];

        if (vo < vr) {
            tape_write.write(vo);
            tape_read.shift_pos_right();
        } else {
            tape_write.write(vr);
            ++cur_pos_ram;
        }
        tape_write.shift_pos_right();
        ++size_tape_write;
    }

    while (tape_read.get_cur_pos() / OFFSET < size_tape_read) {
        int vo = tape_read.read();
        tape_write.write(vo);
        tape_read.shift_pos_right();
        tape_write.shift_pos_right();
        ++size_tape_write;
    }

    while (cur_pos_ram < ram.size() && cur_pos_ram < size_ram) {
        int vr = ram[cur_pos_ram];
        tape_write.write(vr);
        ++cur_pos_ram;
        tape_write.shift_pos_right();
        ++size_tape_write;
    }
}

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
            two_point_merge(ram, last_pos - par_pos, tape_out, size_out, tape_add, size_add);
            is_add = false;
        } else {

            two_point_merge(ram, last_pos - par_pos, tape_add, size_add, tape_out, size_out);
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

