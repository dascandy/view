#pragma once

#include <utility>

template <typename Container, typename Pred>
struct filter_view {
    filter_view(Container& c, Pred&& p)
        : it_(std::begin(c))
        , end_(std::end(c))
        , pred_(std::move(p))
    {
        while (it_ != end_ && !pred_(*it_)) ++it_;
    }
    struct sentinel {};
    filter_view& begin() {
        return *this;
    }
    sentinel end() {
        return sentinel();
    }
    decltype(std::begin(::std::declval<Container&>())) it_;
    decltype(std::end(::std::declval<Container&>())) end_;
    Pred pred_;
    filter_view<Container, Pred>& operator++() {
        do {
            ++it_;
        } while (it_ != end_ && !pred_(*it_));
        return *this;
    }
    decltype(*::std::begin(::std::declval<Container&>())) &operator*() {
        return *it_;
    }
    bool operator!=(const sentinel& oi) {
        return it_ != end_;
    }
    bool operator==(const sentinel& oi) {
        return it_ == end_;
    }
};

template <typename C, typename P>
auto filter(C& c, P&& p) {
    return filter_view<C, P> {c, std::move(p)};
}


