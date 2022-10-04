#include <iostream>
class A{};

A* UpperStreamFunction(bool flag){
  if(flag){
    return new A;
  }else{
    return nullptr;
  }
}

void DownstreamConsumer(){
  const auto result_maybe = UpperStreamFunction(true);

  if (false){
    std::cout << " Empty Case\n";
  }
  
  if (result_maybe){
    std::cout << " Empty Case\n";
  }
  if (!result_maybe){
    std::cout << " Empty Case\n";
  }
  //TODO match another call?
  const auto result_maybe_2 = UpperStreamFunction(false);
  if (!result_maybe_2){
    std::cout << " Empty Case\n";
  }
  
  std::cout<<" Happy Case\n";
}

