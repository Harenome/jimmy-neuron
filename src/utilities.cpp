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

const double utilities::_EPSILON_DOUBLE = std::numeric_limits<double>::epsilon ();

bool utilities::double_equals (double a, double b)
{
    return std::fabs (a - b) < utilities::_EPSILON_DOUBLE;
}
