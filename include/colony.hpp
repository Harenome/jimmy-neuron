/**
 * \file colony.cpp
 * \brief Colony.
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
#ifndef __COLONY_HPP__
#define __COLONY_HPP__

#include <algorithm>

#include "utilities.hpp"
#include "neuron.hpp"
#include "neuron_network.hpp"
#include "neuron_network_fitness.hpp"
#include "evolution.hpp"
#include "random_factory.hpp"

////////////////////////////////////////////////////////////////////////////////
// Enumérations.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Stratégies de purge de la colonie.
 */
typedef enum colony_purge_strategy
{
    COLONY_PURGE_LOOSERS,       /**<- Éliminer les moins bons réseaux. */
    COLONY_PURGE_RANDOMLY,      /**<- Éliminer au hasard. */
    COLONY_PURGE_DEFAULT        /**<- Stratégie par défaut. */
} colony_purge_strategy;

////////////////////////////////////////////////////////////////////////////////
// Typedefs.
////////////////////////////////////////////////////////////////////////////////

typedef std::vector<neuron_network> colony_networks;

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Colonie de réseaux de neurones.
 */
class colony
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructeurs et destructeurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Constructeur.
     */
    colony (void);

    /**
     * \brief Constructeur par copie.
     * \param c Colonie à copier.
     */
    colony (const colony & c);

    /**
     * \brief Constructeur.
     * \param fitness Fitness.
     * \param population_size Taille de la colonie.
     * \param weight_range Fourchette des poids.
     * \param strategy Stratégie de réduction de la colonie.
     * \param weight_number Nombre de poids des neurones de tête.
     * \param head_neurons_number Nombre de neurones en tête.
     */
    colony (const neuron_network_fitness & fitness,
        unsigned int population_size = colony::DEFAULT_POPULATION_SIZE,
        double weight_range = random_factory::DEFAULT_RANGE,
        colony_purge_strategy strategy = COLONY_PURGE_DEFAULT,
        unsigned int weight_number = random_factory::DEFAULT_WEIGHT_NUMBER,
        unsigned int head_neurons_number = random_factory::DEFAULT_HEAD_NEURONS_NUMBER
    );

    /**
     * \brief Destructeur.
     */
    ~colony (void);

    ////////////////////////////////////////////////////////////////////////////
    // Sélecteurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Déterminer si au moins un réseau est approprié.
     * \retval true si au moins un réseau est approprié.
     * \retval false sinon.
     */
    bool has_fit_network (void) const;

    /**
     * \brief Obtenir le meilleur réseau de la colonie.
     * \return Meilleur réseau.
     */
    neuron_network best_network (void) const;

    /**
     * \brief Obtenir la fitness du meilleur réseau de la colonie.
     * \return Meilleure fitness.
     */
    double best_fitness (void) const;

    /**
     * \brief Obtenir la moyenne des fitness des réseaux de la colonie.
     * \return Moyenne.
     */
    double mean_fitness (void) const;

    /**
     * \brief Obtenir le nombre de générations écoulées de la colonie.
     * \return Nombre de générations.
     */
    unsigned int generations_count (void) const;

    ////////////////////////////////////////////////////////////////////////////
    // Modificateurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Passer un tour.
     */
    void turn (void);

    /**
     * \brief Modifier la méthode d'évaluation de la fitness..
     * \param fitness Nouvelle méthode d'évaluation de la fitness.
     */
    void set_fitness (const neuron_network_fitness & fitness);

    /**
     * \brief Modifier la stratégie de réduction.
     * \param strategy Nouvelle stratégie de réduction de la colonie.
     */
    void set_purge_strategy (colony_purge_strategy strategy);

    static const unsigned int DEFAULT_POPULATION_SIZE = 100;    /**<- Taille par défaut de la colonie. */

private:
    unsigned int _generations_count;        /**<- Compte des générations. */
    unsigned int _population_size;          /**<- Taille de la population. */
    unsigned int _weight_number;            /**<- Nombre de poids des neurones de tête. */
    unsigned int _head_neurons_number;      /**<- Nombre de neurones en tête. */
    double _weight_range;                   /**<- Fourchette des poids. */
    neuron_network_fitness _fitness;        /**<- Méthode d'évaluation de la fitness. */
    colony_networks _networks;              /**<- Réseaux de la colonie. */
    void (* _purge) (colony_networks &, const neuron_network_fitness &, unsigned int);

    /**
     * \brief Trier des réseaux selon une fitness.
     * \param networks Réseaux à trier.
     * \param fitness Fitness.
     */
    static void _sort (colony_networks & networks, const neuron_network_fitness & fitness);

    /**
     * \brief Éliminer les moins bons réseaux selon une fitness et trier les réseaux restants..
     * \param networks Réseaux.
     * \param fitness Fitness.
     * \param population_size Nombre de réseaux à conserver.
     */
    static void _purge_loosers (colony_networks & networks,
        const neuron_network_fitness & fitness,
        unsigned int population_size
    );

    /**
     * \brief Éliminer les réseaux au hasard et trier les résaux restants..
     * \param networks Réseaux.
     * \param fitness Fitness.
     * \param population_size Nombre de réseaux à conserver.
     */
    static void _purge_randomly (colony_networks & networks,
        const neuron_network_fitness & fitness,
        unsigned int population_size
    );

    /**
     * \brief Cloner le réseau à l'index \c i.
     * \param i Index du réseau.
     */
    void _clone (unsigned int i);

    /**
     * \brief Effectuer un cross-over avec le réseau à l'index \c i.
     * \param i Index du réseau.
     */
    void _cross_over (long int i);

    /**
     * \brief Provoquer une mutation du réseau à l'index \c i.
     * \param i Index du réseau.
     */
    void _mutate (unsigned int i);
};

#endif /* __COLONY_HPP__ */
