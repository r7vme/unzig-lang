#pragma once

#include "source.hpp"
#include <cstdint>
#include <string>
#include <vector>

enum class TokenId {
  Eof,
  FloatLiteral,
  IntegerLiteral,
  Identifier,
  Asterisk,
  Colon,
  Equal,
  LBrace,
  LParen,
  Minus,
  Plus,
  RBrace,
  RParen,
  Semicolon,
  Slash,
  KwFn,
  KwPub,
  KwReturn,
  KwVar
};

struct Token {
  Token(const TokenId id, const std::string &value, const size_t position)
      : id(id), value(value), position(position) {}

  TokenId id;
  std::string value;
  size_t position;

  friend std::ostream &operator<<(std::ostream &os, const Token &o);
};

using Tokens = std::vector<Token>;

bool operator==(const Token &lhs, const Token &rhs);

Tokens tokenize(const Source in);
