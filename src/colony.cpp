/**
 * \file colony.cpp
 * \brief Colony.
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
#include "colony.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constructeurs et destructeurs.
////////////////////////////////////////////////////////////////////////////////

colony::colony (void)
:
    _generations_count (0),
    _population_size (colony::DEFAULT_POPULATION_SIZE),
    _weight_number (random_factory::DEFAULT_WEIGHT_NUMBER),
    _head_neurons_number (random_factory::DEFAULT_HEAD_NEURONS_NUMBER),
    _weight_range (random_factory::DEFAULT_RANGE),
    _purge (colony::_purge_loosers)
{
}

colony::colony (const colony & c)
:
    _generations_count (c._generations_count),
    _population_size (c._population_size),
    _weight_number (c._weight_number),
    _head_neurons_number (c._head_neurons_number),
    _weight_range (c._weight_range),
    _purge (c._purge)
{
    _fitness = c._fitness;
    _networks = c._networks;
}

colony::colony (const neuron_network_fitness & fitness,
    unsigned int population_size, double weight_range,
    colony_purge_strategy strategy, unsigned int weight_number,
    unsigned int head_neurons_number)
:
    _generations_count (0),
    _population_size (population_size),
    _weight_number (weight_number),
    _head_neurons_number (head_neurons_number),
    _weight_range (weight_range)
{
    set_purge_strategy (strategy);
    _fitness = fitness;
    for (unsigned int i = 0; i < _population_size; ++i)
    {
        neuron_network n = random_factory::random_neuron_network (_weight_number, _head_neurons_number, _weight_range);
        _networks.push_back (n);
    }
    colony::_sort (_networks, _fitness);
}

colony::~colony (void)
{
}

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
////////////////////////////////////////////////////////////////////////////////

bool colony::has_fit_network (void) const
{
    return utilities::double_equals (0.0, _fitness.fitness_of (_networks[0]));
}

neuron_network colony::best_network (void) const
{
    return _networks[0];
}

double colony::best_fitness (void) const
{
    return _fitness.fitness_of (_networks[0]);
}

double colony::mean_fitness (void) const
{
    double mean = 0.0;
    for (unsigned int i = 0; i < _population_size; ++i)
        mean += _fitness.fitness_of (_networks[i]);

    return mean / _population_size;
}

unsigned int colony::generations_count (void) const
{
    return _generations_count;
}

////////////////////////////////////////////////////////////////////////////////
// Modificateurs.
////////////////////////////////////////////////////////////////////////////////

void colony::turn (void)
{
    _generations_count++;

    for (unsigned int i = 0; i < _population_size; ++i)
    {
        evolution_action choice = evolution::choose_action ();
        if (choice == EVOLUTION_CLONE)
            _clone (i);
        else if (choice == EVOLUTION_CROSS_OVER)
            _cross_over (i);
        else if (choice == EVOLUTION_MUTATE)
            _mutate (i);
    }
}

void colony::set_fitness (const neuron_network_fitness & fitness)
{
    _fitness = fitness;
}

void colony::set_purge_strategy (colony_purge_strategy strategy)
{
    switch (strategy)
    {
        case COLONY_PURGE_RANDOMLY:
            _purge = colony::_purge_randomly; break;
        case COLONY_PURGE_LOOSERS:
        case COLONY_PURGE_DEFAULT:
        default:
            _purge = colony::_purge_loosers; break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Modificateurs privés.
////////////////////////////////////////////////////////////////////////////////

void colony::_clone (unsigned int i)
{
    neuron_network clone = evolution::clone (_networks[i]);
    _networks.push_back (clone);
}

void colony::_cross_over (long int i)
{
    int a = i;
    int b = i;

    while (a == i)
        a = utilities::random_int (0, _population_size);

    while (b == i || b == a)
        b = utilities::random_int (0, _population_size);

    neuron_network & a_b = _networks[b];;
    if (_fitness.compare_networks (_networks[a], _networks[b]) < 0)
        a_b = _networks[a];

    neuron_network son = evolution::cross_over (_networks[i], a_b);
            _networks.push_back (son);
}

void colony::_mutate (unsigned int i)
{
    evolution::randomly_mutate (_networks[i], _weight_number, _weight_range);
}

void colony::_sort (colony_networks & networks, const neuron_network_fitness & fitness)
{
    evolution::set_fitness (fitness);
    std::sort (networks.begin (), networks.end (), evolution::network_lower_than);
}

void colony::_purge_loosers (colony_networks & networks,
    const neuron_network_fitness & fitness, unsigned int population_size)
{
    colony::_sort (networks, fitness);
    networks.erase (networks.begin () + population_size, networks.end ());
}

void colony::_purge_randomly (colony_networks & networks,
    const neuron_network_fitness & fitness, unsigned int population_size)
{
    for (colony_networks::size_type size = networks.size (); size > population_size; size = networks.size ())
    {
        int random_index = utilities::random_int (0, size);
        colony_networks::iterator element = networks.begin () + random_index;
        networks.erase (element, element + 1);
    }
    colony::_sort (networks, fitness);
}
