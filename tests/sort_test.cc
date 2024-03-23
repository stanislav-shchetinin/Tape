#include <gtest/gtest.h>
#include "TapeSort.h"

TEST(Sort, TapeSort) {
    std::string input_file = "../tests/input.in";
    std::string output_file = "../tests/output.out";
    std::string config_file = "../tests/configuration.json";
    const int RAM_SIZE = 4;

    std::vector <int> arr_sort;
    std::ifstream is(input_file);
    int x;

    while (is >> x) {
        arr_sort.push_back(x);
    }
    std::sort(arr_sort.begin(), arr_sort.end());

    Config config = read_config_file(config_file);
    std::vector <int> ram(RAM_SIZE);
    Tape tape_in(config, input_file);
    Tape tape_out(config, tape_in.get_len());

    TapeSort tapeSort(tape_in, tape_out, ram, config);
    tapeSort.sort(output_file);

    std::ifstream iso(output_file);
    int ind = 0;
    while (iso >> x) {
        EXPECT_EQ(arr_sort[ind], x);
        ++ind;
    }

}