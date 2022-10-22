#include <iostream>
class Lane{};

Lane* GetMapLaneById(const int Id){
  if(Id<0){
    return nullptr;
  }else{        
    return new Lane;
  }
}

void MapFusionConsumer(){

  const auto lane_ptr_maybe = GetMapLaneById(true);

  if (!lane_ptr_maybe){
    std::cout << " Lane Creation Failed\n";
  }

  
  const auto another_lane_ptr_maybe = GetMapLaneById(false);
  if (!another_lane_ptr_maybe){
    std::cout << " Lane Creation Failed\n";
  }

  // DONE Checking, do rest of the work

}

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



// What is not covered
