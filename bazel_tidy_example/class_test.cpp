struct C{
  int from_c;
};

struct B: public C{
  int b_owns;
};



namespace nm{
  class A{
  public:
    A(int a){}
    int a;
    double b;
  private:
    int method_1(int a){
      return 1;
    }
    int method_2(){
      return 2;
    }
    
  };
}
