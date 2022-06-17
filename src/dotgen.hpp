#pragma once

#include <string>

class FloatExprNode;
class IntegerExprNode;
class BinExprNode;
class VarDeclNode;
class FnDefNode;
class BlockNode;
class RootNode;
class AssignStNode;
class ReturnStNode;
class VarExprNode;
class FnCallExprNode;
class EmptyNode;

class DotGenerator {
  std::string output;

public:
  std::string getDotOutput();
  void generate(const FloatExprNode &astNode);
  void generate(const IntegerExprNode &astNode);
  void generate(const BinExprNode &astNode);
  void generate(const VarDeclNode &astNode);
  void generate(const FnDefNode &astNode);
  void generate(const BlockNode &astNode);
  void generate(const RootNode &astNode);
  void generate(const AssignStNode &astNode);
  void generate(const ReturnStNode &astNode);
  void generate(const VarExprNode &astNode);
  void generate(const FnCallExprNode &astNode);
  void generate(const EmptyNode &astNode);
};
