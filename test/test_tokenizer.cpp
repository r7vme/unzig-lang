#include <catch2/catch_test_macros.hpp>

#include "source.hpp"
#include "tokenizer.hpp"

TEST_CASE("function + main", "[tokenizer]") {
  std::string raw = R"(
fn foo() u64 {
  return 1;
}

pub fn main() void {
  var x: u64 = foo();
  var y: u64 = 123;
  y = 1 + 2;
}
)";
  auto s = std::make_shared<SourceObject>(raw);

  Tokens expectedTokens = {
      // fn foo
      Token{TokenId::KwFn, "", 0},
      Token{TokenId::Identifier, "foo", 0},
      Token{TokenId::LParen, "", 0},
      Token{TokenId::RParen, "", 0},
      Token{TokenId::Identifier, "u64", 0},
      Token{TokenId::LBrace, "", 0},
      // foo block
      Token{TokenId::KwReturn, "", 0},
      Token{TokenId::IntegerLiteral, "1", 0},
      Token{TokenId::Semicolon, "", 0},
      // end foo block
      Token{TokenId::RBrace, "", 0},
      // fn main
      Token{TokenId::KwPub, "", 0},
      Token{TokenId::KwFn, "", 0},
      Token{TokenId::Identifier, "main", 0},
      Token{TokenId::LParen, "", 0},
      Token{TokenId::RParen, "", 0},
      Token{TokenId::Identifier, "void", 0},
      Token{TokenId::LBrace, "", 0},
      // main block
      // line 1
      Token{TokenId::KwVar, "", 0},
      Token{TokenId::Identifier, "x", 0},
      Token{TokenId::Colon, "", 0},
      Token{TokenId::Identifier, "u64", 0},
      Token{TokenId::Equal, "", 0},
      Token{TokenId::Identifier, "foo", 0},
      Token{TokenId::LParen, "", 0},
      Token{TokenId::RParen, "", 0},
      Token{TokenId::Semicolon, "", 0},
      // line 2
      Token{TokenId::KwVar, "", 0},
      Token{TokenId::Identifier, "y", 0},
      Token{TokenId::Colon, "", 0},
      Token{TokenId::Identifier, "u64", 0},
      Token{TokenId::Equal, "", 0},
      Token{TokenId::IntegerLiteral, "123", 0},
      Token{TokenId::Semicolon, "", 0},
      // line 3
      Token{TokenId::Identifier, "y", 0},
      Token{TokenId::Equal, "", 0},
      Token{TokenId::IntegerLiteral, "1", 0},
      Token{TokenId::Plus, "", 0},
      Token{TokenId::IntegerLiteral, "2", 0},
      Token{TokenId::Semicolon, "", 0},
      // end main block
      Token{TokenId::RBrace, "", 0},
      Token{TokenId::Eof, "", 0},
  };

  auto actualTokens = tokenize(s);

  // debug
  // for (auto &token : actualTokens) {
  //   std::cout << token << std::endl;
  // }

  REQUIRE(actualTokens == expectedTokens);
}

TEST_CASE("last char is part of identifier or number", "[tokenizer]") {
  REQUIRE(tokenize(std::make_shared<SourceObject>("1")) ==
          Tokens{Token{TokenId::IntegerLiteral, "1", 0}, Token{TokenId::Eof, "", 0}});
  REQUIRE(tokenize(std::make_shared<SourceObject>("foo")) ==
          Tokens{Token{TokenId::Identifier, "foo", 0}, Token{TokenId::Eof, "", 0}});
}

TEST_CASE("empty string", "[tokenizer]") {
  REQUIRE(tokenize(std::make_shared<SourceObject>("")) == Tokens{Token{TokenId::Eof, "", 0}});
}
