#include <iostream>
#include <stdio.h>
#include <cstring>
#include <optional>


namespace
{
  // https://rules.sonarsource.com/cpp/RSPEC-5798
  void f()
  {
    char str[] = "almost every programmer should know memset!";
    memset (str,'-',6);
    puts (str);  
  }

  // https://rules.sonarsource.com/cpp/RSPEC-6427
  void g(std::optional<int> &val, bool b) {
      if (b) {
        *val = 314; // Noncompliant, will throw if the optional was previously empty
      } else {
        val.value() = 42; // Noncompliant, will throw if the optional was previously empty
      }
  }

}

int main(int argc, char* argv[]) {
  using namespace std;
  
  f();
  g();

  int num = argc - 1;

  if (num == 0) {
    cout << "No arguments provided\n";
  } else if (num == 0) { // intentional mistake
    cout << "1 argument provided\n";
  } else if (num == 2) {
    cout << "2 arguments provided\n";
  } else {
    cout << num << " arguments provided\n";
  }
  if (argv != 0) {
    cout << "argv not null\n";; // intentional extra-semicolon
  }
  if (argv == nullptr) {
    return **argv; // intentional nullptr dereference
  }

  return 0;
}
