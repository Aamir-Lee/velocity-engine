//
// Created by aamir on 31/03/2026.
//
#pragma once

#include <cstdint>
#include <limits>

namespace velocity {
  using RawPrice=uint64_t;
  using Quantity=uint64_t;
  using OrderId=uint64_t;
  using SymbolId=uint32_t;

  inline constexpr RawPrice kInavlidPrice    = std::numeric_limits<RawPrice>::min();
  inline constexpr Quantity kInavlidQuantity = std::numeric_limits<Quantity>::min();
  inline constexpr OrderId kInavlidOrderId   = std::numeric_limits<OrderId>::min();

  inline constexpr int64_t kPriceScale=10'000;
}