// Copyright (c) 2020 The SBER developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef SBER_SAPLING_TEST_FIXTURE_H
#define SBER_SAPLING_TEST_FIXTURE_H

#include "test/test_sber.h"

/**
 * Testing setup that configures a complete environment for Sapling testing.
 */
struct SaplingTestingSetup : public TestingSetup {
    SaplingTestingSetup();
    ~SaplingTestingSetup();
};


#endif //SBER_SAPLING_TEST_FIXTURE_H
