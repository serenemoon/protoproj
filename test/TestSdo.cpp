#include <catch2/catch_test_macros.hpp>

#include "Sdo.h"

namespace {
using DL = Sdo::DataList<3, 6, 8, 19>;
using DP = Sdo::DataPairs<0x24, 0x35, 0x46, 0x57, 0x68, 0x79, 255>;
} /* namespace */

TEST_CASE("DataList checks membership", "[sdo]") {
    // Contains is not constexpr, so CHECK instead of STATIC_REQUIRE
    CHECK(DL::Contains(3));
    CHECK(DL::Contains(19));
    CHECK_FALSE(DL::Contains(4));
    CHECK(DL::NotContains(4));
}

TEST_CASE("DataPairs maps a key to its value, or falls back to the default", "[sdo]") {
    STATIC_REQUIRE(DP::ValueOfKey(0x24) == 0x35);
    STATIC_REQUIRE(DP::ValueOfKey(0x46) == 0x57);
    STATIC_REQUIRE(DP::ValueOfKey(0x68) == 0x79);
    STATIC_REQUIRE(DP::ValueOfKey(0x99) == 255);

    CHECK(DP{}.ValueOfKey(0x46) == 0x57);
    CHECK(DP{}[0x68] == 0x79);
    STATIC_REQUIRE(DP{}[0x24] == 0x35);
}
