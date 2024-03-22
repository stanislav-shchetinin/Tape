//
// Created by stass on 22.03.2024.
//

#ifndef YADRO_TAPESORT_H
#define YADRO_TAPESORT_H


#include "Tape.h"

class TapeSort {
private:
    Tape tape_in;
    Tape tape_out;
    std::vector<int> ram;
    const Config config_add;
public:
    TapeSort(const Tape& tape_in,
             const Tape& tape_out,
             const std::vector<int> &ram,
             const Config& config_add);

    void sort(const std::string&);
};


#endif //YADRO_TAPESORT_H
