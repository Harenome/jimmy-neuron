/**
 * \file parse_cli.cpp
 * \brief Parse CLI.
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
#ifndef __PARSE_CLI_HPP__
#define __PARSE_CLI_HPP__

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * \brief Parser les arguments de la ligne de commande.
 */
class parse_cli
{
public:
    /**
     * \brief Déterminer si une option a été donnée et, le cas échéant, stocker son argument.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param argument Argument de l'option.
     */
    static bool option_is_given (int argc, char ** argv, const std::string & option, std::string & argument);

    /**
     * \brief Déterminer si une option a été donnée et, le cas échéant, stocker son argument.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param argument Argument de l'option.
     */
    static bool option_is_given (int argc, char ** argv, const char * option, std::string & argument);

    /**
     * \brief Modifier la valeur d'un entier selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param value Valeur.
     */
    static void set_unsigned_int (int argc, char ** argv, const char * option, unsigned int & value);

    /**
     * \brief Modifier la valeur d'un entier selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param value Valeur.
     */
    static void set_unsigned_int (int argc, char ** argv, const std::string & option, unsigned int & value);

    /**
     * \brief Modifier la valeur d'un double selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param value Valeur.
     */
    static void set_double (int argc, char ** argv, const char * option, double & value);

    /**
     * \brief Modifier la valeur d'un double selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param value Valeur.
     */
    static void set_double (int argc, char ** argv, const std::string & option, double & value);

    /**
     * \brief Modifier des probabilités selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param cross_over Probabilité de cross-over.
     * \param mutation Probabilité de mutation.
     * \param cloning Probabilité de clonage.
     */
    static void set_probabilities (int argc, char ** argv, unsigned int & cross_over, unsigned int & mutation, unsigned int & cloning);

    /**
     * \brief Modifier le chemin vers un fichier selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param file_path Chemin.
     */
    static void set_file_path (int argc, char ** argv, const char * option, std::string & file_path);

    /**
     * \brief Modifier le chemin vers un fichier selon les arguments de la ligne de commande.
     * \param argc Nombre d'arguments de la ligne de commande.
     * \param argv Arguments de la ligne de commande.
     * \param option Option recherchée.
     * \param file_path Chemin.
     */
    static void set_file_path (int argc, char ** argv, const std::string & option, std::string & file_path);
};

#endif
