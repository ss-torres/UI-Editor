#ifndef ARITHMETIC_UTIL_H
#define ARITHMETIC_UTIL_H

//#include <stdexcept>
//
//// 添加 scalar numeric conversion function，实现源自 C++ programming language(4th)
//// 用来防止使用static转换的时候，值发生改变
//template <class Source, typename Target>
//inline Target narrow_cast(Source v)
//{
//	auto r = static_cast<Target>(v);
//	if (static_cast<Source>(r) != v)
//		throw std::runtime_error("narrow_cast<>() failed");
//	return r;
//}

#include <type_traits>
#include <stdexcept>
#include <limits>

//// 添加 scalar numeric conversion function，实现源自 C++ programming language(4th)
//// 用来防止使用static转换的时候，值发生改变
//template <typename Target, typename Source,
//	typename = std::enable_if_t<!std::is_same_v<std::remove_reference_t<std::remove_const_t<Target>>,
//	std::remove_reference_t<std::remove_const_t<Source>>> && !std::is_reference_v<Target>, int>>
//	inline Target narrow_cast(Source v)
//{
//	// using Target_U = std::remove_reference_t<Target>;
//	// using Source_U = std::remove_reference_t<Source>;
//	auto r = static_cast<Target>(v);
//	if (static_cast<Source>(r) != v)
//		throw std::runtime_error("narrow_cast<>() failed");
//	return r;
//}
//
//template <typename Target, typename Source,
//	typename = std::enable_if_t<std::is_same_v<std::remove_reference_t<std::remove_const_t<Target>>,
//	std::remove_reference_t<std::remove_const_t<Source>>> && !std::is_reference_v<Target>, int>>
//	inline constexpr std::remove_reference_t<Source> narrow_cast(Source v)
//{
//	return std::remove_reference_t<Source>(v);
//}

// there is no implicit conversion from Source to Target
template <typename Target, typename Source,
	typename = std::enable_if_t<!std::is_reference_v<Target> &&
	!std::is_same_v<std::common_type_t<std::decay_t<Target>, std::decay_t<Source>>, std::decay_t<Target>>, int>>
	inline Target narrow_cast(Source v)
{
	static_assert(std::is_arithmetic<Source>::value, "The parameter of narrow_cast should be arithmetic");
	static_assert(std::is_arithmetic<Target>::value, "The return value of narrow_cast should be arithmetic");

	// using Target_U = std::remove_reference_t<Target>;
	// using Source_U = std::remove_reference_t<Source>;

	auto r = static_cast<Target>(v);
	if (static_cast<Source>(r) != v)
		throw std::runtime_error("narrow_cast<>() failed");
	return r;
}

// there is implicit conversion from Source to Target
template <typename Target, typename Source,
	typename = std::enable_if_t<!std::is_reference_v<Target> &&
	std::is_same_v<std::common_type_t<std::decay_t<Target>, std::decay_t<Source>>, std::decay_t<Target>>, int>>
	inline constexpr std::remove_reference_t<Source> narrow_cast(Source v)
{
	static_assert(std::is_arithmetic<Source>::value, "The parameter of narrow_cast should be arithmetic");
	static_assert(std::is_arithmetic<Target>::value, "The return value of narrow_cast should be arithmetic");

	return std::remove_reference_t<Source>(v);
}

#endif	// ARITHMETIC_UTIL_H
