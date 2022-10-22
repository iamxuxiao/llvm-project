//===--- XcheckCompoundMatchCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "XcheckCompoundMatchCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "../utils/OptionsUtils.h"

#include <iostream>
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

// XcheckCompoundMatchCheck::XcheckCompoundMatchCheck(StringRef Name,ClangTidyContext *Context)
//     :ClangTidyCheck(Name, Context),
//      TargetFunctionName(Options.get("TargetFunctionName","")){
//   std::cout<<"Parsed:"<< TargetFunctionName.str() << std::endl;
// }     

XcheckCompoundMatchCheck::XcheckCompoundMatchCheck(StringRef Name,ClangTidyContext *Context)
    :ClangTidyCheck(Name, Context),
     TargetFunctionNames(utils::options::parseStringList(Options.get("TargetFunctionNames",""))){
  for(const auto& TargetFunctionName : TargetFunctionNames){
    std::cout<< "Parsed=" << TargetFunctionName.str()<<std::endl;
  }
}     

  
void XcheckCompoundMatchCheck::registerMatchers(MatchFinder *Finder) {
  //TODO use pass in for function name
  for(const auto& TargetFunctionName : TargetFunctionNames){
    // match: auto results = TargetFunctionName()
    // match: auto results_maybe = TargetFunctionNameReturnsOptional()

    // Match the invoke
    auto invoke_expr =  callExpr(hasDescendant(declRefExpr(to(functionDecl(hasName(TargetFunctionName)))))).bind("invoke_expr");
    // back track to get entire function body    
    auto ancestor_func = functionDecl().bind("function_body");
    // match the auto result = function part
    // so that we can get the name "result" for further analysis
    auto decl_invoke    = declStmt(hasDescendant(varDecl().bind("var_decl")),
                                   hasDescendant(invoke_expr),
                                   hasAncestor(ancestor_func));
    
    Finder->addMatcher(decl_invoke, this);
  }
}

void XcheckCompoundMatchCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *invoke_expr    = Result.Nodes.getNodeAs<CallExpr>("invoke_expr");  
  const auto *var_decl       = Result.Nodes.getNodeAs<VarDecl>("var_decl");  
  const auto *function_body  = Result.Nodes.getNodeAs<FunctionDecl>("function_body");

  // report if we found a function invoke from .tidy_config
  llvm::StringRef var_decl_name = var_decl->getName();
  diag(var_decl->getBeginLoc(), "matched compound stmt, var name [%0]")
    << var_decl_name;

  // Raw AST Traversal to 
  // look for if statement that containts the var_decl_name
  const auto* Body = dyn_cast<CompoundStmt>(function_body->getBody());
  auto  has_direct_usage_of_var = declRefExpr(to(varDecl(hasName(var_decl_name))));
  auto  used_nullopt            = declRefExpr(to(varDecl(hasName("nullopt"))));

  // if we do not found if (!result)  if (result==std::nullopt)
  auto  negate_op = unaryOperator(hasOperatorName("!"));
  int matched_if = 0;
  for(const auto* S : Body->body()) {  
    if(const auto* if_stmt = dyn_cast<IfStmt>(S)){

       const auto cond = if_stmt->getCond();       
       const auto matches_p1 = match(ifStmt(hasDescendant(has_direct_usage_of_var),
                                            hasDescendant(negate_op)),*if_stmt,*Result.Context);      
       // if( matches_p1.size() > 0){
       //   diag(if_stmt->getBeginLoc(), "[!]has if statement contains %0. Matched Size=%1 ")
       //     << var_decl_name
       //     << matches_p1.size() ; 
       // }
       matched_if += matches_p1.size() ;
       const auto matches_p2 = match(ifStmt(hasDescendant(has_direct_usage_of_var),
                                            hasDescendant(binaryOperator()),
                                            hasDescendant(cxxNullPtrLiteralExpr())),*if_stmt,*Result.Context);      
       // if( matches_p2.size() > 0){
       //   diag(if_stmt->getBeginLoc(), "[nullptr] has if statement contains %0. Matched Size=%1 ")
       //     << var_decl_name
       //     << matches_p2.size() ; 
       // }
       matched_if += matches_p2.size() ;

       const auto matches_p3 = match(ifStmt(hasDescendant(has_direct_usage_of_var),
                                            hasDescendant(used_nullopt),                                            
                                            hasDescendant(cxxOperatorCallExpr())),*if_stmt,*Result.Context);      
       

       matched_if += matches_p3.size() ;
       
    }
  }  
  if( matched_if == 0 ){
    diag(var_decl->getBeginLoc(), " Missing null check for ==> %0 ")
      << var_decl_name;
  }

  
  
}

} // namespace misc
} // namespace tidy
} // namespace clang
