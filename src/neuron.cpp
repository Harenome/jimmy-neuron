/**
 * \file neuron.cpp
 * \brief Neurone.
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
#include "neuron.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constructeurs.
////////////////////////////////////////////////////////////////////////////////

neuron::neuron (void)
{
}

neuron::neuron (const neuron & n)
{
    _weights = n._weights;
}

neuron::neuron (const std::vector<double> & weights)
{
    _weights = weights;
}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs.
////////////////////////////////////////////////////////////////////////////////

neuron::~neuron (void)
{
}

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
////////////////////////////////////////////////////////////////////////////////

long double neuron::accumulate (const std::list<bool> & input) const
{
    long double accumulator = 0.0;

    std::list<bool>::const_iterator it = input.begin ();
    std::vector<double>::const_iterator jt = _weights.begin ();
    for ( ; jt != end (); ++it, ++jt)
        if (* it)
            accumulator += * jt;

    return accumulator;
}

bool neuron::attempt (const std::list<bool> & input) const
{
    bool result = input.size () >= _weights.size ();

    if (result)
        result = accumulate (input) >= 0.5;

    return result;
}

double & neuron::operator[] (unsigned int index)
{
    return _weights.at (index);

}
const double & neuron::operator[] (unsigned int index) const
{
    return _weights.at (index);
}

neuron_iterator neuron::begin (void)
{
    return _weights.begin ();
}

neuron_const_iterator neuron::begin (void) const
{
    return _weights.begin ();
}

neuron_iterator neuron::end (void)
{
    return _weights.end ();
}

neuron_const_iterator neuron::end (void) const
{
    return _weights.end ();
}

neuron_weights neuron::weights (void) const
{
    return _weights;
}

neuron_size_type neuron::weight_number (void) const
{
    return _weights.size ();
}

////////////////////////////////////////////////////////////////////////////////
// Modificateurs.
////////////////////////////////////////////////////////////////////////////////

void neuron::add_weight (double weight)
{
    _weights.push_back (weight);
}

void neuron::set_weight (unsigned int index, double weight)
{
    if (index < weight_number ())
        operator[] (index) = weight;
}

////////////////////////////////////////////////////////////////////////////////
// Divers.
////////////////////////////////////////////////////////////////////////////////

void neuron::swap (neuron & n)
{
    _weights.swap (n._weights);
}

neuron & neuron::operator= (neuron n)
{
    this->swap (n);
    return * this;
}

std::ostream & neuron::write_to (std::ostream & os) const
{
    os << _weights.size () << " weights:";
    for (neuron_const_iterator it = begin (); it != end (); ++it)
        os << " " << * it;
    return os;
}

std::istream & neuron::read_from (std::istream & is)
{
    neuron new_neuron;
    unsigned int weight_count;
    std::string str;

    is >> weight_count >> str;

    bool success = ! is.fail () && str == "weights:";

    if (! success)
        is.setstate (std::istream::failbit);

    for (unsigned int i = 0; success && i < weight_count; ++i)
    {
        double weight;
        is >> weight;
        success = ! is.fail ();
        new_neuron.add_weight (weight);
    }

    if (success)
        this->swap (new_neuron);

    return is;
}

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

void swap (neuron & a, neuron & b)
{
    a.swap (b);
}

std::istream & operator>> (std::istream & is, neuron & n)
{
    return n.read_from (is);
}

std::ostream & operator<< (std::ostream & os, const neuron & n)
{
    return n.write_to (os);
}
