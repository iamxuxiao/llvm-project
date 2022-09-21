//===--- FilterCheckCheck.cpp - clang-tidy --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FilterCheckCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void FilterCheckCheck::registerMatchers(MatchFinder *Finder) {
  
  Finder->addMatcher(functionDecl().bind("matched_function"), this);
}

void FilterCheckCheck::check(const MatchFinder::MatchResult &Result) {
  
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("matched_function");

  std::string name = MatchedDecl->getName().str();
  std::cout << "Matched Function : " << name << std::endl;
  diag(MatchedDecl->getLocation(), "==> matched function %0 ")
      << MatchedDecl;
}

} // namespace misc
} // namespace tidy
} // namespace clang
