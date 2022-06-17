#pragma once

#include "types.hpp"
#include <llvm/IR/Instructions.h>
#include <memory>
#include <string>

enum class SymbolType {
  Var,
  Fn,
};

struct SymbolObject {
  SymbolType symbolType;
  std::string name;
  UzType dataType;
  bool isGlobal;
  llvm::AllocaInst *allocaInst;
};

using Symbol = std::shared_ptr<SymbolObject>;

inline Symbol createSymbol(SymbolType symbolType, const std::string &name, const UzType dataType,
                           const bool isGlobal) {
  auto symbol = std::make_shared<SymbolObject>();
  symbol->symbolType = symbolType;
  symbol->name = name;
  symbol->dataType = dataType;
  symbol->isGlobal = isGlobal;
  symbol->allocaInst = nullptr;
  return symbol;
}
