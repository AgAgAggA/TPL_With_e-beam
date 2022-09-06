#pragma once
#include <string>
#include "InputDataHandler/InputData.hpp"

class Parser
{
public:
    void read_file(InputData &, char *argv[]);
    void output_file(InputData &, char *argv[]);
};