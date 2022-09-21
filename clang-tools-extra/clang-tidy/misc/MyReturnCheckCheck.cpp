//===--- MyReturnCheckCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MyReturnCheckCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void MyReturnCheckCheck::registerMatchers(MatchFinder *Finder) {

  auto if_return_nullptr_pattern =   functionDecl(has(compoundStmt(has(ifStmt(has(compoundStmt(has(returnStmt(has(implicitCastExpr(has(cxxNullPtrLiteralExpr())))))))))))).bind("if_return");
  Finder->addMatcher(if_return_nullptr_pattern, this);


  
  auto direct_return_nullptr_pattern =
   functionDecl(has(compoundStmt(has(returnStmt(has(implicitCastExpr(has(cxxNullPtrLiteralExpr())))).bind("direct")))));

  Finder->addMatcher(direct_return_nullptr_pattern, this);
  
}

void MyReturnCheckCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *MatchedIfReturn = Result.Nodes.getNodeAs<FunctionDecl>("if_return");
  if(MatchedIfReturn)
    diag(MatchedIfReturn->getLocation(), "found %0 as if return")
      << MatchedIfReturn;

  const auto *MatchedDirectReturn = Result.Nodes.getNodeAs<ReturnStmt>("direct");
  if(MatchedDirectReturn)
    diag(MatchedDirectReturn->getReturnLoc(), "found as direct return statement");
  
  
}

} // namespace misc
} // namespace tidy
} // namespace clang
