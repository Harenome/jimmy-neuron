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
#include "parse_cli.hpp"

bool parse_cli::option_is_given (int argc, char ** argv, const char * option, std::string & argument)
{
    std::string o (option);
    return parse_cli::option_is_given (argc, argv, o, argument);
}

bool parse_cli::option_is_given (int argc, char ** argv, const std::string & option, std::string & argument)
{
    bool found = false;
    std::string dashes ("--");
    size_t dashes_size = dashes.size ();
    size_t option_size = option.size ();
    for (int i = 0; ! false && i < argc; ++i)
    {
        std::string current_arg (argv[i]);
        if (strlen (argv[i]) > dashes_size && current_arg.compare (0, dashes_size, dashes) == 0)
        {
            int comparison = current_arg.compare (dashes_size, option_size, option);
            if (comparison == 0)
            {
                if (current_arg[dashes_size + option_size] == '=')
                    argument = current_arg.substr (dashes_size + option_size + 1, std::string::npos);
                found = true;
            }
        }
    }

    return found;
}

void parse_cli::set_unsigned_int (int argc, char ** argv, const char * option, unsigned int & value)
{
    std::string o (option);
    parse_cli::set_unsigned_int (argc, argv, o, value);
}

void parse_cli::set_unsigned_int (int argc, char ** argv, const std::string & option, unsigned int & value)
{
    std::string argument;
    if (parse_cli::option_is_given (argc, argv, option, argument))
    {
        int chosen_value = atoi (argument.c_str ());
        if (chosen_value > 0)
            value = chosen_value;
    }
}

void parse_cli::set_double (int argc, char ** argv, const char * option, double & value)
{
    std::string o (option);
    parse_cli::set_double (argc, argv, o, value);
}

void parse_cli::set_double (int argc, char ** argv, const std::string & option, double & value)
{
    std::string argument;
    if (parse_cli::option_is_given (argc, argv, option, argument))
    {
        double chosen_value = atof (argument.c_str ());
        if (chosen_value > 0)
            value = chosen_value;
    }
}

void parse_cli::set_probabilities (int argc, char ** argv, unsigned int & cross_over, unsigned int & mutation, unsigned int & cloning)
{
    std::string argument;
    std::string option ("probabilities");
    if (parse_cli::option_is_given (argc, argv, option, argument))
    {
        size_t first_comma = argument.find_first_of (',');
        size_t last_comma = argument.find_last_of (',');

        /* Vérifier que l'argument contient 2 virgules. */
        if (first_comma != std::string::npos
            && last_comma != std::string::npos
            && argument.find_first_of (',', first_comma + 1) == last_comma)
        {
            std::string chosen_strings[3];
            chosen_strings[0] = argument.substr (0, first_comma);
            chosen_strings[1] = argument.substr (first_comma + 1, last_comma);
            chosen_strings[2] = argument.substr (last_comma + 1, std::string::npos);

            int chosen_values[3];
            for (int i = 0; i < 3; ++i)
            {
                int value = atoi (chosen_strings[i].c_str ());
                chosen_values[i] = value > 0 ? value : 0;
            }

            cross_over = chosen_values[0];
            mutation = chosen_values[1];
            cloning = chosen_values[2];

        }
    }
}
