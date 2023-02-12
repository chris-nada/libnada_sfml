#pragma once

#include <doctest.h>
#include <nada/graphic.hpp>
#include <functional>
#include "nada/multigraphic.hpp"

using namespace nada;

class Test_grafik { TEST_CASE_CLASS("Test_grafik") {

    SUBCASE("smoketest") {
        Graphic g("anything");
    }

    SUBCASE("multigraphic") {
        Multigraphic g({"g1.jpg"}, 0, 0);
    }

}};
