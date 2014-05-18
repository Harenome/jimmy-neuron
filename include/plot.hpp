/**
 * \file plot.hpp
 * \brief Plot.
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
#ifndef __PLOT_HPP__
#define __PLOT_HPP__

#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Typedefs.
////////////////////////////////////////////////////////////////////////////////

typedef std::vector<double> double_vector;

////////////////////////////////////////////////////////////////////////////////
// Classe.
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Interaction avec GNUPlot.
 */
class plot
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // Constructeurs et destructeurs.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Constructeur.
     */
    plot (void);

    /**
     * \brief Constructeur.
     * \param best_fitnesses Meilleurs fitnesses.
     * \param mean_fitnesses Moyennes.
     */
    plot (const double_vector & best_fitnesses,
        const double_vector & mean_fitnesses,
        const char * temporary_file_path = plot::DEFAULT_TEMP_FILE_PATH);

    /**
     * \brief Destructeur.
     */
    ~plot (void);

    ////////////////////////////////////////////////////////////////////////////
    // Divers.
    ////////////////////////////////////////////////////////////////////////////
    /**
     * \brief Lancer et afficher GNUPlot.
     */
    void display (void);

    static const char * DEFAULT_TEMP_FILE_PATH;

private:
    double_vector _best;        /**<- Meilleures fitnesses. */
    double_vector _mean;        /**<- Moyennes. */
    const char * _temp_file_path;

    void _write_to_temp_file (void);
    void _run_gnuplot (void);
};

#endif /* __PLOT_HPP__ */
