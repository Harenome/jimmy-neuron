/**
 * \file main.cpp
 * \brief Main.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \author MEYER Jérémy
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#include <iostream>
#include <sysexits.h>

int main (int argc, char ** argv)
{
    if (argc > 1)
    {
        std::cout << "Error: too many arguments." << std::endl;
        std::cout << "Usage: " << argv[0] << std::endl;
        return EX_USAGE;
    }

    std::cout << "Jimmy Neuron" << std::endl;

    return 0;
}
