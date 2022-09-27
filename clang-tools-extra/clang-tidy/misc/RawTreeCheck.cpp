//===--- RawTreeCheck.cpp - clang-tidy ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RawTreeCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include  <iostream> 
using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void RawTreeCheck::registerMatchers(MatchFinder *Finder) {

  Finder->addMatcher(functionDecl().bind("whole_function"), this);
}

void RawTreeCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *FD = Result.Nodes.getNodeAs<FunctionDecl>("whole_function");
  
  if (!FD->getIdentifier() || !FD->getName().startswith("foo"))
    return;
  
  diag(FD->getLocation(), "[matched] %0 ")      << FD;

  const auto* Body = dyn_cast<CompoundStmt>(FD->getBody());   
  for(const auto* S : Body->body()) {
    
    if(const auto* if_stmt = dyn_cast<IfStmt>(S)){
      const auto cond = if_stmt->getCond();
      diag(cond->getExprLoc(), "<== Loc ") ;
      
      const auto matches = match(ifStmt(hasDescendant(cxxNullPtrLiteralExpr())),*if_stmt,*Result.Context);
      std::cout<<"Found Using NullPtr" << matches.size()<<std::endl;
      if( matches.size() > 0){
        diag(if_stmt->getBeginLoc(), "<== using nullptr ") ;

        const auto op    = match(ifStmt(hasDescendant(binaryOperator().bind("binary_op"))),*if_stmt,*Result.Context);
        if( op.size()>0){
          diag(if_stmt->getBeginLoc(), "! found binary op")  ;
        }

        const auto lhs    = match(ifStmt(hasDescendant(declRefExpr(to(varDecl(hasName("d")))))),*if_stmt,*Result.Context);
        if( lhs.size()>0){
          diag(if_stmt->getBeginLoc(), "! found declrefexpr with name d")  ;
         }
        
      }
    }              
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
