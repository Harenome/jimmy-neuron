/**
 * \file neuron_network.hpp
 * \brief Réseau de neurones.
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
#ifndef __NEURON_NETWORK_HPP__
#define __NEURON_NETWORK_HPP__

#include <list>
#include <vector>
#include <cmath>
#include <ostream>
#include <istream>
#include <limits>

#include "neuron.hpp"

////////////////////////////////////////////////////////////////////////////////
// Typedefs.
////////////////////////////////////////////////////////////////////////////////

typedef std::vector<neuron>::iterator neuron_network_iterator;
typedef std::vector<neuron>::const_iterator neuron_network_const_iterator;

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

class neuron_network
{
public:
    neuron_network (void);
    neuron_network (const neuron_network & x);
    neuron_network (const neuron & a, const neuron & b, const neuron & c, const neuron & out);
    neuron_network (const std::vector<neuron> head, const neuron & out);
    ~neuron_network (void);
    std::vector<neuron> head_neurons (void) const;
    neuron out_neuron (void) const;
    bool attempt (const std::list<bool> & inputs) const;
    bool equals (const neuron_network & x) const;
    bool lower_than (const neuron_network & x) const;
    void set_out_neuron (const neuron & out);
    void set_head_neurons (const std::vector<neuron> & head);
    long double accumulate (const std::list<bool> & inputs) const;
    void swap (neuron_network & x);
    neuron_network & operator= (neuron_network x);
    std::ostream & write_to (std::ostream & os) const;
    std::istream & read_from (std::istream & is);

    static void set_epsilon (double epsilon);
    static double epsilon (void);
private:
    neuron _out;
    std::vector<neuron> _head;
    std::list<bool> _inner_inputs (const std::list<bool> & inputs) const;

    static double _EPSILON;
    static const double _DEFAULT_EPSILON;
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

void swap (neuron_network & a, neuron_network & b);

std::istream & operator>> (std::istream & is, neuron_network & x);

std::ostream & operator<< (std::ostream & os, const neuron_network & x);

#endif /* __NEURON_NETWORK_HPP__ */
