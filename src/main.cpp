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

#include "utilities.hpp"
#include "truth_table.hpp"
#include "neuron_network.hpp"
#include "neuron_network_fitness.hpp"
#include "colony.hpp"

static const unsigned int MAX_GENERATIONS = 2000;

int main (int argc, char ** argv)
{
    if (argc > 1)
    {
        std::cout << "Error: too many arguments." << std::endl;
        std::cout << "Usage: " << argv[0] << std::endl;
        return EX_USAGE;
    }

    std::cout << "Jimmy Neuron" << std::endl;

    /* Ne pas oublier les initialisations ! */
    utilities::new_seed ();
    neuron_network::init_lists ();
    truth_table exclusive_or (false, true, true, false);
    neuron_network_fitness fitness (exclusive_or);

    /* evolution::set_probabilities (100, 0, 0); */
    colony c (fitness, 100);
    c.set_purge_strategy (COLONY_PURGE_RANDOMLY);

    for (unsigned int i = 0; ! c.has_fit_network () && i < MAX_GENERATIONS; ++i)
    {
        c.turn ();
        std::cout << "Best: " << c.best_fitness () << ", Mean: " << c.mean_fitness () << std::endl;
    }

    neuron_network n = c.best_network ();
    std::cout << c.generations_count () << " generations" << std::endl;
    std::cout << n << std::endl;

    return 0;
}
