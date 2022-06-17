#pragma once
#include <memory>
#include <string>

#include "ast.hpp"
#include "ast_node.hpp"
#include "source.hpp"
#include "tokenizer.hpp"

class ParserCtxt {
  const Tokens &tokens;
  const Source source;
  size_t cursor{0};

public:
  ParserCtxt(const Tokens &tokens, const Source source) : tokens(tokens), source(source){};

  const Token &getToken() const {
    assert(tokens.size() > cursor);
    return tokens[cursor];
  }

  const Source getSource() const { return source; }

  void skipToken() { cursor++; }

  const Token &getTokenAndAdvance() {
    const Token &t = getToken();
    skipToken();
    return t;
  }

  size_t getCursor() const { return cursor; }
  size_t getPrevCursor() const { return (cursor == 0) ? cursor : cursor - 1; }
  void resetCursor(const size_t newCursor) {
    assert(tokens.size() > newCursor);
    cursor = newCursor;
  }
};

AstNode parse(const Tokens &tokens, const Source &source);
