/**
 * \file utilities.cpp
 * \brief Utilities
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
#include "utilities.hpp"

////////////////////////////////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////////////////////////////////

unsigned int utilities::_SEED = time (NULL);
const double utilities::_EPSILON_DOUBLE_DEFAULT = std::numeric_limits<double>::epsilon ();
double utilities::_EPSILON_DOUBLE = utilities::_EPSILON_DOUBLE_DEFAULT;

////////////////////////////////////////////////////////////////////////////////
// Fonctions pour les doubles.
////////////////////////////////////////////////////////////////////////////////

bool utilities::double_equals (double a, double b)
{
    return std::fabs (a - b) < utilities::_EPSILON_DOUBLE;
}

double utilities::double_epsilon (void)
{
    return utilities::_EPSILON_DOUBLE;
}

void utilities::set_double_epsilon (double epsilon)
{
    utilities::_EPSILON_DOUBLE = epsilon;
}

////////////////////////////////////////////////////////////////////////////////
// Fonctions pour le pseudo-aléatoire.
////////////////////////////////////////////////////////////////////////////////

bool utilities::random_bool (void)
{
    int r = utilities::random_int (0, 1);
    return r == 1;
}

int utilities::random_int (int minimum, int maximum)
{
    return minimum + std::rand () / (RAND_MAX / (maximum - minimum));
}

double utilities::random_double (double minimum, double maximum)
{
    return minimum + static_cast <double> (std::rand ()) / (static_cast <double> (RAND_MAX) / (maximum - minimum));
}

void utilities::new_seed (void)
{
    _SEED = static_cast <unsigned int> (std::time (NULL));
    std::srand (_SEED);
}

void utilities::set_seed (unsigned int seed)
{
    _SEED = seed;
    std::srand (_SEED);
}

unsigned int utilities::current_seed (void)
{
    return _SEED;
}
