#include <vector>
#include <iostream>
#include <algorithm>

int main() {
  std::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2;

  std::cout << "Before moving" << std::endl;
  std::cout << "Size of v1: " << v1.size() << std::endl;
  std::cout << "Size of v2: " << v2.size() << std::endl;
  std::cout << "Vector size " << v1.size() << std::endl;

  std::cout <<

  // Moving v1 to v2
  v2 = std::move(v1);

  std::cout << "After moving" << std::endl;
  std::cout << "Size of v1: " << v1.size() << std::endl;
  std::cout << "Size of v2: " << v2.size() << std::endl;
}
