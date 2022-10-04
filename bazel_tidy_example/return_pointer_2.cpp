class A{};


A* func_3(){
  int a = 10;
  if( a > 0){
    return nullptr;
  }
  return new A;
}

A* func_4(int a, double b){
  return new A;
}


