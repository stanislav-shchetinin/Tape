#include <iostream>
#include "config.h"
#include "Tape.h"

void argc_check(int argc) {
    if (argc != 4) {
        std::cout << "The arguments for running the program should look like:"
                     "Yadro <input-file> <output-file> <configuration.json>\n";
        exit(1);
    }
}

int main(int argc, char* argv[]) {

    argc_check(argc);
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string config_file = argv[3];

    Config config = read_config_file(config_file);

    Tape tape(config, "../" + input_file);

    return 0;
}
