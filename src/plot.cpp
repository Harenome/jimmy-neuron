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

////////////////////////////////////////////////////////////////////////////////
// Constructeurs et destructeurs.
////////////////////////////////////////////////////////////////////////////////

plot::plot (void)
{
}

plot::plot (const double_vector & best_fitnesses, const double_vector & mean_fitnesses)
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

void plot::display (void)
{
    const char * file_path = "/tmp/jimmy";
    /* std::fstream output (file_path); */
    /* for (int i = 0; i < _best.size (); ++i) */
    /*     output << i << " " << _best[i] << " " << _mean[i] << std::endl; */
    /* output.close (); */
    FILE * const output = fopen(file_path, "w");
    if (output == NULL)
        perror ("fopen");

    for (unsigned int i = 0; i < _best.size (); ++i)
    {
        fprintf (output, "%d %f %f\n", i, _best[i], _mean[i]);
        fflush (output);
    }

    fclose (output);

    FILE * const gnuplot = popen("gnuplot -persistent", "w");

    if (gnuplot == NULL || gnuplot == (FILE *)-1)
    {
        perror("popen");
    }
    else
    {
        fprintf(gnuplot,
                "set style data lines\n"
                "set xlabel \"Générations\"\n"
                "set ylabel \"Fitness\"\n"
                "plot '%s' u 1:3 t 'Best fitness', '%s' u 1:2 t 'Mean fitness'\n",
                file_path, file_path);
        fflush(gnuplot);
        fclose(gnuplot);
    }
}
