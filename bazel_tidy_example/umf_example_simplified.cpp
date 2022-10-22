#include <optional>

struct Lane{};

Lane* GetMapLaneById(const int Id){
  if(Id<0){
    return nullptr;
  }else{        
    return new Lane;
  }
}

std::optional<Lane> GetMapLaneByIdImproved(const int Id){
  if(Id<0){
    return std::nullopt;
  }else{        
    return std::optional<Lane>();
  }
}


void MapFusionWork(){

  const auto lane_ptr = GetMapLaneById(10);
  if (lane_ptr){ // warn here 
    // nullcheck , maybe early exit 
  }

  
  const auto another_lane_ptr = GetMapLaneById(-10);
  if (another_lane_ptr == nullptr){ // no warn here
    // nullcheck , maybe early exit 
  }


  const auto lane_ptr_maybe = GetMapLaneByIdImproved(10);
  if (lane_ptr_maybe){  // warn here 
    // nullcheck , maybe early exit 
  }
//
//  
  const auto another_lane_ptr_maybe = GetMapLaneByIdImproved(-999);
  if (another_lane_ptr_maybe == std::nullopt){
    // nullcheck , maybe early exit 
  }
//
  
  // DONE Checking, do rest of the work
}
// What is not covered
