#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <stdexcept>

#include "catch2/matchers/catch_matchers.hpp"
#include "source.hpp"

using Catch::Matchers::Equals;

TEST_CASE("real use case", "[source]") {
  const std::string input = \
R"(fn foo() i32 {
    return 1;
}
)";

  const std::string expected = \
R"( |     return 1;
 |      ^       )";

  auto source = createSource(input);
  REQUIRE_THAT(source->getHightlightedPosition(20), Equals(expected));
}

TEST_CASE("out of range", "[source]") {
  const std::string input = R"(0123)";
  auto source = createSource(input);
  REQUIRE_THROWS_AS(source->getHightlightedPosition(input.size() + 10), std::out_of_range);
}
