#ifndef MYHEADER_H
#define MYHEADER_H

#include <string>
#include "RingBuff.h"

int process_line(std::string line);
int process_line2(std::string line, RingBuff* buffer);
int get_from_line(std::string line);

#endif
