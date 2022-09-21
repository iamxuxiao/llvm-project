class A{};

A* ReturnTest(int a){
  if(a>0)
    return new A;
  return nullptr;
}
