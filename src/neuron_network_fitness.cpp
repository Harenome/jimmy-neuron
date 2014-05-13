/**
 * \file neuron_network_fitness.cpp
 * \brief Fitness.
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
#include "neuron_network_fitness.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constructeurs.
////////////////////////////////////////////////////////////////////////////////

neuron_network_fitness::neuron_network_fitness (void)
{
}

neuron_network_fitness::neuron_network_fitness (const truth_table & t)
: _table (t)
{
}

neuron_network_fitness::neuron_network_fitness (const neuron_network_fitness & nf)
: _table (nf._table)
{
}

neuron_network_fitness::~neuron_network_fitness (void)
{
}

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
////////////////////////////////////////////////////////////////////////////////

truth_table neuron_network_fitness::table (void) const
{
    return _table;
}

static inline bool is_error (bool b, double acc)
{
    bool active = acc >= 0.5;

    return active != b;
}

static inline double error_value (bool b, double acc)
{
    if (is_error (b, acc))
        return std::fabs (0.5 - acc);
    else
        return 0.0;
}

static inline double mean_error (double errors[4])
{
    double mean = 0.0;
    for (unsigned int i = 0; i < 4; ++i)
        mean += errors[i];

    return mean / 4.0;
}

double neuron_network_fitness::fitness_of (const neuron_network & n) const
{
    double acc[4];
    acc[0] = n.accumulate (neuron_network::FALSE_FALSE);
    acc[1] = n.accumulate (neuron_network::FALSE_TRUE);
    acc[2] = n.accumulate (neuron_network::TRUE_FALSE);
    acc[3] = n.accumulate (neuron_network::TRUE_TRUE);

    acc[0] = error_value (_table.result (false, false), acc[0]);
    acc[1] = error_value (_table.result (false, true), acc[1]);
    acc[2] = error_value (_table.result (true, false), acc[2]);
    acc[3] = error_value (_table.result (true, true), acc[3]);

    double error = mean_error (acc);

    return error;
}

int neuron_network_fitness::compare_networks (const neuron_network & a, const neuron_network & b) const
{
    int result = 1;
    double a_fitness = fitness_of (a);
    double b_fitness = fitness_of (b);

    if (a_fitness < b_fitness)
        result = -1;
    else if (utilities::double_equals (a_fitness, b_fitness))
        result = 0;

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// Modificateurs.
////////////////////////////////////////////////////////////////////////////////

void neuron_network_fitness::set_table (const truth_table & t)
{
    _table = t;
}

////////////////////////////////////////////////////////////////////////////////
// Divers.
////////////////////////////////////////////////////////////////////////////////

void neuron_network_fitness::swap (neuron_network_fitness & nf)
{
    _table.swap (nf._table);
}

neuron_network_fitness & neuron_network_fitness::operator= (neuron_network_fitness nf)
{
    this->swap (nf);
    return * this;
}

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

void swap (neuron_network_fitness & a, neuron_network_fitness & b)
{
    a.swap (b);
}
