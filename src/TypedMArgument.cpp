/**
 * @file	TypedMArgument.cpp
 * @author	Rafal Chojna <rafalc@wolfram.com>
 * @date	April 28, 2020
 * @brief
 */

#include <LLU/TypedMArgument.h>

#include <LLU/Containers/Generic/DataStore.hpp>
#include <LLU/Containers/Generic/Image.hpp>
#include <LLU/Containers/Generic/NumericArray.hpp>
#include <LLU/Containers/Generic/Tensor.hpp>

namespace LLU {

	TypedArgument fromMArgument(MArgument m, MArgumentType t) {
		switch (t) {
			case MArgumentType::MArgument: break;
			case MArgumentType::Boolean: return static_cast<bool>(MArgument_getBoolean(m));
			case MArgumentType::Integer: return MArgument_getInteger(m);
			case MArgumentType::Real: return MArgument_getReal(m);
			case MArgumentType::Complex: {
				auto* mc = MArgument_getComplexAddress(m);
				return std::complex<double> {mc->ri[0], mc->ri[1]};
			}
			case MArgumentType::Tensor: return GenericTensor {MArgument_getMTensor(m), Ownership::LibraryLink};
			case MArgumentType::SparseArray: return MArgument_getMSparseArray(m);
			case MArgumentType::NumericArray: return GenericNumericArray {MArgument_getMNumericArray(m), Ownership::LibraryLink};
			case MArgumentType::Image: return GenericImage {MArgument_getMImage(m), Ownership::LibraryLink};
			case MArgumentType::UTF8String: return std::string_view {MArgument_getUTF8String(m)};
			case MArgumentType::DataStore: return GenericDataList {MArgument_getDataStore(m), Ownership::LibraryLink};
		}
		ErrorManager::throwException(ErrorName::FunctionError); //TODO add specific error
	}

	void toMArgument(const TypedArgument& tma, MArgument& res) {
		switch (static_cast<MArgumentType>(tma.index())) {
			case MArgumentType::MArgument: ErrorManager::throwException(ErrorName::FunctionError); //TODO add specific error;
			case MArgumentType::Boolean: MArgument_setBoolean(res, std::get<bool>(tma)); break;
			case MArgumentType::Integer: MArgument_setInteger(res, std::get<mint>(tma)); break;
			case MArgumentType::Real: MArgument_setReal(res, std::get<double>(tma)); break;
			case MArgumentType::Complex: {
				auto c = std::get<std::complex<double>>(tma);
				mcomplex mc {c.real(), c.imag()};
				MArgument_setComplex(res, mc);
				break;
			}
			case MArgumentType::Tensor: MArgument_setMTensor(res, std::get<GenericTensor>(tma).abandonContainer()); break;
			case MArgumentType::SparseArray: MArgument_setMSparseArray(res, std::get<MSparseArray>(tma)); break;
			case MArgumentType::NumericArray: MArgument_setMNumericArray(res, std::get<GenericNumericArray>(tma).abandonContainer()); break;
			case MArgumentType::Image: MArgument_setMImage(res, std::get<GenericImage>(tma).abandonContainer()); break;
			case MArgumentType::UTF8String: MArgument_setUTF8String(res, const_cast<char*>(std::get<std::string_view>(tma).data())); break;
			case MArgumentType::DataStore: MArgument_setDataStore(res, std::get<GenericDataList>(tma).abandonContainer()); break;
		}
	}
}