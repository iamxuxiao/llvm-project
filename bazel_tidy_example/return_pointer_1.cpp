class A{};


A* func_1(){
  int a = 10;
  if( a > 0){
    return nullptr;
  }
  return new A;
}

A* func_2(int a, double b){
  return new A;
}


