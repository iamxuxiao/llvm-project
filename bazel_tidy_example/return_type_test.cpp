
class A{};
void bar(int x){};

A* foo(int x,double b) {
  return new A;
}

void caller(int a){
  int a1 = 10;
  double b = 20.0;
  A* result = foo(a1,b);
  if(result){
    int bb =20;
  }
 
}


int main(int argc, char** argv) {
  return 0;
}
