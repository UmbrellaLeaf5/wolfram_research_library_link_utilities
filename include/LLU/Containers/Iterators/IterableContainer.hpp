/**
 * @file	IterableContainer.hpp
 * @author	Rafal Chojna <rafalc@wolfram.com>
 * @brief
 */
#ifndef LLU_ITERATORS__ITERABLECONTAINER_HPP
#define LLU_ITERATORS__ITERABLECONTAINER_HPP

#include<vector>

#include "LLU/LibraryData.h"

template<typename T>
class IterableContainer {
public:
	/// Type of elements stored
	using value_type = T;

	/// Iterator type
	using iterator = value_type*;

	/// Constant iterator type
	using const_iterator = const value_type*;

	/// Reference type
	using reference = value_type&;

	/// Constant reference type
	using const_reference = const value_type&;

public:
	/**
	 *	@brief Get raw pointer to underlying data
	 **/
	value_type* data() noexcept {
		return getData();
	}

	/**
	 *	@brief Get raw pointer to const underlying data
	 **/
	const value_type* data() const noexcept {
		return getData();
	}

	/**
	 *	@brief Get iterator at the beginning of underlying data
	 **/
	iterator begin() noexcept {
		return getData();
	}

	/**
	 *	@brief Get constant iterator at the beginning of underlying data
	 **/
	const_iterator begin() const noexcept {
		return getData();
	}

	/**
	 *	@brief Get constant iterator at the beginning of underlying data
	 **/
	const_iterator cbegin() const noexcept {
		return getData();
	}

	/**
	 *	@brief Get iterator after the end of underlying data
	 **/
	iterator end() noexcept {
		return getData() + getSize();
	}

	/**
	 *	@brief Get constant iterator after the end of underlying data
	 **/
	const_iterator end() const noexcept {
		return getData() + getSize();
	}

	/**
	 *	@brief Get constant iterator after the end of underlying data
	 **/
	const_iterator cend() const noexcept {
		return getData() + getSize();
	}

	/**
	 *	@brief 		Get a reference to the data element at given position
	 *	@param[in]	index - position of desired data element
	 **/
	reference operator[](mint index) {
		return *(begin() + index);
	}

	/**
	 *	@brief 		Get a constant reference to the data element at given position
	 *	@param[in]	index - position of desired data element
	 **/
	const_reference operator[](mint index) const {
		return *(cbegin() + index);
	}

	/**
	 * @brief 	Get reference to the first element.
	 * @note 	For empty container the behavior is undefined.
	 */
	reference front() {
		return *begin();
	}

	/**
	 * @brief 	Get constant reference to the first element.
	 * @note 	For empty container the behavior is undefined.
	 */
	const_reference front() const {
		return *cbegin();
	}

	/**
	 * @brief 	Get reference to the last element.
	 * @note 	For empty container the behavior is undefined.
	 */
	reference back() {
		return *(end() - 1);
	}

	/**
	 * @brief 	Get constant reference to the last element.
	 * @note 	For empty container the behavior is undefined.
	 */
	const_reference back() const {
		return *(cend() - 1);
	}

	/**
	 * Copy contents of the data to a std::vector of matching type
	 * @return	std::vector with the copy of the data
	 */
	std::vector<value_type> asVector() const {
		return std::vector<value_type> {cbegin(), cend()};
	}

private:
	/**
	 *	@brief	Get raw pointer to underlying data
	 **/
	virtual T* getData() const noexcept = 0;

	/**
	 *	@brief	Get total number of elements in the underlying data
	 **/
	virtual mint getSize() const noexcept = 0;
};

#endif	  // LLU_ITERATORS__ITERABLECONTAINER_HPP