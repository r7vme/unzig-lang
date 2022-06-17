#include <codecvt>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <memory>
#include <vector>

#include "ast.hpp"
#include "codegen.hpp"
#include "parser.hpp"
#include "sema.hpp"
#include "source.hpp"
#include "tokenizer.hpp"

namespace fs = std::filesystem;

std::string readFileIntoString(const std::string &path) {
  std::ifstream input_file(path);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << path << "'" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return std::string((std::istreambuf_iterator<char>(input_file)),
                     std::istreambuf_iterator<char>());
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: unzig <file>.uz" << std::endl;
    std::exit(1);
  }
  fs::path inputFilePath = argv[1];
  if (!fs::exists(inputFilePath)) {
    std::cerr << "File " << inputFilePath << " does not exist" << std::endl;
    std::exit(1);
  }
  std::string inputCode = readFileIntoString(inputFilePath);
  auto source = std::make_shared<SourceObject>(inputCode);

  std::string llFileName = inputFilePath.replace_extension("ll");
  std::string objFileName = inputFilePath.replace_extension("o");
  std::string dotFileName = inputFilePath.replace_extension("dot");
  std::string pngFileName = inputFilePath.replace_extension("png");
  std::string outputFile = inputFilePath.replace_extension();

  // prepare .ll file
  std::error_code OutErrorInfo;
  std::error_code ok;
  llvm::raw_fd_ostream llFile(llFileName, OutErrorInfo, llvm::sys::fs::OF_None);
  if (OutErrorInfo != ok) {
    std::cerr << "Unable to create .ll file" << std::endl;
    std::exit(1);
  }

  auto tokens = tokenize(source);
  auto ast = parse(tokens, source);
  SemanticAnalyzer sema;
  ast.sema(&sema);

  // AST graph
  DotGenerator g;
  ast.dotgen(&g);
  std::ofstream ofs(dotFileName);
  ofs << g.getDotOutput();
  ofs.close();
  auto dotCmd = std::string("dot -Tpng ") + dotFileName + " > " + pngFileName;
  if (std::system(dotCmd.c_str()) != 0) {
    std::cerr << "png generation failed" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  CodeGenerator codegen(source);
  auto code = ast.codegen(&codegen);
  if (!code) {
    std::cerr << "unzig: unable to generate code" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  codegen.getLLVMModule().print(llFile, nullptr);

  auto llcCmd = std::string("llc -filetype=obj ") + llFileName;
  if (std::system(llcCmd.c_str()) != 0) {
    std::cerr << "unzig: llc compilation failed" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // linker
  std::string linkerCmd = std::string("gcc -o ") + outputFile + " " + objFileName;
  if (std::system(linkerCmd.c_str()) != 0) {
    std::cerr << "unzig: linking failed" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << "unzig: compiled " << outputFile << std::endl;
  return EXIT_SUCCESS;
}
