  class X {};  // Matches X, because X::X is a class of name X inside X.
  class Y { class X {}; };
  class Z { class Y { class X {}; }; };

  class Z { class Y class D {{ class X {}; };}; };
