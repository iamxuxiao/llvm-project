//===--- MyFirstCheckCheck.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MyFirstCheckCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void MyFirstCheckCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(functionDecl().bind("func"), this);
}

void MyFirstCheckCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedFunc = Result.Nodes.getNodeAs<FunctionDecl>("func");
  
  if (!MatchedFunc->getIdentifier() || MatchedFunc->getName().startswith("awesome_"))
    return;

  if (MatchedFunc->getIdentifier() ){
    std::string Name = MatchedFunc->getNameAsString();
    const auto return_type = MatchedFunc->getReturnType();
    //std::cout<< MatchedFunc->getReturnType() <<std::endl; 


    
    diag(MatchedFunc->getLocation(), "{'return_type': %0, 'number of parameter': %1, 'IsPointer': %2} ")
    << MatchedFunc->getReturnType()
    << MatchedFunc->getNumParams()
    << MatchedFunc->getReturnType()->isPointerType()  ;
    
    const auto *ParamIt = MatchedFunc->param_begin();    
    while (ParamIt != MatchedFunc->param_end()) {
      auto ParamName = (*ParamIt)->getName();
      diag(MatchedFunc->getLocation(), "{'Parameter Name': %0} ") << ParamName;
      ++ParamIt;
    }

  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
