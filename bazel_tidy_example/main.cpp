#include "helper.hpp"
#include <iostream>


class B{
  void b_member(){}
};

void b_member(){}

void bar(int x) {

}

using AliasB = B;

AliasB* foo(int x,double b, const AliasB& b_instance) {
  bar(x + 1);
  return new B;
}

A* ReturnTest2(int a){
  if(a>0)
    return new A;
  return nullptr;
}


A* ReturnTest1(int a){
  if(a>0){
    return nullptr;
      }else{
    return new A;
  }

}




A* ReturnTest3(int a){
  if(true){
    if(true){
        if(a>0){
          return nullptr;
        }else{
          return 0;
        }       
    }
  }
}




int main(int argc, char** argv) {
  helper();
  return 0;
}
