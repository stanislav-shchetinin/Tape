//
// Created by stass on 21.03.2024.
//

#ifndef YADRO_TAPE_H
#define YADRO_TAPE_H

#include "config.h"
#include "ITape.h"

#define MAX_CHAR_IN_INT 11
#define OFFSET (MAX_CHAR_IN_INT + 1)

class Tape : public ITape{
private:
    static int tapes_count;
    const Config config;
    int cur_pos{};
    mutable std::fstream file;
    std::string file_name;
    const int num_tape;
    mutable int op_time{};

    explicit Tape(const Config& config);
public:
    Tape(const Config& config,
         const std::string& tape_file);
    Tape(const Config& config, size_t n);
    Tape(const Tape& other); //=delete ??
    Tape& operator=(const Tape& tape) = delete;
    size_t get_len() const;
    int get_cur_pos() const;
    int read() const override;
    void write(int) override;
    void shift_pos_left() override;
    void shift_pos_right() override;
    void rewind() override;
    int get_op_time() const;
    void reset_op_time() const;
    friend void write_file(Tape&, std::ofstream&);
    ~Tape() override = default;
};


#endif //YADRO_TAPE_H
