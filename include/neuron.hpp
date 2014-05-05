/**
 * \file neuron.hpp
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
#ifndef __NEURON_HPP__
#define __NEURON_HPP__

#include <list>
#include <vector>
#include <limits>
#include <ostream>
#include <istream>

#include "utilities.hpp"

////////////////////////////////////////////////////////////////////////////////
// Typedefs.
////////////////////////////////////////////////////////////////////////////////

typedef std::vector<double> neuron_weights;
typedef neuron_weights::iterator neuron_iterator;
typedef neuron_weights::const_iterator neuron_const_iterator;
typedef neuron_weights::size_type neuron_size_type;

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Neurone.
 */
class neuron
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructeurs et destructeurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Constructeur.
     */
    neuron (void);

    /**
     * \brief Constructeur par copie.
     */
    neuron (const neuron & n);

    /**
     * \brief Constructeur.
     * \param weights Liste de poids.
     */
    neuron (const std::vector<double> & weights);

    /**
     * \brief Destructeur.
     */
    ~neuron (void);

    ////////////////////////////////////////////////////////////////////////////
    // Sélecteurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Obtenir la liste des poids du neurone.
     * \return Liste des poids.
     * \note La liste peut être vide.
     */
    neuron_weights weights (void) const;

    /**
     * \brief Obtenir le nombre de poids du neurone.
     * \return Nombre de poids du neurone.
     */
    neuron_size_type weight_number (void) const;

    /**
     * \brief Obtenir la somme des produits des entrées et des poids.
     * \param input Entrées.
     * \return Somme des produits des entrées et des poids.
     */
    long double accumulate (const std::list<bool> & input) const;

    /**
     * \brief Tenter d'activer le neurone.
     * \param input Entrées.
     * \retval true si les entrées fournies activent le neurone.
     * \retval false sinon.
     * \note - Les entrées superflues (c'est-à-dire s'il y a plus d'entrées que de poids) seront ignorées.
     * \note - S'il n'y pas assez d'entrées, le résulat sera nécessairement \c false.
     */
    bool attempt (const std::list<bool> & input) const;

    /**
     * \brief Accéder à l'un des poids du neurone.
     * \param index Index du poids.
     * \return Poids recherché.
     * \pre \c index <= neuron::weight_number
     */
    double & operator[] (unsigned int index);

    /**
     * \brief Accéder à l'un des poids du neurone.
     * \param index Index du poids.
     * \return Poids recherché.
     * \pre \c index < neuron::weight_number
     */
    const double & operator[] (unsigned int index) const;

    /**
     * \brief Obtenir un itérateur sur le début du neurone.
     * \return Itérateur.
     */
    neuron_iterator begin (void);

    /**
     * \brief Obtenir un itérateur sur le début du neurone.
     * \return Itérateur.
     */
    neuron_const_iterator begin (void) const;

    /**
     * \brief Obtenir un itérateur sur la fin du neurone.
     * \return Itérateur.
     */
    neuron_iterator end (void);

    /**
     * \brief Obtenir un itérateur sur la fin du neurone.
     * \return Itérateur.
     */
    neuron_const_iterator end (void) const;

    /**
     * \brief Déterminer si un neurone est égal à un autre neurone.
     * \param n Neurone à comparer.
     * \retval true Si les neurones sont égaux.
     * \retval false Sinon.
     * Deux neurones sont considérés égaux si leurs nombre de poids sont égaux,
     * et si leurs poids de même indices sont égaux.
     */
    bool equals (const neuron & n) const;

    ////////////////////////////////////////////////////////////////////////////
    // Modificateurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Ajouter un poids au neurone.
     * \param weight Poids à ajouter.
     * \note Le poids sera ajouté à la « fin » du neurone.
     */
    void add_weight (double weight);

    /**
     * \brief Modifier un poids du neurone.
     * \param index Index du poids à modifier.
     * \param weight Nouveau poids.
     * \warning On ne peut modifier qu'un poids existant : si \c index >= neuron::weight_number, le neurone ignorera la demande d'ajout de poids.
     */
    void set_weight (unsigned int index, double weight);

    ////////////////////////////////////////////////////////////////////////////
    // Divers.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Échanger deux neurones.
     * \param n Neurone.
     */
    void swap (neuron & n);

    /**
     * \brief Opérateur \c =.
     * \param n Neurone.
     */
    neuron & operator= (neuron n);

    /**
     * \brief Écrire le neurone dans un flux.
     * \param os Flux de sortie.
     * \return \c os.
     */
    std::ostream & write_to (std::ostream & os) const;

    /**
     * \brief Lire le neurone depuis un flux.
     * \param is Flux d'entrée.
     * \return \c is.
     */
    std::istream & read_from (std::istream & is);

private:
    neuron_weights _weights;                /**<- Poids du neurone. */
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Opérateur \c ==.
 * \param a Neurone 1.
 * \param b Neurone 2.
 * \retval true Si les neurones sont égaux.
 * \retval false Sinon.
 * \relates neuron
 * \sa neuron::equals
 */
inline bool operator== (const neuron & a, const neuron & b)
{
    return a.equals (b);
}

/**
 * \brief Opérateur \c !=.
 * \param a Neurone 1.
 * \param b Neurone 2.
 * \retval true Si les neurones sont différents.
 * \retval false Sinon.
 * \relates neuron
 * \sa neuron::equals
 */
inline bool operator!= (const neuron & a, const neuron & b)
{
    return ! operator== (a, b);
}

/**
 * \brief Échanger deux neurones.
 * \param a Neurone 1.
 * \param b Neurone 2.
 * \relates neuron
 */
void swap (neuron & a, neuron & b);

/**
 * \brief Opérateur \c >>.
 * \param is Flux d'entrée.
 * \param n Neurone.
 * \return \c is.
 * \relates neuron
 * \sa neuron::read_from
 */
std::istream & operator>> (std::istream & is, neuron & n);

/**
 * \brief Opérateur \c <<.
 * \param os Flux de sortie
 * \param n Neurone.
 * \return \c os.
 * \relates neuron
 * \sa neuron::write_to
 */
std::ostream & operator<< (std::ostream & os, const neuron & n);

#endif /* __NEURON_HPP__ */
