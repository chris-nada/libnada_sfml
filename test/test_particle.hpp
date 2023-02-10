#pragma once

#include <doctest.h>
#include <nada/particle.hpp>
#include <functional>

using namespace nada;

class Test_particle { TEST_CASE_CLASS("Test_particle") {

    SUBCASE("smoketest") {
        Particle p = Particle::create_smoke();
    }

}};
