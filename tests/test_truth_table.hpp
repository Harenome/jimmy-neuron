/**
 * \file test_truth_table.hpp
 * \brief Test truth table.
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
#ifndef __TEST_TRUTH_TABLE_HPP__
#define __TEST_TRUTH_TABLE_HPP__

#include "truth_table.hpp"

class test_suite_truth_table: public CxxTest::TestSuite
{
private:
    static const unsigned int _POSSIBLE_BOOLS_NUMBER = 2;
    static bool _POSSIBLE_BOOLS[_POSSIBLE_BOOLS_NUMBER];

public:
    /**
     * \brief Initialisation avant chaque test.
     */
    void setUp (void)
    {
        _POSSIBLE_BOOLS[0] = false;
        _POSSIBLE_BOOLS[0] = true;
    }

    /**
     * \brief Nettoyage après chaque test.
     */
    void tearDown (void)
    {
    }

    /**
     * \brief Test constructeur truth_table::truth_table(void)
     * \test truth_table::truth_table(void)
     */
    void test_constructor_void (void)
    {
        truth_table * t;
        TS_ASSERT_THROWS_NOTHING (t = new truth_table ())
        delete t;
    }

    /**
     * \brief Test constructeur truth_table::truth_table(bool, bool, bool, bool)
     * \test truth_table::truth_table(bool, bool, bool, bool)
     */
    void test_constructor_bools (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        truth_table * t;
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        TS_ASSERT_THROWS_NOTHING (t = new truth_table (bi, bj, bk, bl))
                        delete t;
                    }
    }

    /**
     * \brief Test constructeur truth_table::truth_table(const truth_talbe &)
     * \test truth_table::truth_table(const truth_talbe &)
     */
    void test_construtor_copy (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        truth_table t (bi, bj, bk, bl);
                        truth_table * copy;
                        TS_ASSERT_THROWS_NOTHING (copy = new truth_table (t))
                        delete copy;
                    }
    }

    /**
     * \brief Test truth_table::result
     * \test truth_table::result
     */
    void test_result (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        truth_table t (bi, bj, bk, bl);

                        TS_ASSERT_EQUALS (bi, t.result (false, false))
                        TS_ASSERT_EQUALS (bj, t.result (false, true))
                        TS_ASSERT_EQUALS (bk, t.result (true, false))
                        TS_ASSERT_EQUALS (bl, t.result (true, true))
                    }
    }

    /**
     * \brief Test truth_table::equals
     * \test truth_table::equals
     */
    void test_equals (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        truth_table t (bi, bj, bk, bl);
                        truth_table u (! bi, bj, bk, bl);

                        TS_ASSERT_EQUALS (true, t.equals (t))
                        TS_ASSERT_EQUALS (false, t.equals (u))
                    }
    }

    /**
     * \brief Test truth_table::set_result
     * \test truth_table::set_result
     */
    void test_set_result (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        truth_table t (bi, bj, bk, bl);

                        t.set_result (false, false, ! bi);
                        TS_ASSERT_EQUALS (! bi, t.result (false, false))
                   }
    }

    /**
     * \brief Test operator==(const truth_table &, const truth_table &)
     * \test operator==(const truth_table &, const truth_table &)
     */
    void test_operator_equals (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        truth_table t (bi, bj, bk, bl);
                        truth_table u (! bi, bj, bk, bl);

                        TS_ASSERT_EQUALS (true, t == t)
                        TS_ASSERT_EQUALS (false, t == u)
                    }
    }

    /**
     * \brief Test operator!=(const truth_table &, const truth_table &)
     * \test operator!=(const truth_table &, const truth_table &)
     */
    void test_operator_differs (void)
    {
        for (unsigned int i = 0; i < _POSSIBLE_BOOLS_NUMBER; ++i)
            for (unsigned int j = 0; j < _POSSIBLE_BOOLS_NUMBER; ++j)
                for (unsigned int k = 0; k < _POSSIBLE_BOOLS_NUMBER; ++k)
                    for (unsigned int l = 0; l < _POSSIBLE_BOOLS_NUMBER; ++l)
                    {
                        bool bi = _POSSIBLE_BOOLS[i];
                        bool bj = _POSSIBLE_BOOLS[j];
                        bool bk = _POSSIBLE_BOOLS[k];
                        bool bl = _POSSIBLE_BOOLS[l];
                        truth_table t (bi, bj, bk, bl);
                        truth_table u (! bi, bj, bk, bl);

                        TS_ASSERT_EQUALS (false, t != t)
                        TS_ASSERT_EQUALS (true, t != u)
                    }
    }
};

bool test_suite_truth_table::_POSSIBLE_BOOLS[_POSSIBLE_BOOLS_NUMBER];

#endif /* __TEST_TRUTH_TABLE_HPP__ */
