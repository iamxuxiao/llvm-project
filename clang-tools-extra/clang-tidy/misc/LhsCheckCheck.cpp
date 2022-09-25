//===--- LhsCheckCheck.cpp - clang-tidy -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "LhsCheckCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void LhsCheckCheck::registerMatchers(MatchFinder *Finder) {

  auto function_pattern = functionDecl();
  auto function_matcher = function_pattern.bind("function_node");  
  Finder->addMatcher(function_matcher, this);

  auto function_invoke_pattern = callExpr(has(implicitCastExpr(has(declRefExpr()))));    
  auto function_invoke_matcher = function_invoke_pattern.bind("function_invoke_node");  
  Finder->addMatcher(function_invoke_matcher, this);

  
}

void LhsCheckCheck::check(const MatchFinder::MatchResult &Result) {
  
  const auto *matched_function_decl = Result.Nodes.getNodeAs<FunctionDecl>("function_node");
  const auto *matched_invoke_decl = Result.Nodes.getNodeAs<CallExpr>("function_invoke_node");  

  if(matched_function_decl){
    diag(matched_function_decl->getLocation(), "found %0 as function")
      << matched_function_decl->getName();
  }
  if(matched_invoke_decl){
    diag(matched_invoke_decl->getRParenLoc(), "found invoke :%0")
      << matched_invoke_decl->getDirectCallee()->getName();
  }

  if(matched_function_decl && matched_invoke_decl){
     std::cout<<"<==== not possible to reach here ! \n";
   }
}

} // namespace misc
} // namespace tidy
} // namespace clang
