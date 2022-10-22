struct Lane{};

Lane* GetMapLaneById(const int Id){
  if(Id<0){
    return nullptr;
  }else{        
    return new Lane;
  }
}

void MapFusionWork(){

  const auto lane_ptr_maybe = GetMapLaneById(10);
  if (lane_ptr_maybe){
    // nullcheck , maybe early exit 
  }

  
  const auto another_lane_ptr_maybe = GetMapLaneById(-10);
  if (another_lane_ptr_maybe == nullptr){
    // nullcheck , maybe early exit 
  }

  // DONE Checking, do rest of the work
}
// What is not covered
