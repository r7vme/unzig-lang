#pragma once

#include <cstdlib>
#include <iostream>
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

class SemanticAnalyzer {
public:
  void fatalSemaError(const std::string &msg);
  void analyze(FloatExprNode &astNode);
  void analyze(IntegerExprNode &astNode);
  void analyze(BinExprNode &astNode);
  void analyze(VarDeclNode &astNode);
  void analyze(FnDefNode &astNode);
  void analyze(BlockNode &astNode);
  void analyze(RootNode &astNode);
  void analyze(AssignStNode &astNode);
  void analyze(ReturnStNode &astNode);
  void analyze(VarExprNode &astNode);
  void analyze(FnCallExprNode &astNode);
  void analyze(EmptyNode &astNode);
};
