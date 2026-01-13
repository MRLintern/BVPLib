// BVPODECxxTestSuite.ixx

export module BVPODECxxTestSuite;

// CxxTest testing; not C++20 => include not import
#include <cxxtest/TestSuite.h>

import BVPODETestLogic;

namespace Tests {

	export class BVPODETestSuite final : public CxxTest::TestSuite {

	public:

		void TestModelProblem1() {

			const auto result = Logic::RunModelProblem1();
			TS_ASSERT(result.passed);
		}

		void TestModelProblem2() {

			const auto result = Logic::RunModelProblem2();
			TS_ASSERT(result.passed);
		}
	};
}
