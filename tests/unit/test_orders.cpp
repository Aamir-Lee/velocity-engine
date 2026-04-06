//
// Created by aamir on 06/04/2026.
//

#include <gtest/gtest.h>
#include "core/order.hpp"

TEST(OrderTest, LeavesQtyOnFreshOrder) {
  velocity::Order order{};
  order.quantity   = 100;
  order.filled_qty = 0;
  EXPECT_EQ(order.leaves_qty(), 100);
}

TEST(OrderTest, FullyFilledDetected) {
  velocity::Order order{};
  order.quantity   = 100;
  order.filled_qty = 100;
  EXPECT_TRUE(order.is_fully_filled());
}

TEST(OrderTest, InvalidOrderIdIsZero) {
  EXPECT_EQ(velocity::kInvalidOrderId, 0);
}