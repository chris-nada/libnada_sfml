#pragma once

#include <doctest.h>
#include <nada/particle.hpp>
#include <functional>

class Test_misc { TEST_CASE_CLASS("Test_particle") {

    SUBCASE("smoketest") {
        Particle p = Particle::create_smoke();
    }

}};
