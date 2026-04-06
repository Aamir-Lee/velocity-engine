//
// Created by aamir on 06/04/2026.
//

#include "core/order.hpp"
#include <iostream>

int main() {
  velocity::Order order{};
  order.quantity   = 100;
  order.filled_qty = 40;

  std::cout << order.leaves_qty() << '\n';
  return 0;
}