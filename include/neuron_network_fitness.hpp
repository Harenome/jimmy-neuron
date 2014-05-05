/**
 * \file neuron_network_fitness.hpp
 * \brief Fitness.
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
#ifndef __NEURON_NETWORK_FITNESS_HPP__
#define __NEURON_NETWORK_FITNESS_HPP__

#include <cmath>

#include "utilities.hpp"
#include "neuron.hpp"
#include "neuron_network.hpp"
#include "truth_table.hpp"

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief « Fitness » d'un réseau de neurones par rapport à une table de vérité.
 * \sa neuron, neuron_network, truth_table
 */
class neuron_network_fitness
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructeurs et destructeurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Constructeur.
     */
    neuron_network_fitness (void);

    /**
     * \brief Constructeur.
     * \param t Table de vérité.
     */
    neuron_network_fitness (const truth_table & t);

    /**
     * \brief Constructeur par copie.
     * \param nf Fitness.
     */
    neuron_network_fitness (const neuron_network_fitness & nf);

    /**
     * \brief Destructeur.
     */
    ~neuron_network_fitness (void);

    ////////////////////////////////////////////////////////////////////////////
    // Sélecteurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Obtenir la table de vérité.
     * \return Table de vérité.
     */
    truth_table table (void) const;

    /**
     * \brief Calculer la fitness d'un réseau.
     * \param n Réseau.
     * \todo neuron_network_fitness::fitness_of
     */
    double fitness_of (const neuron_network & n) const;

    /**
     * \brief Comparer deux réseaux de neurones par leur fitness.
     * \param a Réseau.
     * \param b Réseau.
     * \retval 1 Si \c a est supérieur à \c b.
     * \retval 0 Si \c a et \c b sont égaux.
     * \retval -1 Si \c a est inférieur à \c b.
     */
    int compare_networks (const neuron_network & a, const neuron_network & b) const;

    ////////////////////////////////////////////////////////////////////////////
    // Modificateurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Modifier la table de vérité.
     * \param t Table de vérité.
     */
    void set_table (const truth_table & t);

    ////////////////////////////////////////////////////////////////////////////
    // Divers.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Échanger deux fitness.
     * \param nf Fitness.
     */
    void swap (neuron_network_fitness & nf);

    /**
     * \brief Opérateur \c ==.
     * \param nf Fitness.
     */
    neuron_network_fitness & operator= (neuron_network_fitness nf);
private:
    truth_table _table;     /**<- Table de vérité. */
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Échanger deux fitness
 * \param a Fitness.
 * \param b Fitness.
 * \relates neuron_network_fitness
 */
void swap (neuron_network_fitness & a, neuron_network_fitness & b);

#endif /* __NEURON_NETWORK_FITNESS_HPP__ */
