/**
 * \file random_factory.cpp
 * \brief Random factory.
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
#include "random_factory.hpp"

////////////////////////////////////////////////////////////////////////////////
// Fonctions et variables statiques.
////////////////////////////////////////////////////////////////////////////////

const double random_factory::DEFAULT_RANGE = 2.0;

neuron random_factory::random_neuron (unsigned int weight_number, double weight_range)
{
    std::vector<double> weights;
    for (unsigned int i = 0; i < weight_number; ++i)
        weights.push_back (utilities::random_double (weight_range, -weight_range));
    neuron n (weights);

    return n;
}

neuron_network random_factory::random_neuron_network (unsigned int weight_number, unsigned int head_neurons_number, double weight_range)
{
    std::vector<neuron> head;
    for (unsigned int i = 0; i < head_neurons_number; ++i)
        head.push_back (random_factory::random_neuron (weight_number, weight_range));
    neuron out = random_factory::random_neuron (weight_number, weight_range);
    neuron_network network (head, out);

    return network;
}
