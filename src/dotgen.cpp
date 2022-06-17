#include "dotgen.hpp"
#include "ast.hpp"
#include <iostream>
#include <sstream>
#include <string>

std::string getNodeId(const AstNode &astNode) { return std::to_string(astNode.getNodeId()); }

std::string DotGenerator::getDotOutput() {
  return std::string("digraph \"AST\" {\n") + output + "}";
}

void DotGenerator::generate(const FloatExprNode &astNode) {
  const auto text = std::string("FloatExpr\\n") + astNode.value;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");
}

void DotGenerator::generate(const IntegerExprNode &astNode) {
  const auto text = std::string("IntegerExpr\\n") + astNode.value;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");
}

void DotGenerator::generate(const BinExprNode &astNode) {
  std::string binOpType;
  switch (astNode.type) {
  case BinOpType::ADD:
    binOpType = "+";
    break;
  case BinOpType::SUB:
    binOpType = "-";
    break;
  case BinOpType::MUL:
    binOpType = "*";
    break;
  case BinOpType::DIV:
    binOpType = "/";
    break;
  }

  const auto text = std::string("BinExpr\\n") + binOpType;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  // lhs
  astNode.lhs.dotgen(this);
  output.append(nodeId + "->" + getNodeId(astNode.lhs) + "\n");

  // rhs
  astNode.rhs.dotgen(this);
  output.append(nodeId + "->" + getNodeId(astNode.rhs) + "\n");
}

void DotGenerator::generate(const VarDeclNode &astNode) {
  const auto text = std::string("VarDecl\\n") + astNode.name;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  astNode.initExpr.dotgen(this);
  output.append(nodeId + "->" + getNodeId(astNode.initExpr) + "\n");
}

void DotGenerator::generate(const FnDefNode &astNode) {
  const auto text = std::string("FnDef\\n") + astNode.name;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  astNode.body.dotgen(this);
  output.append(nodeId + "->" + getNodeId(astNode.body) + "\n");
}

void DotGenerator::generate(const BlockNode &astNode) {
  const auto text = std::string("Block");
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  for (auto &d : astNode.statements) {
    d.dotgen(this);
    output.append(nodeId + "->" + getNodeId(d) + "\n");
  }
}

void DotGenerator::generate(const RootNode &astNode) {
  const auto text = std::string("Root");
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  for (auto &d : astNode.declarations) {
    d.dotgen(this);
    output.append(nodeId + "->" + getNodeId(d) + "\n");
  }
}
void DotGenerator::generate(const AssignStNode &astNode) {
  const auto text = std::string("AssignSt\\n") + astNode.varName;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  astNode.expr.dotgen(this);
  output.append(nodeId + "->" + getNodeId(astNode.expr) + "\n");
}

void DotGenerator::generate(const ReturnStNode &astNode) {
  const auto text = std::string("ReturnSt");
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");

  astNode.expr.dotgen(this);
  output.append(nodeId + "->" + getNodeId(astNode.expr) + "\n");
}

void DotGenerator::generate(const VarExprNode &astNode) {
  const auto text = std::string("VarExpr\\n") + astNode.name;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");
}

void DotGenerator::generate(const FnCallExprNode &astNode) {
  const auto text = std::string("FnCallExpr\\n") + astNode.callee;
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");
}

void DotGenerator::generate(const EmptyNode &astNode) {
  const auto text = std::string("Empty\\n");
  const auto nodeId = getNodeId(astNode);
  output.append(nodeId + "[label=\"" + text + "\"]\n");
}
