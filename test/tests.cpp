#define DOCTEST_CONFIG_IMPLEMENT
//#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include <doctest.h>

#include "test_particle.hpp"
#include "test_grafik.hpp"

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("order-by", "name");
    context.applyCommandLine(argc, argv);
    const auto res = context.run();
    context.shouldExit();
    return res;
}
