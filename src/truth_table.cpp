/**
 * \file truth_table.cpp
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
#include "truth_table.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constructeurs.
////////////////////////////////////////////////////////////////////////////////

truth_table::truth_table (void)
{
    for (unsigned int i = 0; i < 2; ++i)
        for (unsigned int j = 0; j < 2; ++j)
            _table[i][j] = true;
}

truth_table::truth_table (bool false_false, bool false_true, bool true_false, bool true_true)
{
    _table[0][0] = false_false;
    _table[0][1] = false_true;
    _table[1][0] = true_false;
    _table[1][1] = true_true;
}

truth_table::truth_table (const truth_table & t)
{
    for (unsigned int i = 0; i < 2; ++i)
        for (unsigned int j = 0; j < 2; ++j)
            _table[i][j] = t._table[i][j];
}

truth_table::~truth_table (void)
{
}

////////////////////////////////////////////////////////////////////////////////
// Sélecteurs.
////////////////////////////////////////////////////////////////////////////////

bool truth_table::result (bool a, bool b) const
{
    unsigned int i = _bool_to_unsigned_int (a);
    unsigned int j = _bool_to_unsigned_int (b);
    return _table[i][j];
}

bool truth_table::equals (const truth_table & t) const
{
    bool success = true;
    for (unsigned int i = 0; success && i < 2; ++i)
        for (unsigned int j = 0; success && j < 2; ++j)
            success = _table[i][j] == t._table[i][j];

    return success;
}

////////////////////////////////////////////////////////////////////////////////
// Modificateurs.
////////////////////////////////////////////////////////////////////////////////

void truth_table::set_result (bool a, bool b, bool result)
{
    unsigned int i = _bool_to_unsigned_int (a);
    unsigned int j = _bool_to_unsigned_int (b);
    _table[i][j] = result;
}

////////////////////////////////////////////////////////////////////////////////
// Divers.
////////////////////////////////////////////////////////////////////////////////

void truth_table::swap (truth_table & t)
{
    for (unsigned int i = 0; i < 2; ++i)
        for (unsigned int j = 0; j < 2; ++j)
            std::swap (_table[i][j], t._table[i][j]);
}

truth_table & truth_table::operator= (truth_table t)
{
    this->swap (t);
    return * this;
}

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

void swap (truth_table & a, truth_table & b)
{
    a.swap (b);
}
