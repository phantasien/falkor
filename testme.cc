#include <iostream>
#include <bastian.h>

BASTIAN_FUNC(Log) {
  std::cout << func->GetArgument(0)->StringValue() << std::endl;
}

BASTIAN_OBJ(Console) {
  obj->Export("log", Log);
}

BASTIAN_OBJ(Global) {
  obj->Export("console", Console);
}

int main(int argc, char* argv[]) {
  bastian::Engine::New(Global)->Run("console.log('This is Hello World !')");
  return 0;
}