#include <gtest/gtest.h>
#include "config.h"

TEST(Config, ReadConfig) {
    std::string config_file = "../tests/configuration.json";
    Config config = read_config_file(config_file);
    EXPECT_EQ(config.recording_delay, 1000);
    EXPECT_EQ(config.read_delay, 1500);
    EXPECT_EQ(config.tape_rewind_delay, 10000);
    EXPECT_EQ(config.tape_shift_delay, 100);
}