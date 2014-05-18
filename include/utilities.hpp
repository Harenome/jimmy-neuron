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

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <limits>

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Utilitaires.
 */
class utilities
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Fonctions pour les doubles.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Test d'égalité sur les double.
     * \param a Double.
     * \param b Double.
     * \retval true Si \c a == \c b.
     * \retval false Sinon.
     */
    static bool double_equals (double a, double b);

    /**
     * \brief Obtenir l'epsilon utilisé pour comparer les doubles.
     * \return epsilon.
     */
    static double double_epsilon (void);

    /**
     * \brief Modifier l'epsilon.
     * \param epsilon Epsilon
     */
    static void set_double_epsilon (double epsilon);

    ////////////////////////////////////////////////////////////////////////////
    // Fonctions pour le pseudo-aléaoire.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Obtenir un bool pseudo-aléatoire.
     * \return bool pseudo-aléatoire.
     */
    static bool random_bool (void);

    /**
     * \brief Obtenir un int pseudo-aléatoire.
     * \return int pseudo-aléatoire.
     */
    static int random_int (int minimum, int maximum);

    /**
     * \brief Obtenir un double pseudo-aléatoire.
     * \return double pseudo-aléatoire.
     */
    static double random_double (double minimum, double maximum);

    /**
     * \brief Changer de graine pour les tirages pseudo-aléatoires.
     */
    static void new_seed (void);

    /**
     * \brief Modifier la graine pour le pseudo-aléatoire.
     * \param seed Nouvelle graine.
     */
    static void set_seed (unsigned int seed);

    /**
     * \brief Obtenir la graine utilisée.
     * \return Graine utilisée.
     */
    static unsigned int current_seed (void);

private:
    static unsigned int _SEED;                      /**<- Graine pour le pseudo-aléatoire. */
    static double _EPSILON_DOUBLE;                  /**<- Epsilon pour les doubles. */
    static const double _EPSILON_DOUBLE_DEFAULT;    /**<- Epsilon par défaut pour les doubles. */
};

#endif /* __UTILITIES_HPP__ */
