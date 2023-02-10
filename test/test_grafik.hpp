#pragma once

#include <doctest.h>
#include <nada/graphic.hpp>
#include <functional>

using namespace nada;

class Test_grafik { TEST_CASE_CLASS("Test_grafik") {

    SUBCASE("smoketest") {
        Graphic g("anything");
    }

}};
