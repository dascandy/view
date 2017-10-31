#pragma once

#include <utility>
#include <string>
#include <string_view>

template <typename StrType>
struct view_for;
template <>
struct view_for<std::string> { using type = std::string_view; };
template <typename StrType>
using view_for_t = view_for<StrType>::type;

template <typename Str>
struct split_view {
    split_view(const Str& str, const Str& chars)
        : it_(std::begin(str))
        , end_cur_(it_)
        , end_(std::end(str))
        , chars_(chars)
    {
        while (end_cur_ != end_ && chars_.find(*end_cur) != chars_.end()) ++end_cur_;
    }
    struct sentinel {};
    split_view& begin() {
        return *this;
    }
    sentinel end() {
        return sentinel();
    }
    decltype(std::begin(::std::declval<Str&>())) it_;
    decltype(std::begin(::std::declval<Str&>())) end_cur_;
    decltype(std::end(::std::declval<Str&>())) end_;
    const Str& chars_;
    split_view& operator++() {
        it_ = end_cur_;
        while (it_ != end_ && chars_.find(*it_) == chars_.end()) ++it_;
        end_cur_ = it_;
        while (end_cur_ != end_ && chars_.find(*end_cur_) != chars_.end()) ++end_cur_;
        return *this;
    }
    auto operator*() {
        return view_for_t<Str>(it_, end_cur_);
    }
    bool operator!=(const sentinel& oi) {
        return it_ != end_;
    }
    bool operator==(const sentinel& oi) {
        return it_ == end_;
    }
};

template <typename Str>
struct split_view {
    split_view(const Str& str, Str::value_type chr)
        : it_(std::begin(str))
        , end_cur_(it_)
        , end_(std::end(str))
        , chr_(chr)
    {
        while (end_cur_ != end_ && *end_cur != chr_) ++end_cur_;
    }
    struct sentinel {};
    split_view& begin() {
        return *this;
    }
    sentinel end() {
        return sentinel();
    }
    decltype(std::begin(::std::declval<Str&>())) it_;
    decltype(std::begin(::std::declval<Str&>())) end_cur_;
    decltype(std::end(::std::declval<Str&>())) end_;
    Str::value_type chr_;
    split_view& operator++() {
        it_ = end_cur_;
        while (it_ != end_ && chr_ == *it_) ++it_;
        end_cur_ = it_;
        while (end_cur_ != end_ && chr_ != *end_cur_) ++end_cur_;
        return *this;
    }
    auto operator*() {
        return view_for_t<Str>(it_, end_cur_);
    }
    bool operator!=(const sentinel& oi) {
        return it_ != end_;
    }
    bool operator==(const sentinel& oi) {
        return it_ == end_;
    }
};

template <typename C, typename P>
auto split(C& c, const P& p) {
    return split_view<C, P> {c, p};
}


