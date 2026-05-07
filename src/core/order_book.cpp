//
// Created by aamir on 07/05/2026.
//

#include "core/order_book.hpp"
#include <cassert>

namespace velocity {
    OrderBook::OrderBook(SymbolId symbol_id) noexcept
        : symbol_id_(symbol_id) {}

    RawPrice OrderBook::best_bid() const noexcept {
        if (bids_.empty()) return kInvalidPrice;
        return bids_.begin()->first;
    }

    RawPrice OrderBook::best_ask() const noexcept {
        if (asks_.empty()) return kInvalidPrice;
        return asks_.begin()->first;
    }

    bool OrderBook::empty() const noexcept {
        return bids_.empty() && asks_.empty();
    }

    std::size_t OrderBook::order_count() const noexcept {
        return orders_index_.size();
    }

    OrderBook::AddResult OrderBook::add_order(Order& order) noexcept {

        if (order.quantity == 0) return AddResult::Rejected;
        if (order.order_id == kInvalidOrderId) return AddResult::Rejected;

        if (order.side == Side::Bid) {
            match_against_asks(order);
        } else {
            match_against_bids(order);
        }

        if (order.is_fully_filled()) {
            return AddResult::FilledFully;
        }

        // Rest the remaining quantity in the book
        if (order.side == Side::Bid) {
            auto& level = bids_[order.price];
            auto  it    = level.insert(level.end(), &order);
            orders_index_.emplace(order.order_id,
                OrderLocation{it, order.price, Side::Bid});
        } else {
            auto& level = asks_[order.price];
            auto  it    = level.insert(level.end(), &order);
            orders_index_.emplace(order.order_id,
                OrderLocation{it, order.price, Side::Ask});
        }

        if (order.filled_qty > 0) return AddResult::FilledPartially;
        return AddResult::Accepted;
    }

    OrderBook::CancelResult OrderBook::cancel_order(OrderId order_id) noexcept {
        auto loc_it = orders_index_.find(order_id);
        if (loc_it == orders_index_.end()) return CancelResult::NotFound;

        OrderLocation& loc = loc_it->second;

        if (loc.side == Side::Bid) {
            auto& level = bids_[loc.price];
            level.erase(loc.iter);
            remove_empty_level(Side::Bid, loc.price);
        } else {
            auto& level = asks_[loc.price];
            level.erase(loc.iter);
            remove_empty_level(Side::Ask, loc.price);
        }

        orders_index_.erase(loc_it);
        return CancelResult::Cancelled;
    }

    void OrderBook::match_against_asks(Order& bid_order) noexcept {
        while (!asks_.empty() && !bid_order.is_fully_filled()) {
            auto& [ask_price, ask_level] = *asks_.begin();

            if (ask_price > bid_order.price) break;

            while (!ask_level.empty() && !bid_order.is_fully_filled()) {
                Order* passive = ask_level.front();

                Quantity fill_qty = std::min(bid_order.leaves_qty(), passive->leaves_qty());

                bid_order.filled_qty += fill_qty;
                passive->filled_qty  += fill_qty;

                if (passive->is_fully_filled()) {
                    orders_index_.erase(passive->order_id);
                    ask_level.pop_front();
                }
            }

            remove_empty_level(Side::Ask, ask_price);
        }
    }

    void OrderBook::match_against_bids(Order& ask_order) noexcept {
        while (!bids_.empty() && !ask_order.is_fully_filled()) {
            auto& [bid_price, bid_level] = *bids_.begin();

            if (bid_price < ask_order.price) break;

            while (!bid_level.empty() && !ask_order.is_fully_filled()) {
                Order* passive = bid_level.front();

                Quantity fill_qty = std::min(ask_order.leaves_qty(), passive->leaves_qty());

                ask_order.filled_qty += fill_qty;
                passive->filled_qty  += fill_qty;

                if (passive->is_fully_filled()) {
                    orders_index_.erase(passive->order_id);
                    bid_level.pop_front();
                }
            }

            remove_empty_level(Side::Bid, bid_price);
        }
    }

    void OrderBook::remove_empty_level(Side side, RawPrice price) noexcept {
        if (side == Side::Bid) {
            auto it = bids_.find(price);
            if (it != bids_.end() && it->second.empty()) {
                bids_.erase(it);
            }
        } else {
            auto it = asks_.find(price);
            if (it != asks_.end() && it->second.empty()) {
                asks_.erase(it);
            }
        }
    }

}