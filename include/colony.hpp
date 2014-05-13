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
#ifndef __COLONY_HPP__
#define __COLONY_HPP__

#include <algorithm>

#include "utilities.hpp"
#include "neuron.hpp"
#include "neuron_network.hpp"
#include "neuron_network_fitness.hpp"
#include "evolution.hpp"
#include "random_factory.hpp"

class colony
{
public:
    colony (void);
    colony (const colony & c);
    colony (const neuron_network_fitness & fitness,
        unsigned int population_size = colony::DEFAULT_POPULATION_SIZE,
        unsigned int weight_number = random_factory::DEFAULT_WEIGHT_NUMBER,
        unsigned int head_neurons_number = random_factory::DEFAULT_HEAD_NEURONS_NUMBER,
        double weight_range = random_factory::DEFAULT_RANGE
    );
    ~colony (void);
    void turn (void);
    void set_fitness (const neuron_network_fitness & fitness);
    bool has_fit_network (void) const;
    neuron_network best_network (void) const;
    double best_fitness (void) const;
    double mean_fitness (void) const;
    unsigned int generations_count (void) const;
    static const unsigned int DEFAULT_POPULATION_SIZE = 100;

private:
    unsigned int _generations_count;
    unsigned int _population_size;
    unsigned int _weight_number;
    unsigned int _head_neurons_number;
    double _weight_range;
    neuron_network_fitness _fitness;
    std::vector<neuron_network> _networks;

    void _sort (void);
    void _purge (void);
};

#endif /* __COLONY_HPP__ */
