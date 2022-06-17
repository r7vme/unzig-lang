#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "ast_node.hpp"
#include "codegen.hpp"
#include "dotgen.hpp"
#include "scope.hpp"
#include "sema.hpp"
#include "types.hpp"

#define COMMON_MEMBERS(CLASS)                                                                      \
  size_t sourcePos{0};                                                                             \
  Scope scope{nullptr};                                                                            \
  void setScope(Scope newScope) { scope = newScope; };                                             \
  Scope &getScope() { return scope; };                                                             \
  const uint64_t nodeId{curNodeId++};                                                              \
  uint64_t getNodeId() const { return nodeId; };                                                   \
  llvm::Value *codegen(CodeGenerator *g) const { return g->generate(*this); };                     \
  void dotgen(DotGenerator *g) const { return g->generate(*this); };                               \
  void sema(SemanticAnalyzer *g) { return g->analyze(*this); };                                    \
  bool isEqual(const CLASS &other) const;

#define IS_EMPTY_NODE_FALSE                                                                        \
  bool isEmptyNode() const { return false; };

#define AST_NODE_MEMBERS(CLASS)                                                                    \
  COMMON_MEMBERS(CLASS)                                                                            \
  IS_EMPTY_NODE_FALSE

static uint64_t curNodeId{0};
enum BinOpType { ADD, SUB, MUL, DIV };
using MayBeAstNode = std::optional<AstNode>;

struct EmptyNode {
  bool isEmptyNode() const { return true; };
  COMMON_MEMBERS(EmptyNode);
};

struct FnCallExprNode {
  const std::string callee;

  FnCallExprNode(const std::string &callee, const size_t sourcePos)
      : callee(callee), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(FnCallExprNode);
};

struct VarExprNode {
  const std::string name;

  Symbol varSymbol{nullptr};

  VarExprNode(const std::string &name, const size_t sourcePos) : name(name), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(VarExprNode)
};

struct FloatExprNode {
  const std::string value;

  FloatExprNode(const std::string &value, const size_t sourcePos)
      : value(value), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(FloatExprNode)
};

struct IntegerExprNode {
  const std::string value;

  IntegerExprNode(const std::string &value, const size_t sourcePos)
      : value(value), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(IntegerExprNode)
};

struct BinExprNode {
  BinOpType type;
  AstNode lhs, rhs;

  BinExprNode(const BinOpType type, const AstNode lhs, const AstNode rhs, const size_t sourcePos)
      : type(type), lhs(lhs), rhs(rhs), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(BinExprNode)
};

struct AssignStNode {
  const std::string varName;
  AstNode expr;

  Symbol varSymbol{nullptr};

  AssignStNode(const std::string &varName, const AstNode expr, const size_t sourcePos)
      : varName(varName), expr(expr), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(AssignStNode)
};

struct ReturnStNode {
  AstNode expr;

  ReturnStNode(const AstNode expr, const size_t sourcePos) : expr(expr), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(ReturnStNode)
};

struct BlockNode {
  std::vector<AstNode> statements;

  BlockNode(const std::vector<AstNode> statements, const size_t sourcePos)
      : statements(statements), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(BlockNode)
};

struct FnDefNode {
  const std::string name;
  const UzType returnType;
  AstNode body;

  FnDefNode(const std::string &name, const UzType &returnType, const AstNode body,
            const size_t sourcePos)
      : name(name), returnType(returnType), body(body), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(FnDefNode)
};

struct VarDeclNode {
  const std::string name;
  const UzType type;
  AstNode initExpr;

  Symbol symbol{nullptr};

  VarDeclNode(const std::string &name, const UzType &type, const AstNode initExpr,
              const size_t sourcePos)
      : name(name), type(type), initExpr(initExpr), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(VarDeclNode)
};

struct RootNode {
  std::vector<AstNode> declarations;

  RootNode(const std::vector<AstNode> declarations, const size_t sourcePos)
      : declarations(declarations), sourcePos(sourcePos) {}
  AST_NODE_MEMBERS(RootNode)
};
