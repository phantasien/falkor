#include <vector>
#include "value.h"

namespace mnc {

class FunctionContext {
  public:
    FunctionContext();

  private:
    std::vector<Value*> arguments_;
    Value* result_; 
};

}