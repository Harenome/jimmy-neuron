/**
 * \file random_factory.hpp
 * \brief Random factory.
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
#ifndef __RANDOM_FACTORY_HPP__
#define __RANDOM_FACTORY_HPP__

#include "utilities.hpp"
#include "neuron.hpp"
#include "neuron_network.hpp"

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Usine pseudo-aléatoire.
 */
class random_factory
{
public:
    /**
     * \brief Créer un neurone pseudo-aléatoire.
     * \param weight_number Nombre de poids du neurone.
     * \param weight_range Fourchette pour le poids du neurone.
     * \return Neurone pseudo-aléatoire.
     */
    static neuron random_neuron (unsigned int weight_number = random_factory::DEFAULT_WEIGHT_NUMBER, double weight_range = random_factory::DEFAULT_RANGE);

    /**
     * \brief Créer un réseau de neurones pseudo-aléatoire.
     * \param weight_number Nombre de poids des neurones.
     * \param head_neurons_number Nombre de neurones en tête du réseau.
     * \param weight_range Fourchette pour les poids des neurones.
     * \return Réseau de neurones pseudo-aléatoire.
     */
    static neuron_network random_neuron_network
        (unsigned int weight_number = random_factory::DEFAULT_WEIGHT_NUMBER,
        unsigned int head_neurons_number = random_factory::DEFAULT_HEAD_NEURONS_NUMBER,
        double weight_range = random_factory::DEFAULT_RANGE);

    static const double DEFAULT_RANGE;                              /**<- Fourchette par défaut. */
    static const unsigned int DEFAULT_WEIGHT_NUMBER = 2;            /**<- Nombre de poids par défaut. */
    static const unsigned int DEFAULT_HEAD_NEURONS_NUMBER = 3;      /**<- Nombre de neurones de tête par défaut. */
};

const double random_factory::DEFAULT_RANGE = 2.0;

#endif /* __RANDOM_FACTORY_HPP__ */
