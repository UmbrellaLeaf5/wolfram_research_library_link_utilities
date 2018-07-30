/** 
 * @file	Utilities.hpp
 * @author	Rafal Chojna <rafalc@wolfram.com>
 * @date	8/07/2017
 *
 * @brief	Short but generally useful functions
 *
 */
#ifndef LLUTILS_UTILITIES_H_
#define LLUTILS_UTILITIES_H_

#include <complex>
#include <cstdint>
#include <type_traits>

#include "WolframLibrary.h"
#include "WolframRawArrayLibrary.h"


namespace LibraryLinkUtils {

	/**
	 * @brief 	Utility type that strips any given type from reference and cv qualifiers
	 * @tparam	T - any type
	 */
	template<typename T>
	using remove_cv_ref = std::remove_cv_t<std::remove_reference_t<T>>;

	/**
	 * @brief 	Utility type that is valid only if B is not A and not a subclass of A
	 * @tparam	A - any type
	 * @tparam	B - any type, will be stripped of reference and cv-qualifiers before comparing with A
	 */
	template<typename A, typename B>
	using disable_if_same_or_derived = typename std::enable_if_t<!std::is_same<A, B>::value && !std::is_base_of<A, remove_cv_ref<B>>::value>;

	/**
	 * @brief 	Utility type that is valid only if B is A or a subclass of A
	 * @tparam	A - any type
	 * @tparam	B - any type, will be stripped of reference and cv-qualifiers before comparing with A
	 */
	template<typename A, typename B>
	using enable_if_same_or_derived = typename std::enable_if_t<std::is_same<A, B>::value || std::is_base_of<A, remove_cv_ref<B>>::value>;

	/**
	 * @brief 	Utility type that checks if given type can be treated as input iterator
	 * @tparam	Iterator - iterator type
	 */
	template<typename Iterator>
	using enable_if_input_iterator = enable_if_same_or_derived<std::input_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>;


	/**
	 * @brief 	Utility type that checks if given container type has elements that are integers (and therefore can be used as Tensor or RawArray dimensions)
	 * @tparam	Container - container type
	 */
	template<typename Container>
	using enable_if_integral_elements = typename std::enable_if_t<std::is_integral<typename std::remove_reference_t<Container>::value_type>::value>;

	/**
	 * @brief 	Dummy function called on otherwise unused parameters to eliminate compiler warnings.
	 * @tparam 	Ts - variadic template parameter, any number of arbitrary types
	 */
	template<typename... Ts>
	void Unused(Ts&&...) {}


	/// Utility structure that matches an MRawArray data type with corresponding C++ type
	template<rawarray_t>
	struct RawArrayFromEnum;

	template<> struct RawArrayFromEnum<MRawArray_Type_Bit8> {
		using type = std::int8_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Ubit8> {
		using type = std::uint8_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Bit16> {
		using type = std::int16_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Ubit16> {
		using type = std::uint16_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Bit32> {
		using type = std::int32_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Ubit32> {
		using type = std::uint32_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Bit64> {
		using type = std::int64_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Ubit64> {
		using type = std::uint64_t;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Real32> {
		using type = float;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Real64> {
		using type = double;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Float_Complex> {
		using type = std::complex<float>;
	};
	template<> struct RawArrayFromEnum<MRawArray_Type_Double_Complex> {
		using type = std::complex<double>;
	};

	template<rawarray_t rat>
	using RawArrayTypeFromEnum = typename RawArrayFromEnum<rat>::type;

	/**
	 * @brief Calls an overload of \c f() with template type matching an MRawArray type \c rat
	 * @param raType - MRawArray type
	 * @param f - any callable structure
	 * @param args - additional arguments for f::operator()
	 * @warning This function is a prototype, has not been tested yet and is likely to change in the future.
	 */
	template<typename Callable, typename ... Args>
	void applyToRawArray(rawarray_t raType, Callable&& f, Args&&... args) {
		switch (raType) {
			case MRawArray_Type_Bit8:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Bit8>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Ubit8:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Ubit8>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Bit16:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Bit16>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Ubit16:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Ubit16>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Bit32:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Bit32>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Ubit32:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Ubit32>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Bit64:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Bit64>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Ubit64:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Ubit64>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Real32:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Real32>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Real64:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Real64>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Float_Complex:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Float_Complex>>(std::forward<Args>(args)...);
				break;
			case MRawArray_Type_Double_Complex:
				std::forward<Callable>(f).template operator()<RawArrayTypeFromEnum<MRawArray_Type_Double_Complex>>(std::forward<Args>(args)...);
				break;
			default:
				return;
		}
	}

} /* namespace LibraryLinkUtils */

#endif /* LLUTILS_UTILITIES_H_ */