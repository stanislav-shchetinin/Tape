#include <iostream>
#include <vector>
#include "config.h"
#include "Tape.h"
#include "TapeSort.h"

#define ERROR_CODE 1

void argc_check(int argc) {
    if (argc != 4) {
        std::cout << "The arguments for running the program should look like:"
                     "Yadro <input-file> <output-file> <configuration.json>\n";
        exit(ERROR_CODE);
    }
}

int main(int argc, char* argv[]) {

    argc_check(argc);
    const size_t M = 4 * 4; //4 bytes for int
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string config_file = argv[3];

    std::vector<int> ram(M / 4);

    Config config = read_config_file(config_file);
    Tape tape_in(config, "../" + input_file);
    Tape tape_out(config, tape_in.get_len());

    TapeSort tapeSort(tape_in, tape_out, ram, config);
    tapeSort.sort("../" + output_file);

    return 0;
}
