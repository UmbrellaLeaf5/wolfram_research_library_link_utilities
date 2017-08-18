/*
 An example that demonstrates catching errors when calling 
 a Wolfram Library function from Mathematica.
 */

#include "setjmp.h"
#include "stdio.h"  /* for printf */
#include "string.h" /* for memset */
#include "WolframLibrary.h"
#include "MArgumentManager.h"

using namespace LibraryLinkUtils;

EXTERN_C DLLEXPORT mint WolframLibrary_getVersion() {
	return WolframLibraryVersion;
}

EXTERN_C DLLEXPORT int WolframLibrary_initialize(WolframLibraryData libData) {
	MArgumentManager::setLibraryData(libData);
	return 0;
}

EXTERN_C DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData) {

	return;
}

EXTERN_C DLLEXPORT int errordemo1(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	auto err = LLErrorCode::NoError;
	try {
		MArgumentManager mngr(Argc, Args, Res);
		auto T0 = mngr.getTensor<double>(0);
		auto I0 = mngr.getInteger<mint>(1);

		mngr.setReal(T0[I0 - 1]);
	}
	catch (LibraryLinkError<LLErrorCode>& e) {
		err = e.which();
	}
	return static_cast<int>(err);
}

EXTERN_C DLLEXPORT int errordemo2(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	auto err = LLErrorCode::NoError;
	MArgumentManager mngr(Argc, Args, Res);
	try {
		auto T0 = mngr.getTensor<double>(0);
		auto I0 = mngr.getInteger<mint>(1);

		mngr.setReal(T0[I0 - 1]);
	}
	catch (LibraryLinkError<LLErrorCode>& e) {
		std::cout << e.what() << std::endl;
		mngr.setReal(0.);
	}
	return static_cast<int>(err);
}

EXTERN_C DLLEXPORT int errordemo3(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	auto err = LLErrorCode::NoError;
	try {
		MArgumentManager mngr(Argc, Args, Res);
		auto T0 = mngr.getTensor<double>(0);
		auto I0 = mngr.getInteger<mint>(1);

		mngr.setReal(T0[I0 - 1]);

		mngr.setReal(T0[I0 - 1]);
	}
	catch (LibraryLinkError<LLErrorCode>& e) {
		std::cout << e.what() << std::endl;
		err = e.which();
	}
	return static_cast<int>(err);
}

EXTERN_C DLLEXPORT int errordemo4(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	auto err = LLErrorCode::NoError;
	try {
		MArgumentManager mngr(Argc, Args, Res);
		auto T0 = mngr.getTensor<double>(0);
		auto I0 = mngr.getInteger<mint>(1);

		mngr.setReal(0.);

		if (T0.rank() != 1) {
			libData->Message("rankerror");
			throw LibraryLinkError<LLErrorCode>(LLErrorCode::RankError);
		}

		auto& dims = T0.dimensions();
		if ((I0 < 1) || (I0 > dims[0])) {
			libData->Message("outofrange");
			throw LibraryLinkError<LLErrorCode>(LLErrorCode::DimensionsError);
		}

		mngr.setReal(T0[I0 - 1]);
	}
	catch (LibraryLinkError<LLErrorCode>& e) {
		err = e.which();
	}
	return static_cast<int>(err);
}

EXTERN_C DLLEXPORT int errordemo5(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	MTensor T0, Tres;
	mint n, type, rank, *dims;
	int err = LIBRARY_NO_ERROR;

	type = MArgument_getInteger(Args[0]);
	rank = MArgument_getInteger(Args[1]);
	T0 = MArgument_getMTensor(Args[2]);

	dims = libData->MTensor_getIntegerData(T0);

	err = libData->MTensor_new(type, rank, dims, &Tres);
	if (err)
		return err;
	MArgument_setMTensor(Res, Tres);

	n = libData->MTensor_getFlattenedLength(Tres);
	switch (type) {
		case MType_Integer:
			memset(libData->MTensor_getIntegerData(Tres), 0, n * sizeof(mint));
			break;
		case MType_Real:
			memset(libData->MTensor_getRealData(Tres), 0, n * sizeof(mreal));
			break;
		default:
			break;
	}
	return 0;
}

EXTERN_C DLLEXPORT int errordemo6(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	auto err = LLErrorCode::NoError;
	try {
		MArgumentManager mngr(Argc, Args, Res);
		auto n = mngr.getInteger<mint>(0);
		auto T = mngr.getTensor<mint>(1);

		mint i {};
		for (; i < n; i++) {
			if (libData->AbortQ()) {
				libData->Message("aborted");
				break;
			}
		}
		T[0] = i;
	}
	catch (LibraryLinkError<LLErrorCode>& e) {
		err = e.which();
	}
	catch (std::exception& e) {
		err = LLErrorCode::FunctionError;
	}
	return static_cast<int>(err);
}

EXTERN_C DLLEXPORT int errorTest_Return(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	mint retVal;

	retVal = MArgument_getInteger(Args[0]);

	return (int) retVal;
}
