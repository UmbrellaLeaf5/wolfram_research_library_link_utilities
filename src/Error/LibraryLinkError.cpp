/** 
 * @file	LibraryLinkError.cpp
 * @author	Rafal Chojna <rafalc@wolfram.com>
 *
 * @brief	Contains definitions of ErrorManager members and implementation of interface function sendRegisteredErrors used by PacletFailure framework in LLU
 *
 */
#include "LLU/Error/LibraryLinkError.h"

#include "LLU/Error/Errors.h"
#include "LLU/ML/MLStream.hpp"


namespace LibraryLinkUtils {

	std::string LibraryLinkError::exceptionDetailsSymbol = "LLU`$LastFailureParameters";

	void LibraryLinkError::setExceptionDetailsSymbol(std::string newSymbol) {
		exceptionDetailsSymbol = std::move(newSymbol);
	}

	const std::string& LibraryLinkError::getExceptionDetailsSymbol() {
		return exceptionDetailsSymbol;
	}

	MLINK LibraryLinkError::openLoopback(MLENV env) {
		int err = MLEUNKNOWN;
		auto link = MLLoopbackOpen(env, &err);
		if (err != MLEOK) {
			link = nullptr;
		}
		return link;
	}

	LibraryLinkError::LibraryLinkError(const LibraryLinkError& e) : std::runtime_error(e), errorId(e.errorId), type(e.type), messageTemplate(e.messageTemplate),
												  debugInfo(e.debugInfo) {
		if (e.messageParams) {
			messageParams = openLoopback(MLLinkEnvironment(e.messageParams));
			if (!messageParams) {
				return;
			}
			auto mark = MLCreateMark(e.messageParams);
			MLTransferToEndOfLoopbackLink(messageParams, e.messageParams);
			MLSeekMark(e.messageParams, mark, 0);
			MLDestroyMark(e.messageParams, mark);
		}
	}

	LibraryLinkError::~LibraryLinkError() {
		if (messageParams) {
			MLClose(messageParams);
		}
	}

	int LibraryLinkError::sendParameters(WolframLibraryData libData, const std::string& WLSymbol) const noexcept {
		try {
			if (libData) {
				MLStream<ML::Encoding::UTF8> mls{libData->getWSLINK(libData)};
				mls << ML::Function("EvaluatePacket", 1);
				mls << ML::Function("Set", 2);
				mls << ML::Symbol(WLSymbol);
				if (!MLTransferToEndOfLoopbackLink(mls.get(), messageParams)) {
					return LLErrorCode::FunctionError;
				}
				libData->processWSLINK(mls.get());
				auto pkt = MLNextPacket(mls.get());
				if (pkt == RETURNPKT) {
					mls << ML::NewPacket;
				}
			}
		} catch (const LibraryLinkError& e) {
			return e.which();
		} catch (...) {
			return LLErrorCode::FunctionError;
		}
		return LLErrorCode::NoError;
	}

} /* namespace LibraryLinkUtils */
