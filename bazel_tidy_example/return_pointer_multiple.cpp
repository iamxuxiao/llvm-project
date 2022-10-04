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
  const auto result_maybe_1 = UpperStreamFunction(true);
  
  if (result_maybe_1){
    std::cout << " Empty Case\n";
  }

  const auto result_maybe_2 = UpperStreamFunction(false);
  if (!result_maybe_2){
    std::cout << " Empty Case\n";
  }

  if (!result_maybe_1){
    std::cout << " Empty Case\n";
  }

  if (result_maybe_2){
    std::cout << " Empty Case\n";
  }

  const auto result_maybe_3 = UpperStreamFunction(false);  
  if (result_maybe_3 == nullptr){
    std::cout << " Empty Case\n";
  }

  std::cout<<" Happy Case\n";
}

