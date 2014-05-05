/**
 * \file utilities.hpp
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
#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#include <limits>
#include <cmath>

class utilities
{
public:
    static bool double_equals (double a, double b);
private:
    static const double _EPSILON_DOUBLE;
};

#endif /* __UTILITIES_HPP__ */
