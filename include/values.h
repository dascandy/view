#pragma once

#include <utility>

template <typename Container>
struct values_view {
    values_view(Container& c)
        : it_(std::begin(c))
        , end_(std::end(c))
    {
    }
    struct sentinel {};
    values_view& begin() {
        return *this;
    }
    sentinel end() {
        return sentinel();
    }
    decltype(std::begin(::std::declval<Container&>())) it_;
    decltype(std::end(::std::declval<Container&>())) end_;
    values_view<Container>& operator++() {
        ++it_;
        return *this;
    }
    auto &operator*() {
        return it_->second;
    }
    bool operator!=(const sentinel&) {
        return it_ != end_;
    }
    bool operator==(const sentinel&) {
        return it_ == end_;
    }
};

template <typename C>
auto values(C& c) {
    return values_view<C> {c};
}

