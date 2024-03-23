#include <gtest/gtest.h>
#include "config.h"
#include "Tape.h"

#define NUM_CNT 9

std::string input_file = "../tests/input.in";
std::string config_file = "../tests/configuration.json";
Config config = read_config_file(config_file);

TEST(Tape, ShiftPosRight) {
    Tape tape(config, input_file);
    for (int i = 0; i <= NUM_CNT; ++i) {
        int ind = std::min(i, NUM_CNT - 1);
        EXPECT_EQ(ind, tape.get_cur_pos() / OFFSET);
        tape.shift_pos_right();
    }
}

TEST(Tape, ShiftPosLeft) {
    Tape tape(config, input_file);
    for (int i = 0; i <= NUM_CNT; ++i) {
        tape.shift_pos_right();
    }

    for (int i = NUM_CNT - 1; i >= -1; --i) {
        tape.shift_pos_left();
        int ind = std::max(0, i - 2);
        EXPECT_EQ(ind, tape.get_cur_pos() / OFFSET);

    }

}

TEST(Tape, Rewind) {
    Tape tape(config, input_file);
    for (int i = 0; i <= NUM_CNT / 2; ++i) {
        tape.shift_pos_right();
    }

    tape.rewind();
    EXPECT_EQ(0, tape.get_cur_pos() / OFFSET);
}

TEST(Tape, Read) {
    Tape tape(config, input_file);
    std::fstream f(input_file);

    for (size_t i = 0; i < NUM_CNT; ++i) {
        int xr, xt;
        f >> xr;
        xt = tape.read();
        tape.shift_pos_right();
        EXPECT_EQ(xr, xt);
    }

}

TEST(Tape, Write) {
    Tape tape(config, NUM_CNT * OFFSET);

    for (int i = 0; i < NUM_CNT; ++i) {
        tape.write(i);
        tape.shift_pos_right();
    }
    tape.rewind();
    for (int i = 0; i < NUM_CNT; ++i) {
        int x = tape.read();
        EXPECT_EQ(i, x);
        tape.shift_pos_right();
    }

}
