//
// Created by aamir on 05/04/2026.
//

#pragma once

#include "common/types.hpp"
#include <atomic>

class OrderIdGenerator {
public:
  explicit OrderIdGenerator(OrderId start=1) : next_{start} {}

  [[nodiscard]] OrderId next() noexcept {
    return next_++;
  }
private:
  OrderId next_;
};

class AtomicOrderGenerator {
public:
  explicit AtomicOrderGenerator(OrderId start=1) : next_{start} {}

  [[nodiscard]] OrderId next() noexcept{
    return next_.fetch_add(1, std::memory_order_relaxed);
  }
private:
  alignas(64) std::atomic<OrderId> next_;
};