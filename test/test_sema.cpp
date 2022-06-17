#include <catch2/catch_test_macros.hpp>

#include "parser.hpp"
#include "sema.hpp"
#include "source.hpp"
#include "tokenizer.hpp"
#include "code_example.hpp"

TEST_CASE("functions", "[sema]") {
  auto source = std::make_shared<SourceObject>(codeExample);
  auto tokens = tokenize(source);
  auto ast = parse(tokens, source);
  SemanticAnalyzer sema;
  ast.sema(&sema);
  REQUIRE(true);
}
