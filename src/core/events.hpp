//
// Created by aamir on 05/04/2026.
//

#pragma once

#include "common/types.hpp"
#include "order.hpp"

namespace velocity {

struct TradeEvent {
  OrderId  aggressor_id;
  OrderId  passive_id;
  SymbolId symbol_id;
  RawPrice trade_price;
  Quantity trade_qty;
  uint64_t timestamp_ns;
};

struct OrderAcceptedEvent {
  OrderId  order_id;
  SymbolId symbol_id;
  Side     side;
  RawPrice price;
  Quantity quantity;
  uint64_t timestamp_ns;
};

struct OrderCancelledEvent {
  OrderId  order_id;
  SymbolId symbol_id;
  uint64_t timestamp_ns;
};

struct OrderRejectedEvent {
  OrderId  order_id;
  SymbolId symbol_id;
  uint8_t  reason_code;
  uint64_t timestamp_ns;
};

struct FillEvent {
  OrderId  order_id;
  SymbolId symbol_id;
  RawPrice fill_price;
  Quantity fill_qty;
  Quantity leaves_qty;
  bool     is_fully_filled;
  uint64_t _pad[7];
  uint64_t timestamp_ns;
};
}
