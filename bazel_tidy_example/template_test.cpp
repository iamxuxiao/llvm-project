class A{};

template<typename T>
T TemplateFunction(T obj){
  T obj_out = obj;
  return obj_out;
}


A* UserFunction(const int a){
  return TemplateFunction(A());
}


