/**
 * \file neuron_network.hpp
 * \brief Réseau de neurones.
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
#ifndef __NEURON_NETWORK_HPP__
#define __NEURON_NETWORK_HPP__

#include <list>
#include <vector>
#include <cmath>
#include <ostream>
#include <istream>
#include <limits>

#include "neuron.hpp"

////////////////////////////////////////////////////////////////////////////////
// Typedefs.
////////////////////////////////////////////////////////////////////////////////

typedef std::vector<neuron>::iterator neuron_network_iterator;
typedef std::vector<neuron>::const_iterator neuron_network_const_iterator;
typedef std::vector<neuron>::size_type neuron_network_size_type;

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Réseau de neurones.
 * \sa neuron
 */
class neuron_network
{
public:
    /**
     * \brief Constructeur.
     */
    neuron_network (void);

    /**
     * \brief Constructeur par copie.
     * \param n Réseau à copier.
     */
    neuron_network (const neuron_network & n);

    /**
     * \brief Constructeur.
     * \param head Neurones en tête.
     * \param out Neurone en sortie.
     */
    neuron_network (const std::vector<neuron> head, const neuron & out);

    /**
     * \brief Destructeur.
     */
    ~neuron_network (void);

    /**
     * \brief Obtenir les neurones en tête.
     * \return Neurones en tête.
     */
    std::vector<neuron> head_neurons (void) const;

    /**
     * \brief Obtenir le neuron en sortie.
     * \return Neurone en sortie.
     */
    neuron out_neuron (void) const;

    /**
     * \brief Tenter d'activer le réseau de neurones.
     * \param inputs Entrées.
     * \retval true Si les entrées fournies activent le réseau.
     * \retval false Sinon.
     * \note - Les entrées superflues (c'est-à-dire s'il y a plus d'entrées que de poids) seront ignorées.
     * \note - S'il n'y pas assez d'entrées, le résulat sera nécessairement \c false.
     */
    bool attempt (const std::list<bool> & inputs) const;

    /**
     * \brief Obtenir la somme des produits des entrées et des poids.
     * \param input Entrées.
     * \return Somme des produits des entrées et des poids.
     */
    long double accumulate (const std::list<bool> & inputs) const;

    /**
     * \brief Obtenir le nombre de neurones en tête.
     * \return Nombre de neurones en tête.
     */
    neuron_network_size_type head_neurons_number (void) const;

    /**
     * \brief Modifier le neurone en sortie.
     * \param out Nouveau neurone de sortie.
     */
    void set_out_neuron (const neuron & out);

    /**
     * \brief Modifier les neurones en tête.
     * \param head Nouveaux neurones de tête.
     */
    void set_head_neurons (const std::vector<neuron> & head);

    /**
     * \brief Échanger deux réseaux.
     * \param n Réseau.
     */
    void swap (neuron_network & n);

    /**
     * \brief Opérateur \c =.
     * \param n Réseau.
     */
    neuron_network & operator= (neuron_network n);

    /**
     * \brief Écrire le réseau dans un flux de sortie.
     * \param os Flux de sortie.
     * \return \c os.
     */
    std::ostream & write_to (std::ostream & os) const;

    /**
     * \brief Écrire le réseau dans un flux d'entrée.
     * \param os Flux d'entrée.
     * \return \c is.
     */
    std::istream & read_from (std::istream & is);

    /**
     * \brief Initialiser les listes à 2 entrées.
     */
    static void init_lists (void);

    static std::list<bool> FALSE_FALSE;     /**<- Faux, faux. */
    static std::list<bool> FALSE_TRUE;      /**<- Faux, vrai. */
    static std::list<bool> TRUE_FALSE;      /**<- Vrai, faux. */
    static std::list<bool> TRUE_TRUE;       /**<- Vrai, vrai. */

private:
    neuron _out;                    /**<- Neurone de sortie. */
    std::vector<neuron> _head;      /**<- Neurones de tête. */

    /**
     * \brief Calculer les entrées intermédiaires.
     * \param inputs Véritables entrées.
     * \return Entrées intermédiaires.
     * Il s'agit des sorties des neurones de têtes, ces sorties seront passées
     * en entrée du neurone de sortie.
     */
    std::list<bool> _inner_inputs (const std::list<bool> & inputs) const;
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Échanger deux réseaux.
 * \param a Réseau 1.
 * \param b Réseau 2.
 */
void swap (neuron_network & a, neuron_network & b);

/**
 * \brief Écrire le réseau dans un flux de sortie.
 * \param os Flux de sortie.
 * \param n Réseau.
 * \return \c is.
 */
std::istream & operator>> (std::istream & is, neuron_network & n);

/**
 * \brief Écrire le réseau dans un flux d'entrée.
 * \param os Flux d'entrée.
 * \param n Réseau.
 * \return \c os.
 */
std::ostream & operator<< (std::ostream & os, const neuron_network & n);

#endif /* __NEURON_NETWORK_HPP__ */
