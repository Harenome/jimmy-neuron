/**
 * \file test_neuron_network.hpp
 * \brief Test neuron network.
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
#ifndef __TEST_NEURON_NETWORK_HPP__
#define __TEST_NEURON_NETWORK_HPP__

#include <list>
#include <vector>
#include <limits>
#include <cmath>
#include <cxxtest/TestSuite.h>

#include "neuron.hpp"
#include "neuron_network.hpp"

class test_suite_neuron_network: public CxxTest::TestSuite
{
private:
    static const unsigned int _INPUTS_LENGTH = 4;
    static const unsigned int _WEIGHTS_LENGTH = 9;
    static const unsigned int _POSSIBLE_INPUTS_NUMBER = 2;
    static const unsigned int _POSSIBLE_WEIGHTS_NUMBER = 3;

    static bool _POSSIBLE_INPUTS[_POSSIBLE_INPUTS_NUMBER];
    static double _POSSIBLE_WEIGHTS[_POSSIBLE_WEIGHTS_NUMBER];
    std::list<bool> _inputs[_INPUTS_LENGTH];
    std::vector<double> _weights[_WEIGHTS_LENGTH];
    std::vector<neuron> _neurons;
    std::vector<neuron_network> _networks;

    static inline bool _double_compare (long double a, long double b)
    {
        return std::fabs (a - b) < std::numeric_limits<double>::epsilon ();
    }

    static inline long double _accumulate (const std::vector<double> & weights, const std::list<bool> & inputs)
    {
        long double accumulator = 0.0;

        std::list<bool>::const_iterator it = inputs.begin ();
        std::vector<double>::const_iterator jt = weights.begin ();
        for ( ; jt != weights.end (); ++it, ++jt)
            if (* it)
                accumulator += * jt;

        return accumulator;
    }

    #define _DOUBLE_ASSERT_EQUALS(a, b) TS_ASSERT_EQUALS (true, test_suite_neuron_network::_double_compare (a, b))

public:
    /**
     * \brief Initialisation avant chaque test.
     */
    void setUp (void)
    {
        _POSSIBLE_INPUTS[0] = true;
        _POSSIBLE_INPUTS[1] = false;

        for (unsigned int i = 0; i < _POSSIBLE_INPUTS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_INPUTS_NUMBER; ++j)
            {
                _inputs[i + _POSSIBLE_INPUTS_NUMBER * j].push_back (_POSSIBLE_INPUTS[i]);
                _inputs[i + _POSSIBLE_INPUTS_NUMBER * j].push_back (_POSSIBLE_INPUTS[j]);
            }

        _POSSIBLE_WEIGHTS[0] = 0.0;
        _POSSIBLE_WEIGHTS[1] = 1.0;
        _POSSIBLE_WEIGHTS[2] = -1.0;

        for (unsigned int i = 0; i < _POSSIBLE_WEIGHTS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_WEIGHTS_NUMBER; ++j)
            {
                _weights[i + _POSSIBLE_WEIGHTS_NUMBER * j].push_back (_POSSIBLE_WEIGHTS[i]);
                _weights[i + _POSSIBLE_WEIGHTS_NUMBER * j].push_back (_POSSIBLE_WEIGHTS[j]);
            }

        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            _neurons.push_back (n);
        }

    }

    /**
     * \brief Nettoyage après chaque test.
     */
    void tearDown (void)
    {
        for (unsigned int i = 0; i < _INPUTS_LENGTH; ++i)
        {
            _inputs[i].clear ();
            _weights[i].clear ();
        }

        for (unsigned int i = _INPUTS_LENGTH; i < _WEIGHTS_LENGTH; ++i)
            _weights[i].clear ();

        _neurons.clear ();
        _networks.clear ();
    }

    /**
     * \brief Test du constructeur neuron_network::neuron_network(void).
     * \test neuron_network::neuron_network(void)
     */
    void test_constructor_void (void)
    {
        neuron_network * n;
        TS_ASSERT_THROWS_NOTHING (n = new neuron_network ())
        delete n;
    }

    /**
     * \brief Test du constructeur neuron_network::neuron_network(const std::vector<neuron> &, const neuron &).
     * \test neuron_network::neuron_network(const std::vector<neuron> &, const neuron &)
     */
    void test_constructor_head_out (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);

                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        neuron_network * n;
                        TS_ASSERT_THROWS_NOTHING (n = new neuron_network (head, _neurons[l]))
                        delete n;
                    }
                }
    }

    /**
     * \brief Test du constructeur neuron_network::neuron_network(const neuron_network &)
     * \test neuron_network::neuron_network(const neuron_network &)
     */
    void test_constructor_copy (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);

                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        neuron_network * copy;
                        neuron_network n (head, _neurons[l]);
                        TS_ASSERT_THROWS_NOTHING (copy = new neuron_network (n))
                        delete copy;
                    }
                }
    }

    /**
     * \brief Test de neuron_network::head_neurons
     * \test neuron_network::head_neurons
     */
    void test_head_neurons (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);

                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        neuron_network n (head, _neurons[l]);

                        std::vector<neuron> n_head = n.head_neurons ();
                        TS_ASSERT_EQUALS (n_head.size (), 3)
                        TS_ASSERT_EQUALS (n_head[0], _neurons[i])
                        TS_ASSERT_EQUALS (n_head[1], _neurons[j])
                        TS_ASSERT_EQUALS (n_head[2], _neurons[k])
                    }
                }
    }

    /**
     * \brief Test de neuron_network::out_neuron
     * \test neuron_network::out_neuron
     */
    void test_out_neuron (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);

                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        neuron_network n (head, _neurons[l]);
                        TS_ASSERT_EQUALS (n.out_neuron (), _neurons[l])
                    }
                }
    }

    /**
     * \brief Test de neuron_network::accumulate.
     * \test neuron_network::accumulate
     */
    void test_accumulate (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);

                    for (unsigned int m = 0; m < _INPUTS_LENGTH; ++m)
                    {
                        std::list<bool> inner;
                        inner.push_back (_neurons[i].attempt (_inputs[m]));
                        inner.push_back (_neurons[j].attempt (_inputs[m]));
                        inner.push_back (_neurons[k].attempt (_inputs[m]));

                        for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                        {
                            neuron_network n (head, _neurons[l]);
                            long double expected = _neurons[l].accumulate (inner);
                            _DOUBLE_ASSERT_EQUALS (n.accumulate (_inputs[m]), expected)
                        }
                    }
                }
    }

    /**
     * \brief Test de neuron_network::attempt.
     * \test neuron_network::attempt
     */
    void test_attempt (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);

                    for (unsigned int m = 0; m < _INPUTS_LENGTH; ++m)
                    {
                        std::list<bool> inner;
                        inner.push_back (_neurons[i].attempt (_inputs[m]));
                        inner.push_back (_neurons[j].attempt (_inputs[m]));
                        inner.push_back (_neurons[k].attempt (_inputs[m]));

                        for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                        {
                            neuron_network n (head, _neurons[l]);
                            bool expected = _neurons[l].accumulate (inner) >= 0.5;
                            TS_ASSERT_EQUALS (n.attempt (_inputs[m]), expected)
                        }
                    }
                }
    }
    /**
     * \brief Test de neuron_network::head_neurons_number
     * \test neuron_network::head_neurons_number
     */
    void test_head_neurons_number (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);
                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        neuron_network n (head, _neurons[l]);
                        TS_ASSERT_EQUALS (n.head_neurons_number (), 3)
                    }
                }
    }

    /**
     * \brief Test de neuron_network::set_out_neuron.
     * \test neuron_network::set_out_neuron
     */
    void test_set_out_neuron (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                {
                    std::vector<neuron> head;
                    head.push_back (_neurons[i]);
                    head.push_back (_neurons[j]);
                    head.push_back (_neurons[k]);
                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        neuron_network n (head, _neurons[l]);
                        for (unsigned int m = 0; m < _WEIGHTS_LENGTH; ++m)
                        {
                            n.set_out_neuron (_neurons[m]);
                            std::vector<neuron> h = n.head_neurons ();
                            TS_ASSERT_EQUALS (n.head_neurons_number (), 3)
                            TS_ASSERT_EQUALS (h[0], _neurons[i])
                            TS_ASSERT_EQUALS (h[1], _neurons[j])
                            TS_ASSERT_EQUALS (h[2], _neurons[k])
                            TS_ASSERT_EQUALS (n.out_neuron (), _neurons[m])
                        }
                    }
                }
    }

    void test_set_head_neurons (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _WEIGHTS_LENGTH; ++j)
                for (unsigned int k = 0; k < _WEIGHTS_LENGTH; ++k)
                    for (unsigned int l = 0; l < _WEIGHTS_LENGTH; ++l)
                    {
                        std::vector<neuron> head;
                        head.push_back (_neurons[i]);
                        head.push_back (_neurons[j]);
                        head.push_back (_neurons[k]);
                        neuron_network network (head, _neurons[l]);

                        /* Décommenter les lignes appropriées pour un
                         * maximum d'éclate !
                         */
                        for (unsigned int m = 0; m < _WEIGHTS_LENGTH; ++m)
                            /* for (unsigned int n = 0; n < _WEIGHTS_LENGTH; ++n) */
                                /* for (unsigned int o = 0; o < _WEIGHTS_LENGTH; ++o) */
                                {
                                    std::vector<neuron> new_head;
                                    new_head.push_back (_neurons[m]);

                                    new_head.push_back (_neurons[j]);
                                    new_head.push_back (_neurons[k]);
                                    /* new_head.push_back (_neurons[n]); */
                                    /* new_head.push_back (_neurons[o]); */

                                    network.set_head_neurons (new_head);
                                    std::vector<neuron> h = network.head_neurons ();
                                    TS_ASSERT_EQUALS (network.head_neurons_number (), 3)
                                    TS_ASSERT_EQUALS (h[0], _neurons[m])

                                    TS_ASSERT_EQUALS (h[1], _neurons[j])
                                    TS_ASSERT_EQUALS (h[2], _neurons[k])
                                    /* TS_ASSERT_EQUALS (h[1], _neurons[n]) */
                                    /* TS_ASSERT_EQUALS (h[2], _neurons[o]) */
                                    TS_ASSERT_EQUALS (network.out_neuron (), _neurons[l])
                                }
                    }
    }

    #undef _DOUBLE_ASSERT_EQUALS
};

bool test_suite_neuron_network::_POSSIBLE_INPUTS[_POSSIBLE_INPUTS_NUMBER];
double test_suite_neuron_network::_POSSIBLE_WEIGHTS[_POSSIBLE_WEIGHTS_NUMBER];

#endif /* __TEST_NEURON_NETWORK_HPP__ */
