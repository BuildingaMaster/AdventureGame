#pragma once
#include <sstream>
#include <streambuf>
#include <iostream>
#include <typeinfo>
#include <vector>

#include "PlayerActions.h"

#define MAX_COMMAND_SIZE 30

class PrintDisplay
{
public:
        static std::ostringstream custom_cout;

        /// @brief Print the buffer to the console, must be called.
        static void flush();

        /// @brief Print the buffer to the console without effects, must be called.
        static void no_effect_flush();

        /// @brief Handles direct input from the terminal.
        /// @param noHistory The history should be disabled.
        /// @return The command in string form.
        static std::string inputValidation(bool);

        /// @brief The history of the commands the player typed.
        static std::vector<std::string> commandHistory;

        /// @brief Displays "Press any key to continue..."
        static void pause();
private:
        static void common_flush(bool);
};