#pragma once
#include <utility>

template <typename Lambda>
struct lambda_view {
    lambda_view(Lambda&& l)
    : l(std::move(l))
    {
        value = this->l();
    }
    struct sentinel {};
    lambda_view& begin() {
        return *this;
    }
    sentinel end() {
        return sentinel();
    }
    Lambda l;
    decltype(l()) value;
    lambda_view<Lambda>& operator++() {
        value = l();
        return *this;
    }
    auto &operator*() {
        return value.value();
    }
    bool operator!=(const sentinel&) {
        return value.has_value();
    }
    bool operator==(const sentinel&) {
        return !value.has_value();
    }
};

template <typename L>
auto lambda(L&& l) {
    return lambda_view<L> {std::move(l)};
}

