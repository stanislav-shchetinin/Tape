//
// Created by stass on 25.03.2024.
//

#ifndef YADRO_ITAPE_H
#define YADRO_ITAPE_H

class ITape {
public:
    [[nodiscard]] virtual int read() const = 0;
    virtual void write(int) = 0;
    virtual void shift_pos_left() = 0;
    virtual void shift_pos_right() = 0;
    virtual void rewind() = 0;
    virtual ~ITape() = default;
};

#endif //YADRO_ITAPE_H
