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

        /// @brief The history of the commands the player typed (for the terminal).
        static std::vector<std::string> commandHistory;

        /// @brief A log of the commands the player typed (for debugging).
        static std::vector<std::string> logCommandVector;

        /// @brief Displays "Press any key to continue . . ."
        static void pause();

        /// @brief Displays the HitUI 
        /// @param hitBox a string of '#' (hit) and 'O' (miss). IE: "000##"
        /// @param MAX_RED How many red tiles to show (less than 24)
        /// @param time_to_react How fast the cursor moves
        /// @return If the hit succeeded.
        static bool hitScreen(string, int);

        /// @brief Displays the DodgeUI 
        /// @return If the player dodged.
        static bool dodgeScreen();

        /// @brief Print a cool looking box.
        static void printMoveBox(bool, bool, bool, bool);

#ifdef GTESTING
        static std::string GT_inStr;

        /// @brief Pretends to be the string buffer for GTESTING
        /// @param s The string to process
        static void GT_setString(std::string s);

        /// @brief Helper for GTESTING, replicates getch().
        /// @return The character at the front of the string
        static char GT_getch();
#endif
private:
        static void common_flush(bool);
};