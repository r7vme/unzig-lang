#include "scope.hpp"

void ScopeObject::insertSymbol(const Symbol &symbol) { table.insert({symbol->name, symbol}); }

std::optional<Symbol> ScopeObject::lookupSymbol(const std::string &name) const {
  auto it = table.find(name);
  if (it != table.end()) {
    return it->second;
  }
  if (parent) {
    return parent->lookupSymbol(name);
  }
  return std::nullopt;
}

Scope createScope(const Scope parent) { return std::make_shared<ScopeObject>(parent); }

ScopeObject::ScopeObject(const Scope parent) : parent(parent) {}
