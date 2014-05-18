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

#include "parse_cli.hpp"
#include "utilities.hpp"
#include "truth_table.hpp"
#include "neuron_network.hpp"
#include "neuron_network_fitness.hpp"
#include "colony.hpp"
#include "plot.hpp"

static const unsigned int MAX_GEN = 2000;

static inline void print_help (const char * program_name)
{
    std::cout << "Usage: " << program_name << " [--option=value | --option=arguments,comma,separated]" << std::endl
    << "\t--max-generations=N\n\t\t"
        "Set the maximum number of generations to N.\n"
        "\t\tDefaults to " << MAX_GEN << ".\n"
    << "\t--colony-size=N\n"
        "\t\tSet the colony size to N.\n"
        "\t\tDefaults to " << colony::DEFAULT_POPULATION_SIZE << ".\n"
    << "\t--weight-range=N\n"
        "\t\tSet the range of the weights.\n"
        "\t\tDefaults to " << random_factory::DEFAULT_RANGE << ".\n"
    << "\t--probabilities=N,O,P\n"
        "\t\tSet the probabilites of cross-over, mutation and cloning to N, O and P.\n"
        "\t\tDefaults to " << evolution::DEFAULT_PROBABILITY_CROSS_OVER << ","
        << evolution::DEFAULT_PROBABILITY_MUTATION << ","
        << evolution::DEFAULT_PROBABILITY_CLONING << ".\n"
    << "\t--temp-file=path\n"
        "\t\tSet the path to use for the temporary file.\n"
        "\t\tDefaults to \"" << plot::DEFAULT_TEMP_FILE_PATH << "\".\n"
    ;
}

static inline void print_version (void)
{
    std::cout << "Jimmy neuron, version 1.1" << std::endl;
    std::cout << "Written by MEYER Jérémy, RANAIVOARIVONY RAZANAJATO Harenome" << std::endl;
}

static inline bool check_help_or_version (int argc, char ** argv)
{
    bool found = true;

    std::string dummy;

    if (parse_cli::option_is_given (argc, argv, "help", dummy))
        print_help (argv[0]);
    else if (parse_cli::option_is_given (argc, argv, "version", dummy))
        print_version ();
    else
        found = false;

    return found;
}

int main (int argc, char ** argv)
{
    if (check_help_or_version (argc, argv))
        return 0;

    /* Ne pas oublier les initialisations ! */
    utilities::new_seed ();
    neuron_network::init_lists ();
    truth_table exclusive_or (false, true, true, false);
    neuron_network_fitness fitness (exclusive_or);

    /* Variables */
    unsigned int max_generations = MAX_GEN;
    unsigned int population_size = colony::DEFAULT_POPULATION_SIZE;
    double weight_range = random_factory::DEFAULT_RANGE;
    unsigned int cross_over = evolution::DEFAULT_PROBABILITY_CROSS_OVER;
    unsigned int mutation = evolution::DEFAULT_PROBABILITY_MUTATION;
    unsigned int cloning = evolution::DEFAULT_PROBABILITY_CLONING;
    std::string temp_file_path = plot::DEFAULT_TEMP_FILE_PATH;

    /* Lecture (très naïve (parcours de argv à chaque fois !!)) des arguments
     * de la ligne de commande.
     */
    parse_cli::set_unsigned_int (argc, argv, "colony-size", population_size);
    parse_cli::set_unsigned_int (argc, argv, "max-generations", max_generations);
    parse_cli::set_double (argc, argv, "weight-range", weight_range);
    parse_cli::set_probabilities (argc, argv, cross_over, mutation, cloning);
    parse_cli::set_file_path (argc, argv, "temp-file", temp_file_path);

    /* Seconde vague d'initialisations. */
    evolution::set_probabilities (cross_over, mutation, cloning);
    colony c (fitness, population_size, weight_range);
    /* c.set_purge_strategy (COLONY_PURGE_RANDOMLY); */

    std::vector<double> best;
    std::vector<double> mean;

    /* Pour la génération 0. */
    best.push_back (c.best_fitness ());
    mean.push_back (c.mean_fitness ());

    for (unsigned int i = 0; ! c.has_fit_network () && i < max_generations; ++i)
    {
        c.turn ();
        best.push_back (c.best_fitness ());
        mean.push_back (c.mean_fitness ());
    }

    /* Affichage du meilleur réseau. */
    neuron_network n = c.best_network ();
    std::cout << c.generations_count () << " generations" << std::endl;
    std::cout << n << std::endl;

    /* Affichage du graphe. */
    plot p (best, mean, temp_file_path);
    p.display ();

    return 0;
}
