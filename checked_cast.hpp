#pragma once
#include <limits>
#include <type_traits>

#if __has_cpp_attribute(nodiscard)
#define CHECKED_CAST_NODISCARD [[nodiscard]]
#endif

#if CHECKED_CAST_NAMESPACE
namespace cc{
#endif

// signed int to unsigned int
template <class TTo, class TFrom,
	std::enable_if_t<
	std::is_signed_v<TFrom> && std::is_same_v<std::make_unsigned_t<TFrom>, TTo>
	&& (sizeof(TFrom) == sizeof(TTo)),
	std::nullptr_t > = nullptr>
CHECKED_CAST_NODISCARD
constexpr TTo checked_cast(TFrom from)
{
	if (0 <= from)
		return static_cast<TTo>(from);
	else
		throw std::range_error("integer overflow");
}

// unsigned int to signed int
template <class TTo, class TFrom,
	std::enable_if_t<
	std::is_unsigned_v<TFrom> && std::is_same_v<std::make_signed_t<TFrom>, TTo>
	&& (sizeof(TFrom) == sizeof(TTo)),
	std::nullptr_t > = nullptr>
CHECKED_CAST_NODISCARD
constexpr TTo checked_cast(TFrom from)
{
	if (from <= static_cast<std::make_unsigned_t<TFrom>>(std::numeric_limits<TTo>::max()))
		return static_cast<TTo>(from);
	else
		throw std::range_error("integer overflow");
}

// long to int
template <class TTo, class TFrom,
	std::enable_if_t<
	std::is_signed_v<TFrom> == std::is_signed_v<TTo>
	&& (sizeof(TFrom) > sizeof(TTo)),
	std::nullptr_t > = nullptr>
CHECKED_CAST_NODISCARD
constexpr TTo checked_cast(TFrom from)
{
	if (std::numeric_limits<TTo>::min() <= from && from <= std::numeric_limits<TTo>::max())
		return static_cast<TTo>(from);
	else
		throw std::range_error("integer overflow");
}

// signed long to unsigned int
template <class TTo, class TFrom,
	std::enable_if_t<
	std::is_signed_v<TFrom> && std::is_unsigned_v<TTo>
	&& (sizeof(TFrom) > sizeof(TTo)),
	std::nullptr_t > = nullptr>
CHECKED_CAST_NODISCARD
constexpr TTo checked_cast(TFrom from)
{
	if (0 <= from && from <= static_cast<TFrom>(std::numeric_limits<TTo>::max()))
		return static_cast<TTo>(from);
	else
		throw std::range_error("integer overflow");
}

// unsigned long to signed int
template <class TTo, class TFrom,
	std::enable_if_t<
	std::is_unsigned_v<TFrom> && std::is_signed_v<TTo>
	&& (sizeof(TFrom) > sizeof(TTo)),
	std::nullptr_t > = nullptr>
CHECKED_CAST_NODISCARD
constexpr TTo checked_cast(TFrom from)
{
	if (from <= static_cast<TFrom>(std::numeric_limits<TTo>::max()))
		return static_cast<TTo>(from);
	else
		throw std::range_error("integer overflow");
}

#if CHECKED_CAST_ALLOW_SAME_SIZE
// same size
template <class TTo, class TFrom,
	std::enable_if_t<
	std::is_signed_v<TFrom> == std::is_signed_v<TTo>
	&& (sizeof(TFrom) == sizeof(TTo)),
	std::nullptr_t > = nullptr>
CHECKED_CAST_NODISCARD
constexpr TTo checked_cast(TFrom from)
{
	return from;
}
#endif

#if CHECKED_CAST_NAMESPACE
}
#endif
