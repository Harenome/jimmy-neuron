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

colony::colony (void)
:
_generations_count (0),
_population_size (colony::DEFAULT_POPULATION_SIZE),
_weight_number (random_factory::DEFAULT_WEIGHT_NUMBER),
_head_neurons_number (random_factory::DEFAULT_HEAD_NEURONS_NUMBER),
_weight_range (random_factory::DEFAULT_RANGE)
{
}

colony::colony (const colony & c)
: _generations_count (c._generations_count),
_population_size (c._population_size),
_weight_number (c._weight_number),
_head_neurons_number (c._head_neurons_number),
_weight_range (c._weight_range)
{
    _fitness = c._fitness;
    _networks = c._networks;
}

colony::colony (const neuron_network_fitness & fitness, unsigned int population_size, unsigned int weight_number, unsigned int head_neurons_number, double weight_range)
: _generations_count (0),
_population_size (population_size),
_weight_number (weight_number),
_head_neurons_number (head_neurons_number),
_weight_range (weight_range)
{
    _fitness = fitness;
    for (unsigned int i = 0; i < _population_size; ++i)
    {
        neuron_network n = random_factory::random_neuron_network (_weight_number, _head_neurons_number, _weight_range);
        _networks.push_back (n);
    }
    _sort ();
}

colony::~colony (void)
{
}

void colony::turn (void)
{
    _generations_count++;

    for (unsigned int i = 0; i < _population_size; ++i)
    {
        evolution_action choice = evolution::choose_action ();
        if (choice == EVOLUTION_CLONE)
        {
            neuron_network clone = evolution::clone (_networks[i]);
            _networks.push_back (clone);
        }
        else if (choice == EVOLUTION_CROSS_OVER)
        {
            int a = utilities::random_int (0, _population_size);
            int b = utilities::random_int (0, _population_size);
            while (a == b)
                b = utilities::random_int (0, _population_size);

            neuron_network & a_b = _networks[b];;
            if (_fitness.compare_networks (_networks[a], _networks[b]) < 0)
                a_b = _networks[a];

            neuron_network son = evolution::cross_over (_networks[i], a_b);
            _networks.push_back (son);
        }
        else if (choice == EVOLUTION_MUTATE)
        {
            evolution::randomly_mutate (_networks[i], _weight_number, _weight_range);
        }
    }

}

void colony::set_fitness (const neuron_network_fitness & fitness)
{
    _fitness = fitness;
}

bool colony::has_fit_network (void) const
{
    return utilities::double_equals (0.0, _fitness.fitness_of (_networks[0]));
}

neuron_network colony::best_network (void) const
{
    return _networks[0];
}

unsigned int colony::generations_count (void) const
{
    return _generations_count;
}

void colony::_sort (void)
{
    evolution::set_fitness (_fitness);
    std::sort (_networks.begin (), _networks.end (), evolution::network_lower_than);
}

void colony::_purge (void)
{
    _sort ();
    _networks.erase (_networks.begin () + _population_size, _networks.end ());
}
