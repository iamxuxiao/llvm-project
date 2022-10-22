//===--- FunctionSignatureCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FunctionSignatureCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void FunctionSignatureCheck::registerMatchers(MatchFinder *Finder) {

  Finder->addMatcher(functionDecl().bind("function_decl"), this);
}

void FunctionSignatureCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *matched_function_decl = Result.Nodes.getNodeAs<FunctionDecl>("function_decl");
  if (!matched_function_decl->getIdentifier())
    return;

  
  // if matched
  std::string all_params = "";  
  for(auto param_it = matched_function_decl->param_begin();
      param_it != matched_function_decl->param_end();
      ++param_it){
    std::string ParamenterName = (*param_it)->getType().getAsString();
    all_params = all_params + "," +  ParamenterName;       
  }

  
  diag(matched_function_decl->getLocation(), "Name:%0; ReturnType:%1; IsPointer:%2; ParameterType:%3")
    << matched_function_decl->getName()
    << matched_function_decl->getReturnType()
    << matched_function_decl->getReturnType()->isPointerType()
    << StringRef(all_params)
    ;
}

} // namespace misc
} // namespace tidy
} // namespace clang
