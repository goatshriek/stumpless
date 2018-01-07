#include <iostream>
#include "test/function/utf8.hpp"

void TestUTF8Compliance(const char *str){
  // strip off the BOM if it exists
  if(*str == '\xef' && *(str+1) == '\xbb' && *(str+2) == '\xbf'){
    str += 3;
  }

  for(const char *c=str; *c != '\0'; c++){
    if((*c & 0x80) == 0){
      continue;
    }

    std::cout << *c;
  }

  std::cout << '\n';
}
