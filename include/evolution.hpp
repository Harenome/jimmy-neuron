/**
 * \file evolution.hpp
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
#ifndef __MUTATE_HPP__
#define __MUTATE_HPP__

#include <algorithm>

#include "utilities.hpp"
#include "neuron.hpp"
#include "neuron_network.hpp"
#include "truth_table.hpp"
#include "neuron_network_fitness.hpp"
#include "random_factory.hpp"

////////////////////////////////////////////////////////////////////////////////
// Enumérations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Actions d'évolution.
 */
typedef enum evolution_action
{
    EVOLUTION_CROSS_OVER,   /**<- Cross-over. */
    EVOLUTION_MUTATE,       /**<- Mutation. */
    EVOLUTION_CLONE,        /**<- Clonage. */
    EVOLUTION_UNKNOWN       /**<- ?! */
} evolution_action;

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Évolution.
 */
class evolution
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Probabilités.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Obtenir la probabilité de mutation courante.
     * \retrun Probabilité de mutation courante.
     */
    static unsigned int probability_mutation (void);

    /**
     * \brief Obtenir la probabilité de cross-over courante.
     * \retrun Probabilité de cross-over courante.
     */
    static unsigned int probability_cross_over (void);

    /**
     * \brief Obtenir la probabilité de clonage courante.
     * \retrun Probabilité de clonage courante.
     */
    static unsigned int probability_cloning (void);

    /**
     * \brief Modifier les probabilités.
     * \param cross_over Probabilité de cross-over.
     * \param mutation Probabilité de mutation.
     * \param cloning Porbabilité de clonage.
     * \pre cross_over + mutation + cloning = 100.
     * \note Si la somme des trois paramètres esst différente de \c 100, rien n'est fait.
     */
    static void set_probabilities (unsigned int cross_over, unsigned int mutation, unsigned int cloning);

    ////////////////////////////////////////////////////////////////////////////
    // Évolution des réseaux.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Choisir une action.
     * \retval EVOLUTION_CLONE S'il faut cloner.
     * \retval EVOLUTION_MUTATE S'il faut muter.
     * \retval EVOLUTION_CROSS_OVER S'il faut faire un corss-over.
     * \retval EVOLUTION_UNKNOWN ?!
     */
    static evolution_action choose_action (void);

    /**
     * \brief Provoquer une mutation du réseau.
     * \param n Réseau.
     * \param weight_number Nombre de poids.
     * \param weight_range Fourchette.
     */
    static void randomly_mutate (neuron_network & n, unsigned int weight_number, double weight_range);

    /**
     * \brief Cloner un réseau.
     * \param n Réseau.
     * \return Clone.
     */
    static neuron_network clone (const neuron_network & n);

    /**
     * \brief Provoquer un cross-over.
     * \param a Premier réseau.
     * \param b Second réseau.
     * \return Réseau.
     */
    static neuron_network cross_over (const neuron_network & a, const neuron_network & b);

    ////////////////////////////////////////////////////////////////////////////
    // Comparaison des réseaux.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Modifier la fitness utilisée.
     * \param fitness Nouvelle fitness.
     */
    static void set_fitness (const neuron_network_fitness & fitness);

    /**
     * \brief Obtenir la fitness courante.
     */
    static neuron_network_fitness current_fitness (void);

    /**
     * \brief Comparer les fitness de deux réseaux.
     * \param a Premier réseau.
     * \param b Second réseau.
     * \retval true Si \c a est « inférieur » à \c b.
     * \retval false sinon.
     */
    static bool network_lower_than (const neuron_network & a, const neuron_network & b);

    ////////////////////////////////////////////////////////////////////////////
    // Probabilités (variables).
    ////////////////////////////////////////////////////////////////////////////
    static const unsigned int DEFAULT_PROBABILITY_MUTATION = 10;    /**<- Probabilité de mutation par défaut. */
    static const unsigned int DEFAULT_PROBABILITY_CLONING = 5;      /**<- Probabilité de clonage par défaut. */
    static const unsigned int DEFAULT_PROBABILITY_CROSS_OVER = 85;  /**<- Provavilité de cross-over par défaut. */

private:
    static unsigned int _probability_mutation;          /**<- Probabilité de mutation effective. */
    static unsigned int _probability_cross_over;        /**<- Probabilité de Cross-over. */
    static unsigned int _probability_cloning;           /**<- Probabilité de clonage. */
    static neuron_network_fitness _fitness;             /**<- Fitness à utiliser. */
};

#endif /* __MUTATE_HPP__ */
