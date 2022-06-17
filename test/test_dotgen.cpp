#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <filesystem>

#include "dotgen.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"
#include "code_example.hpp"

namespace fs = std::filesystem;

TEST_CASE("generates valid .dot graph", "[dotgen]") {
  auto source = std::make_shared<SourceObject>(codeExample);

  INFO("checking if dot is intalled");
  REQUIRE(std::system("hash dot") == 0);

  auto tokens = tokenize(source);
  auto ast = parse(tokens, source);
  DotGenerator g;
  ast.dotgen(&g);

  std::string dotTmpFile = fs::temp_directory_path() / "test_dotgen.dot";
  std::ofstream ofs(dotTmpFile);
  ofs << g.getDotOutput();
  ofs.close();

  auto dotCmd = std::string("dot -Tpng ") + dotTmpFile + " > /dev/null";
  INFO("checking if correct .dot file was generated");
  CHECK(std::system(dotCmd.c_str()) == 0);
  fs::remove(dotTmpFile);
}
