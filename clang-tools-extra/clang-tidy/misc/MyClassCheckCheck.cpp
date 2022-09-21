//===--- MyClassCheckCheck.cpp - clang-tidy -------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MyClassCheckCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void MyClassCheckCheck::registerMatchers(MatchFinder *Finder) {

  auto class_pattern  = cxxRecordDecl(unless(isImplicit())); // otherwise the inserted one will be matched too.
  Finder->addMatcher(class_pattern.bind("top_level_class"), this);
}

void MyClassCheckCheck::check(const MatchFinder::MatchResult &Result) {

  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXRecordDecl>("top_level_class");  
  if(MatchedDecl){
    std::string all_methods = "";
    for(auto method_it = MatchedDecl->method_begin();
        method_it != MatchedDecl->method_end();
        ++method_it){
      StringRef MethodName = (*method_it)->getName();
      all_methods = all_methods + ";" +  MethodName.str();      
    }
    //diag(MatchedDecl->getLocation(), "{'methods': %0} ") << 
    
    std::string all_fields = "";

    for(auto field_it = MatchedDecl->field_begin();
        field_it != MatchedDecl->field_end();
        ++field_it){
      StringRef FieldName = (*field_it)->getName();
      all_fields = all_fields + ";" +  FieldName.str();      
    }
    
    //diag(MatchedDecl->getLocation(), "{'fields': %0} ") 
    

    diag(MatchedDecl->getLocation(), "class Info  Name %0 , Methods %1, Fields %2 ")
       << MatchedDecl->getName()
       << StringRef(all_methods)
       << StringRef(all_fields);      
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
