#include <string>
#include <string_view>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "Number.h"
#include "TypeName.h"

TEST_CASE("Number does arithmetic", "[number]") {
    SECTION("int uses the non-template overload from protolib") {
        CHECK(Number::Add(3, 4) == 7);
        CHECK(Number::Sub(3, 4) == -1);
        CHECK(Number::Multiply(3, 4) == 12);
        CHECK(Number::Divide(12, 4) == 3);
    }

    SECTION("other types use the template") {
        CHECK(Number::Add(1.5, 2.25) == 3.75);
        CHECK(Number::Divide(1.0, 4.0) == 0.25);
    }
}

TEST_CASE("TypeName strips the compiler specific parts", "[typename]") {
    CHECK(PrintT<int>() == "int");

    auto const name = PrintT<std::vector<int>>();
    CHECK(name.find("vector") != std::string_view::npos);
    CHECK(name.find("with T =") == std::string_view::npos);

    CHECK(PrintV(std::string{}).find("T =") == std::string_view::npos);
}
