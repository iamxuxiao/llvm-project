//===--- XcheckReturnPointerCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "XcheckReturnPointerCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void XcheckReturnPointerCheck::registerMatchers(MatchFinder *Finder) {
  // match usage of func_1
  // get the entire scope of func_2
  // get the val name as result_maybe
  // search for the result_maybe as a name
  // search if there is a result_maybe in the if statement
  auto invoke_func_with_ptr_return =  callExpr(hasDescendant(declRefExpr(to(functionDecl(hasName("UpperStreamFunction")))))).bind("invoke_expr");
  auto declare_and_call = declStmt(hasDescendant(varDecl().bind("var_decl")),hasDescendant(invoke_func_with_ptr_return));
  auto interested_function_body  = functionDecl(hasDescendant(declare_and_call));
  Finder->addMatcher(interested_function_body.bind("function_body"), this);
}

void XcheckReturnPointerCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *function_body = Result.Nodes.getNodeAs<FunctionDecl>("function_body");
  const auto *invoke_expr = Result.Nodes.getNodeAs<CallExpr>("invoke_expr");  
  const auto *var_decl = Result.Nodes.getNodeAs<VarDecl>("var_decl");  
  llvm::StringRef var_decl_name = var_decl->getName();
  
  diag(function_body->getLocation(), "1st matched function  [%0]  Var name [%1]")
    << function_body
    << var_decl_name;

  const auto* Body = dyn_cast<CompoundStmt>(function_body->getBody());
  auto  has_direct_usage_of_var = declRefExpr(to(varDecl(hasName(var_decl_name))));
  for(const auto* S : Body->body()) {  
    if(const auto* if_stmt = dyn_cast<IfStmt>(S)){
      //std::cout<<"[debug] found if statement !\n";
      const auto cond = if_stmt->getCond();
      const auto matches = match(ifStmt(hasDescendant(has_direct_usage_of_var)),*if_stmt,*Result.Context);      
      if( matches.size() > 0){
        diag(if_stmt->getBeginLoc(), "has if statement contains %0. Matched Size=%1 ")
          << var_decl_name
          << matches.size() ; 
      }
    }
  }  
}

} // namespace misc
} // namespace tidy
} // namespace clang
