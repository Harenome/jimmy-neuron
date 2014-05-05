/**
 * \file test_neuron.hpp
 * \brief Test neuron.
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
#include <list>
#include <vector>
#include <limits>
#include <cmath>
#include <cxxtest/TestSuite.h>

#include "neuron.hpp"


/**
 * \brief Suite de tests pour \r neuron.
 * \sa neuron
 */
class test_suite_neuron: public CxxTest::TestSuite
{
private:
    static const unsigned int _INPUTS_LENGTH = 4;
    static const unsigned int _WEIGHTS_LENGTH = 25;
    static const unsigned int _POSSIBLE_INPUTS_NUMBER = 2;
    static const unsigned int _POSSIBLE_WEIGHTS_NUMBER = 5;
    static bool _POSSIBLE_INPUTS[_POSSIBLE_INPUTS_NUMBER];
    static double _POSSIBLE_WEIGHTS[_POSSIBLE_WEIGHTS_NUMBER];
    std::list<bool> _inputs[_INPUTS_LENGTH];
    std::vector<double> _weights[_WEIGHTS_LENGTH];

    static inline bool _double_compare (long double a, long double b)
    {
        return std::fabs (a - b) < std::numeric_limits<double>::epsilon ();
    }

    static inline long double _accumulate (const std::vector<double> weights, const std::list<bool> & inputs)
    {
        long double accumulator = 0.0;

        std::list<bool>::const_iterator it = inputs.begin ();
        std::vector<double>::const_iterator jt = weights.begin ();
        for ( ; jt != weights.end (); ++it, ++jt)
            if (* it)
                accumulator += * jt;

        return accumulator;
    }

    #define _DOUBLE_ASSERT_EQUALS(a, b) TS_ASSERT_EQUALS (true, test_suite_neuron::_double_compare (a, b))

public:
    /**
     * \brief Initialisation avant chaque test.
     */
    void setUp (void)
    {
        _POSSIBLE_INPUTS[0] = true;
        _POSSIBLE_INPUTS[1] = false;

        _POSSIBLE_WEIGHTS[0] = 0.0;
        _POSSIBLE_WEIGHTS[1] = 1.0;
        _POSSIBLE_WEIGHTS[2] = -1.0;
        _POSSIBLE_WEIGHTS[3] = std::numeric_limits<double>::min ();
        _POSSIBLE_WEIGHTS[4] = std::numeric_limits<double>::max ();

        for (unsigned int i = 0; i < _POSSIBLE_INPUTS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_INPUTS_NUMBER; ++j)
            {
                _inputs[i + _POSSIBLE_INPUTS_NUMBER * j].push_back (_POSSIBLE_INPUTS[i]);
                _inputs[i + _POSSIBLE_INPUTS_NUMBER * j].push_back (_POSSIBLE_INPUTS[j]);
            }

        for (unsigned int i = 0; i < _POSSIBLE_WEIGHTS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_WEIGHTS_NUMBER; ++j)
            {
                _weights[i + _POSSIBLE_WEIGHTS_NUMBER * j].push_back (_POSSIBLE_WEIGHTS[i]);
                _weights[i + _POSSIBLE_WEIGHTS_NUMBER * j].push_back (_POSSIBLE_WEIGHTS[j]);
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
    }

    /**
     * \brief Test du constructeur neuron::neuron(void).
     * \test neuron::neuron(void)
     */
    void test_constructor_void (void)
    {
        neuron * n;
        TS_ASSERT_THROWS_NOTHING (n = new neuron ())
        delete n;
    }

    /**
     * \brief Test du constructeur neuron::neuron(const std::vector<double> &).
     * \test neuron::neuron(const std::vector<double> &)
     */
    void test_constructor_weights (void)
    {
        neuron * n;

        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            TS_ASSERT_THROWS_NOTHING (n = new neuron (_weights[i]))
            delete n;
        }
    }

    /**
     * \brief Test du constructeur neuron::neuron(const neuron &)
     * \test neuron::neuron(const neuron &)
     */
    void test_constructor_neuron (void)
    {
        neuron * copy;

        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            TS_ASSERT_THROWS_NOTHING (copy = new neuron (n))
            delete copy;
        }
    }

    /**
     * \brief Test de neuron::weights
     * \test neuron::weights
     */
    void test_weights (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            std::vector<double> weights = n.weights ();
            TS_ASSERT_EQUALS (weights.size (), _weights[i].size ())
            for (unsigned int j = 0; j < weights.size (); ++j)
                _DOUBLE_ASSERT_EQUALS (weights[j], _weights[i][j])
        }
    }

    /**
     * \brief Test de neuron::weight_number
     * \test neuron::weight_number
     */
    void test_weight_number (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            TS_ASSERT_EQUALS (n.weight_number (), _weights[i].size ())
        }
    }

    void test_accumulate (void)
    {
        for (unsigned int i = 0; i < 2; ++i)
            for (unsigned int j = 0; j < _INPUTS_LENGTH; ++j)
            {
                const std::vector<double> & weights = _weights[i];
                const std::list<bool> & inputs = _inputs[j];
                neuron n (weights);
                long double accumulator = test_suite_neuron::_accumulate (weights, inputs);

                _DOUBLE_ASSERT_EQUALS (n.accumulate (inputs), accumulator)
            }
    }

    /**
     * \brief Test de neuron::weight_attempt
     * \test neuron::weight_attempt
     */
    void test_attempt (void)
    {
        for (unsigned int i = 0; i < 2; ++i)
            for (unsigned int j = 0; j < _INPUTS_LENGTH; ++j)
            {
                const std::vector<double> & weights = _weights[i];
                const std::list<bool> & inputs = _inputs[j];

                neuron n (weights);
                bool attempt = n.attempt (inputs);

                std::list<bool>::size_type inputs_size = inputs.size ();
                std::vector<double>::size_type weights_size = weights.size ();

                bool result = inputs_size >= weights_size;

                if (result)
                    result = test_suite_neuron::_accumulate (weights, inputs) >= 0.5;

                TS_ASSERT_EQUALS (attempt, result)
            }
    }

    /**
     * \brief Test de neuron::operator[]
     * \test neuron::operator[]
     */
    void test_operator_square_brackets (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            for (unsigned int j = 0; j < _weights[i].size ();++j)
                _DOUBLE_ASSERT_EQUALS (n[j], _weights[i][j])
        }
    }

    /**
     * \brief Test de neuron::begin
     * \test neuron::begin
     */
    void test_begin (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            neuron_iterator it = n.begin ();
            if (n.weight_number () > 0)
                _DOUBLE_ASSERT_EQUALS (* it, n[0])
        }
    }

    /**
     * \brief Test de neuron::end
     * \test neuron::end
     */
    void test_end (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            neuron_iterator it = n.end ();
            neuron_size_type number = n.weight_number ();
            if (number > 0)
            {
                --it;
                _DOUBLE_ASSERT_EQUALS (* it, n[number - 1])
            }
        }
    }

    /**
     * \brief Test de neuron::begin
     * \test neuron::begin
     */
    void test_begin_const (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            neuron_const_iterator it = n.begin ();
            if (n.weight_number () > 0)
                _DOUBLE_ASSERT_EQUALS (* it, n[0])
        }
    }

    /**
     * \brief Test de neuron::end
     * \test neuron::end
     */
    void test_end_const (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
        {
            neuron n (_weights[i]);
            neuron_const_iterator it = n.end ();
            neuron_size_type number = n.weight_number ();
            if (number > 0)
            {
                --it;
                _DOUBLE_ASSERT_EQUALS (* it, n[number - 1])
            }
        }
    }

    /**
     * \brief Test de neuron::add_weight
     * \test neuron::add_weight
     */
    void test_add_weight (void)
    {
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_WEIGHTS_NUMBER; ++j)
            {
                neuron n (_weights[i]);
                n.add_weight (_POSSIBLE_WEIGHTS[j]);

                neuron_size_type number = n.weight_number ();
                _DOUBLE_ASSERT_EQUALS (number, _weights[i].size () + 1)
                for (unsigned int k = 0; k < _weights[i].size (); ++k)
                    _DOUBLE_ASSERT_EQUALS (n[k], _weights[i][k])
                _DOUBLE_ASSERT_EQUALS (n[number - 1], _POSSIBLE_WEIGHTS[j])
            }
    }

    /**
     * \brief Test de neuron::add_weight
     * \test neuron::add_weight
     */
    void test_set_weight (void)
    {
        /* Crazy ! */
        for (unsigned int i = 0; i < _WEIGHTS_LENGTH; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_WEIGHTS_NUMBER; ++j)
                for (unsigned int k = 0; k < _weights[i].size (); ++k)
                {
                    neuron n (_weights[i]);
                    n.set_weight (k, _POSSIBLE_WEIGHTS[j]);

                    neuron_size_type number = n.weight_number ();
                    TS_ASSERT_EQUALS (number, _weights[i].size ())

                    for (unsigned int l = 0; l < k; ++l)
                        _DOUBLE_ASSERT_EQUALS (n[l], _weights[i][l])
                    _DOUBLE_ASSERT_EQUALS (n[k], _POSSIBLE_WEIGHTS[j])
                    for (unsigned int l = k + 1; l < number; ++l)
                        _DOUBLE_ASSERT_EQUALS (n[l], _weights[i][l])
                }
    }

    #undef _DOUBLE_ASSERT_EQUALS
};

bool test_suite_neuron::_POSSIBLE_INPUTS[_POSSIBLE_INPUTS_NUMBER];
double test_suite_neuron::_POSSIBLE_WEIGHTS[_POSSIBLE_WEIGHTS_NUMBER];

