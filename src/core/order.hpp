//
// Created by aamir on 01/04/2026.
//

#pragma once

#include "common/types.hpp"
#include <cstdint>

namespace velocity {
  enum class Side : uint8_t {
    Bid=0,
    Ask=1,
  };

  enum class OrderType : uint8_t {
    Limit=0,
    Market=1,
  };

  enum class OrderStatus : uint8_t {
    New             = 0,
    PartiallyFilled = 1,
    Filled          = 2,
    Cancelled       = 3,
    Rejected        = 4,
  };

  struct Order {
    RawPrice    price;
    Quantity    quantity;
    Quantity    filled_qty;
    OrderId     order_id;
    SymbolId    symbol_id;
    OrderType   type;
    Side        side;
    OrderStatus status;
    uint8_t     _pad[1];
    uint64_t    timestamp_ns;

    [[nodiscard]] Quantity leaves_qty() const noexcept {
      return quantity-filled_qty;
    }

    [[nodiscard]] bool is_fully_filled() const noexcept {
		return filled_qty>=quantity;
	}

	[[nodiscard]] bool is_active() const noexcept {
        return status==OrderStatus::New || status==OrderStatus::PartiallyFilled;
    }
  };

static_assert(sizeof(Order) == 48, "Order struct size changed");
static_assert(alignof(Order) == 8, "Order alignment expected");
} // namespace velocity
