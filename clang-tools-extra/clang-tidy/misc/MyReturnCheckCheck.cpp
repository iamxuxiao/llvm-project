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
    functionDecl(has(compoundStmt(has(returnStmt(has(implicitCastExpr(has(cxxNullPtrLiteralExpr())))).bind("direct_return_stmt"))))).bind("owner_function");

  Finder->addMatcher(direct_return_nullptr_pattern, this);


  auto sub_node_return = functionDecl(hasDescendant(returnStmt(has(implicitCastExpr(has(cxxNullPtrLiteralExpr().bind("null_expr"))))))).bind("top_func");    
  Finder->addMatcher(sub_node_return, this);


  
}

  

void MyReturnCheckCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *MatchedIfReturn = Result.Nodes.getNodeAs<FunctionDecl>("if_return");
  if(MatchedIfReturn)
    diag(MatchedIfReturn->getLocation(), "found %0 as if return")
      << MatchedIfReturn;

  const auto *MatchedDirectReturn = Result.Nodes.getNodeAs<ReturnStmt>("direct_return_stmt");
  const auto *function = Result.Nodes.getNodeAs<FunctionDecl>("owner_function");
  
  if(MatchedDirectReturn && function)
    diag(MatchedDirectReturn->getReturnLoc(), "found as direct return statement in function %0")
    << function->getName()  ;


  const auto *func = Result.Nodes.getNodeAs<FunctionDecl>("top_func");
  const auto *expr = Result.Nodes.getNodeAs<CXXNullPtrLiteralExpr>("null_expr");  
  if(func && expr){
    diag(expr->getLocation(),"Matched top level function");
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
