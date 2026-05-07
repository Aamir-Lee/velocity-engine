//
// Created by aamir on 07/05/2026.
//

#pragma once

#include "common/types.hpp"
#include "core/order.hpp"

#include <map>
#include <list>
#include <unordered_map>
#include <functional>

namespace velocity {

    class OrderBook {
    private:
        using PriceLevel=std::list<Order*>;

        std::map<RawPrice, PriceLevel, std::greater<RawPrice>> bids_;
        std::map<RawPrice, PriceLevel>                    asks_;

        struct OrderLocation {
            PriceLevel::iterator iter;
            RawPrice             price;
            Side                 side;
        };

        std::unordered_map<OrderId, OrderLocation> orders_index_;

        SymbolId symbol_id_;

        void match_against_asks(Order& bid_order) noexcept;
        void match_against_bids(Order& ask_order) noexcept;

        void remove_empty_level(Side side, RawPrice price) noexcept;

    public:
        enum class AddResult : uint8_t {
            Accepted,
            FilledFully,
            FilledPartially,
            Rejected,
        };

        enum class CancelResult : uint8_t {
            Cancelled,
            NotFound,
        };

        explicit OrderBook(SymbolId symbol_id) noexcept;

        [[nodiscard]] AddResult add_order(Order& order) noexcept;

        [[nodiscard]] CancelResult cancel_order(OrderId order_id) noexcept;

        [[nodiscard]] RawPrice best_bid() const noexcept;

        [[nodiscard]] RawPrice best_ask() const noexcept;

        [[nodiscard]] std::size_t order_count() const noexcept;

        [[nodiscard]] bool empty() const noexcept;
    };
}