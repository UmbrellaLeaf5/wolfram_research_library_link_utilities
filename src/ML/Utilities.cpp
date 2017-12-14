/** 
 * @file	Utilities.cpp
 * @date	Nov 26, 2017
 * @author	rafalc
 * @brief	<brief description>
 */

#include "Utilities.h"

#include <string>

#include "mathlink.h"
#include "MathLinkStream.h"

namespace LibraryLinkUtils {

	namespace ML {

		const std::string& Symbol::getHead() const {
			return head;
		}

		int Function::getArgc() const {
			return argc;
		}

		void Function::setArgc(int newArgc) {
			argc = newArgc;
		}

		MathLinkStream& NewPacket(MathLinkStream& ms) {
			MLNewPacket(ms.get()); //TODO error checking
			return ms;
		}

		MathLinkStream& EndPacket(MathLinkStream& ms) {
			MLEndPacket(ms.get()); //TODO error checking
			return ms;
		}

		MathLinkStream& Flush(MathLinkStream& ms) {
			MLFlush(ms.get()); //TODO error checking
			return ms;
		}

		MathLinkStream& Rule(MathLinkStream& ms, Direction dir) {
			if (dir == Direction::Put)
				return ms << Function("Rule", 2);
			else
				return ms >> Function("Rule", 2);
		}

		std::string getMLErrorText(MLINK mlp) {
			std::string err = "Error code reported by MathLink: " + std::to_string(MLError(mlp)) + "\n";
			auto mlErrorMsg = MLErrorMessage(mlp);
			err += "\"" + std::string(mlErrorMsg) + "\"\nAdditional debug info: ";
			MLReleaseErrorMessage(mlp, mlErrorMsg);
			MLClearError(mlp);
			return err;
		}


		void checkError(MLINK m, int statusOk, int errorCode, const std::string& debugInfo) {
			if (!statusOk) {
				ErrorManager::throwException(errorCode, getMLErrorText(m) + debugInfo);
			}
		}

		void checkError(MLINK m, int statusOk, const std::string& errorName, const std::string& debugInfo) {
			if (!statusOk) {
				ErrorManager::throwException(errorName, getMLErrorText(m) + debugInfo);
			}
		}

	}
}
