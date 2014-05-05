/**
 * \file neuron_network.cpp
 * \brief XOR Neurones.
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
#include "neuron_network.hpp"

////////////////////////////////////////////////////////////////////////////////
// Variables et fonctions statiques.
////////////////////////////////////////////////////////////////////////////////

const double neuron_network::_DEFAULT_EPSILON = std::numeric_limits<double>::epsilon ();
double neuron_network::_EPSILON = neuron_network::_DEFAULT_EPSILON;

double neuron_network::epsilon (void)
{
    return neuron_network::_EPSILON;
}

void neuron_network::set_epsilon (double epsilon)
{
    neuron_network::_EPSILON = epsilon;
}

////////////////////////////////////////////////////////////////////////////////
// Constructeurs.
////////////////////////////////////////////////////////////////////////////////

neuron_network::neuron_network (void)
{
}

neuron_network::neuron_network (const neuron_network & x)
: _out (x._out)
{
    _head = x._head;
}

neuron_network::neuron_network (const neuron & a, const neuron & b, const neuron & c, const neuron & out)
: _out (out)
{
    _head.push_back (a);
    _head.push_back (b);
    _head.push_back (c);
}

neuron_network::neuron_network (const std::vector<neuron> head, const neuron & out)
: _out (out)
{
    _head = head;
}

////////////////////////////////////////////////////////////////////////////////
// Destructeurs.
////////////////////////////////////////////////////////////////////////////////

neuron_network::~neuron_network (void)
{
}

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
////////////////////////////////////////////////////////////////////////////////

std::vector<neuron> neuron_network::head_neurons (void) const
{
    return _head;
}

neuron neuron_network::out_neuron (void) const
{
    return _out;
}

std::list<bool> neuron_network::_inner_inputs (const std::list<bool> & inputs) const
{
    std::list<bool> inner_inputs;
    for (neuron_network_const_iterator it = _head.begin (); it != _head.end (); ++it)
        inner_inputs.push_back (it->attempt (inputs));

    return inner_inputs;
}

long double neuron_network::accumulate (const std::list<bool> & inputs) const
{
    std::list<bool> inner_inputs = _inner_inputs (inputs);
    return _out.accumulate (inner_inputs);
}

bool neuron_network::attempt (const std::list<bool> & inputs) const
{
    std::list<bool> inner_inputs = _inner_inputs (inputs);
    return _out.attempt (inner_inputs);
}

////////////////////////////////////////////////////////////////////////////////
// Modificateurs.
////////////////////////////////////////////////////////////////////////////////

void neuron_network::set_out_neuron (const neuron & out)
{
    _out = out;
}

void neuron_network::set_head_neurons (const std::vector<neuron> & head)
{
    _head = head;
}

////////////////////////////////////////////////////////////////////////////////
// Divers.
////////////////////////////////////////////////////////////////////////////////

void neuron_network::swap (neuron_network & x)
{
    _head.swap (x._head);
    _out.swap (x._out);
}

neuron_network & neuron_network::operator= (neuron_network x)
{
    this->swap (x);
    return * this;
}

std::ostream & neuron_network::write_to (std::ostream & os) const
{
    os << "Out: " << _out << std::endl;
    os << "Head: " << _head.size () << " neurons:" << std::endl;
    for (neuron_network_const_iterator it = _head.begin (); it != _head.end (); ++it)
        os << " " << * it;
    return os;
}

std::istream & neuron_network::read_from (std::istream & is)
{
    neuron out;
    std::vector<neuron> head;
    unsigned int head_size;
    std::string out_section, head_section, description;

    is >> out_section >> out >> head_section >> head_size >> description;

    bool success = ! is.fail ()
        && out_section == "Out:"
        && head_section == "Head:"
        && description == "neurons:";

    if (! success)
        is.setstate (std::istream::failbit);

    for (unsigned int i = 0; success && i < head_size; ++i)
    {
        neuron head_neuron;
        is >> head_neuron;
        success = ! is.fail ();
        head.push_back (head_neuron);
    }

    if (success)
    {
        neuron_network x (head, out);
        this->swap (x);
    }

    return is;
}

void swap (neuron_network & a, neuron_network & b)
{
    a.swap (b);
}

std::istream & operator>> (std::istream & is, neuron_network & x)
{
    return x.read_from (is);
}

std::ostream & operator<< (std::ostream & os, const neuron_network & x)
{
    return x.write_to (os);
}
