/**
 * \file evolution.cpp
 * \brief Evolution.
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
#include "evolution.hpp"

////////////////////////////////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////////////////////////////////

unsigned int evolution::_probability_mutation = evolution::DEFAULT_PROBABILITY_MUTATION;
unsigned int evolution::_probability_cross_over = evolution::DEFAULT_PROBABILITY_CROSS_OVER;
unsigned int evolution::_probability_cloning = evolution::DEFAULT_PROBABILITY_CLONING;
neuron_network_fitness evolution::_fitness;

////////////////////////////////////////////////////////////////////////////////
// Probabilités.
////////////////////////////////////////////////////////////////////////////////

unsigned int evolution::probability_mutation (void)
{
    return evolution::_probability_mutation;
}

unsigned int evolution::probability_cross_over (void)
{
    return evolution::_probability_cross_over;
}

unsigned int evolution::probability_cloning (void)
{
    return evolution::_probability_cloning;
}

void evolution::set_probabilities (unsigned int cross_over, unsigned int mutation, unsigned int cloning)
{
    if (cross_over + mutation + cloning == 100)
    {
        evolution::_probability_mutation = mutation;
        evolution::_probability_cross_over = cross_over;
        evolution::_probability_cloning = cloning;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Évolution des réseaux.
////////////////////////////////////////////////////////////////////////////////

void evolution::randomly_mutate (neuron_network & n, unsigned int weight_number, double weight_range)
{
    neuron new_neuron = random_factory::random_neuron (weight_number, weight_range);
    int dice = utilities::random_int (0, n.head_neurons_number () + 1);
    int head_number = n.head_neurons_number ();

    if (dice < head_number)
    {
        std::vector<neuron> head = n.head_neurons ();
        head[dice]  = new_neuron;
        n.set_head_neurons (head);
    }
    else
    {
        n.set_out_neuron (new_neuron);
    }
}

neuron_network evolution::clone (const neuron_network & n)
{
    neuron_network clone (n);
    return clone;
}

static inline neuron _mean_neuron (const neuron & a, const neuron & b)
{
    neuron new_neuron (a);
    for (unsigned int i = 0; i < a.weight_number (); ++i)
    {
        new_neuron[i] += b[i];
        new_neuron[i] /= 2;
    }

    return new_neuron;
}

static inline std::vector<neuron> _mean_head (const neuron_network & a, const neuron_network & b)
{
    std::vector<neuron> head_a = a.head_neurons ();
    std::vector<neuron> head_b = a.head_neurons ();

    std::vector<neuron> son_head;
    for (unsigned int i = 0; i < head_a.size (); ++i)
    {
        neuron n = _mean_neuron (head_a[i], head_b[i]);
        son_head.push_back (n);
    }

    return son_head;
}

neuron_network evolution::cross_over (const neuron_network & a, const neuron_network & b)
{
    std::vector<neuron> son_head = _mean_head (a, b);
    neuron son_out = _mean_neuron (a.out_neuron (), b.out_neuron ());

    neuron_network son (son_head, son_out);

    return son;
}

evolution_action evolution::choose_action (void)
{
    int dice = utilities::random_int (0, 100);
    long int clone = evolution::_probability_cloning;
    long int mutate = clone + evolution::_probability_mutation;
    long int cross = mutate + evolution::_probability_cross_over;

    evolution_action choice;
    if (dice < clone)
        choice = EVOLUTION_CLONE;
    else if (dice < mutate)
        choice = EVOLUTION_MUTATE;
    else if (dice < cross)
        choice = EVOLUTION_CROSS_OVER;
    else
        choice = EVOLUTION_UNKNOWN;

    return choice;
}

////////////////////////////////////////////////////////////////////////////////
// Comparaison des réseaux.
////////////////////////////////////////////////////////////////////////////////

void evolution::set_fitness (const neuron_network_fitness & fitness)
{
    evolution::_fitness = fitness;
}

neuron_network_fitness evolution::current_fitness (void)
{
    return evolution::_fitness;
}

bool evolution::network_lower_than (const neuron_network & a, const neuron_network & b)
{
    int comparison = evolution::_fitness.compare_networks (a, b);
    return comparison == -1;
}
