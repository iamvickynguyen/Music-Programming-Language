#include <iostream>
#include "lexer/lexer.h"
#include <string>

int main() {
  std::string line;
  std::cerr << "musicpp> ";
  getline(std::cin, line);

  lex::TokenArray arr;
  arr = lex::lex_input(line);
  lex::debug_print_token_array(arr);

  return 0;
}
