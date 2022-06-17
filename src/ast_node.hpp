#pragma once

#include <cstdint>
#include <memory>

#include "codegen.hpp"
#include "dotgen.hpp"
#include "scope.hpp"
#include "sema.hpp"

// Inspired by https://www.foonathan.net/2020/01/type-erasure/
// use std::shared_ptr to prevent copies
class AstNode {
  class Base {
  public:
    virtual ~Base() = default;
    virtual bool isEqual(const Base &other) const = 0;
    virtual bool isEmptyNode() const = 0;
    virtual llvm::Value *codegen(CodeGenerator *g) const = 0;
    virtual void dotgen(DotGenerator *g) const = 0;
    virtual void sema(SemanticAnalyzer *g) = 0;
    virtual uint64_t getNodeId() const = 0;
    virtual void setScope(Scope newScope) = 0;
    virtual Scope &getScope() = 0;
  };

  template <typename T> class Wrapper final : public Base {
  public:
    Wrapper(T obj) : obj(std::move(obj)) {}
    bool isEqual(const Base &other) const override {
      return (typeid(*this) == typeid(other)) &&
             obj.isEqual(static_cast<const Wrapper<T> &>(other).obj);
    };
    bool isEmptyNode() const { return obj.isEmptyNode(); };
    llvm::Value *codegen(CodeGenerator *g) const override { return obj.codegen(g); };
    void dotgen(DotGenerator *g) const override { obj.dotgen(g); };
    void sema(SemanticAnalyzer *g) override { obj.sema(g); };
    uint64_t getNodeId() const override { return obj.getNodeId(); };
    void setScope(Scope newScope) override { obj.setScope(newScope); };
    Scope &getScope() override { return obj.getScope(); };

  private:
    T obj;
  };

public:
  template <typename T> AstNode(T obj) : ptr(std::make_shared<Wrapper<T>>(std::move(obj))) {}
  AstNode(const AstNode &other) : ptr(other.ptr) {}
  AstNode &operator=(const AstNode other) {
    ptr = other.ptr;
    return *this;
  }
  bool operator==(const AstNode &other) const { return ptr->isEqual(*other.ptr); }
  operator bool() const { return !(ptr->isEmptyNode()); }
  llvm::Value *codegen(CodeGenerator *g) const { return ptr->codegen(g); };
  void dotgen(DotGenerator *g) const { ptr->dotgen(g); }
  void sema(SemanticAnalyzer *g) { ptr->sema(g); }
  uint64_t getNodeId() const { return ptr->getNodeId(); };
  void setScope(Scope newScope) { ptr->setScope(newScope); };
  Scope &getScope() { return ptr->getScope(); };

private:
  std::shared_ptr<Base> ptr;
};
