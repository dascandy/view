#pragma once

#include <utility>

template <typename Container>
struct keys_view {
    keys_view(Container& c)
        : it_(std::begin(c))
        , end_(std::end(c))
    {
    }
    struct sentinel {};
    keys_view& begin() {
        return *this;
    }
    sentinel end() {
        return sentinel();
    }
    decltype(std::begin(::std::declval<Container&>())) it_;
    decltype(std::end(::std::declval<Container&>())) end_;
    keys_view<Container>& operator++() {
        ++it_;
        return *this;
    }
    auto &operator*() {
        return it_->first;
    }
    bool operator!=(const sentinel&) {
        return it_ != end_;
    }
    bool operator==(const sentinel&) {
        return it_ == end_;
    }
};

template <typename C>
auto keys(C& c) {
    return keys_view<C> {c};
}

