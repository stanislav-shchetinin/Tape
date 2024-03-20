#include <iostream>
#include <fstream>
#include "json.hpp"

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << "The arguments for running the program should look like:"
                     "main.cpp <input-file> <output-file> <configuration.json>\n";
        exit(1);
    }
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string config_file = argv[3];

    std::cout << input_file << " " << output_file << " " << config_file << " " << std::endl;

    using json = nlohmann::json;
    std::ifstream f("../" + config_file);
    json data = json::parse(f);

    int recording_delay = data["recording_delay"];
    std::cout << recording_delay << std::endl;

    return 0;
}
