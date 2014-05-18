/**
 * \file truth_table.hpp
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
#ifndef __TRUTH_TABLE_HPP__
#define __TRUTH_TABLE_HPP__

#include <list>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Table de vérité 2x2
 * \note Il est ici possible d'avoir des tables asymétriques.
 */
class truth_table
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructeurs et destructeurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Constructeur.
     */
    truth_table (void);

    /**
     * \brief Constructeur.
     * \param false_false Résultat pour \c true et \c false.
     * \param false_true Résultat pour \c false et \c true.
     * \param true_false Résultat pour \c true et \c false.
     * \param true_true Résultat pour \c true et \c true.
     */
    truth_table (bool false_false, bool false_true, bool true_false, bool true_true);

    /**
     * \brief Constructeur par copie.
     * \param t Table de vérité.
     */
    truth_table (const truth_table & t);

    /**
     * \brief Destructeur.
     */
    ~truth_table (void);

    ////////////////////////////////////////////////////////////////////////////
    // Sélecteurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Résultat pour \c a et \c b.
     * \param a Première entrée.
     * \param b Deuxième entrée.
     * \retval true Si le résultat de la table de vérité pour \c a et \c b est \true.
     * \retval false Sinon.
     */
    bool result (bool a, bool b) const;

    /**
     * \brief Tester l'égalité de deux tables de vérité.
     * \param t Table de vérité.
     * Deux tables de vérité sont égales si tous leurs résultats
     * sont identiques.
     */
    bool equals (const truth_table & t) const;

    ////////////////////////////////////////////////////////////////////////////
    // Modificateurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Modifier le résultat pour \c a et \c b.
     * \param a Première entrée.
     * \param b Deuxième entrée.
     * \param result Nouveau résultat.
     */
    void set_result (bool a, bool b, bool result);

    ////////////////////////////////////////////////////////////////////////////
    // Divers.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Échanger deux tables de vérité.
     * \param t Table de vérité.
     */
    void swap (truth_table & t);

    /**
     * \brief Opérateur \c =.
     * \param t Table de vérité.
     */
    truth_table & operator= (truth_table t);

private:
    bool _table[2][2];      /**<- Table de vérité. */
    static inline unsigned _bool_to_unsigned_int (bool b)
    {
        return b ? 1 : 0;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Fonctions amies.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Échanger deux tables de vérité.
 * \param a Table de vérité.
 * \param b Table de vérité.
 */
void swap (truth_table & a, truth_table & b);

/**
 * \brief Tester l'égalité de deux tables de vérité.
 * \param a Table de vérité.
 * \param b Table de vérité.
 * \retval true Si les deux tables sont égales.
 * \retval false Sinon.
 * \sa truth_table::equals
 */
inline bool operator== (const truth_table & a, const truth_table & b)
{
    return a.equals (b);
}

/**
 * \brief Tester l'inégalité de deux tables de vérité.
 * \param a Table de vérité.
 * \param b Table de vérité.
 * \retval false Si les deux tables sont égales.
 * \retval true Sinon.
 * \sa truth_table::equals, operator==(const truth_table &, const truth_table &)
 */
inline bool operator!= (const truth_table & a, const truth_table & b)
{
    return ! operator== (a, b);
}

#endif /* __TRUTH_TABLE_HPP__ */
