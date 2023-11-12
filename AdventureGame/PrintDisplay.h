#pragma once
#include <sstream>
#include <streambuf>
#include <iostream>
#include <typeinfo>

#include "PlayerActions.h"
#include "CommonGameObjects.h"

class PrintDisplay : public CommonGameObjects
{
public:
        static std::ostringstream custom_cout;

        /// @brief Print the buffer to the console, must be called.
        static void flush();

        /// @brief Print the buffer to the console without effects, must be called.
        static void no_effect_flush();
private:
        static void common_flush(bool);
};