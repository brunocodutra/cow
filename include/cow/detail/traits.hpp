#ifndef COW_DETAIL_TRAITS_HPP
#define COW_DETAIL_TRAITS_HPP

#include <type_traits>

namespace cow::detail {
template <typename to>
void convert(to);

template <typename To,
    typename... From,
    typename = decltype(convert<To>({ std::declval<From>()... })),
    bool disabled = std::is_array_v<To> || std::is_function_v<To>>
std::true_type is_convertible_impl(std::enable_if_t<!disabled, int>);

template <typename, typename...>
std::false_type is_convertible_impl(...);

template <typename To, typename... From>
struct is_convertible : decltype(is_convertible_impl<To, From...>(0)) {
};

template <typename To, typename From>
struct is_convertible<To, From> : std::is_convertible<From, To> {
};

template <typename To, typename... From>
constexpr bool is_convertible_v = is_convertible<To, From...>::value;
}

#endif
