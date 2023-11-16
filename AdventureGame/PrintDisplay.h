#pragma once
#include <sstream>
#include <streambuf>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "PlayerActions.h"

class PrintDisplay
{
public:
        static std::ostringstream custom_cout;

        /// @brief Print the buffer to the console, must be called.
        static void flush();

        /// @brief Print the buffer to the console without effects, must be called.
        static void no_effect_flush();

        static std::string inputValidation();
        static std::vector<std::string> commandHistory;
private:
        static void common_flush(bool);
};