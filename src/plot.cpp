/**
 * \file plot.cpp
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
#include "plot.hpp"

const char * plot::DEFAULT_TEMP_FILE_PATH = "/tmp/jimmy_neuron.dat";

////////////////////////////////////////////////////////////////////////////////
// Constructeurs et destructeurs.
////////////////////////////////////////////////////////////////////////////////

plot::plot (void)
: _temp_file_path (plot::DEFAULT_TEMP_FILE_PATH)
{
}

plot::plot (const double_vector & best_fitnesses, const double_vector & mean_fitnesses, const char * temporary_file_path)
: _temp_file_path (temporary_file_path)
{
    _best = best_fitnesses;
    _mean = mean_fitnesses;
}

plot::~plot (void)
{
}

////////////////////////////////////////////////////////////////////////////////
// Divers.
////////////////////////////////////////////////////////////////////////////////

void plot::_write_to_temp_file (void)
{
    std::ofstream output (_temp_file_path);
    for (size_t i = 0; i < _best.size (); ++i)
        output << i << " " << _best[i] << " " << _mean[i] << std::endl;
    output.close ();
}

static const char * _gnuplot_options =
    "set style data lines\n"
    "set key outside\n"
    "set grid\n"
    "set xlabel \"Générations\"\n"
    "set ylabel \"Fitness\"\n"
    "plot '%s' u 1:3 t 'Best fitness', '%s' u 1:2 t 'Mean fitness'\n"
;

void plot::_run_gnuplot (void)
{
    FILE * const gnuplot = popen("gnuplot -persist", "w");

    if (gnuplot == NULL || gnuplot == (FILE *)-1)
        perror("popen");
    else
    {
        fprintf(gnuplot, _gnuplot_options, _temp_file_path, _temp_file_path);
        fflush(gnuplot);
        fclose(gnuplot);
    }
}

void plot::display (void)
{
    _write_to_temp_file ();
    _run_gnuplot ();
}
