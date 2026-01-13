// BVPODETestLogic.ixx

export module BVPODETestLogic;

import <vector>;
import <fstream>;
import <cmath>;
import <string>;
import <stdexcept>;

import BVPODE;

namespace Tests::Logic {

	// RHS functions
	constexpr double modelProb1RHS(double /*X*/) noexcept { return 1.0; }

	inline double modelProb2RHS(double x) noexcept { return 32.0 * std::sin(x); }

	// small utility struct for returning results
	export struct TestResult {

		bool passed {};
		std::string message {};
	};

	// file reader
	inline void ReadIn(const std::string& filename, std::vector<double>& xs, std::vector<double>& us) {

		std::ifstream file(filename);

		if (!file) {

			throw std::runtime_error("Failed to open file: " + filename);
		}

		double x {}, u {};

		while (file >> x >> u) {

			xs.push_back(x);
			us.push_back(u);
		}
	}

	// -- Model Problem 1 -- //

	export TestResult RunModelProblem1() {

		SecondOrderODE ODE(

			-1.0, 0.0, 0.0,

			modelProb1RHS,
			
			0.0, 1.0
		);

		BoundaryConditions BC;

		BC.SetLHSDirichletBC(0.0);
		BC.SetRHSDirichletBC(0.0);

		constexpr std::size_t N { 101 };

		BVPODE solver(ODE, BC, N);
		solver.SetFilename("Model_Problem_Results1.dat");
		solver.Solve();

		std::vector<double> xs, us;

		ReadIn("Model_Problem_Results1.dat", xs, us);

		if (xs.size() != N || us.size() != N) { return {false, "Incorrect Output Vector Size"}; }

		for (std::size_t i { 0 }; i < N; ++i) {

			const double exact = xs[i] * (1.0 - xs[i]) / 2.0;

			if (std::abs(us[i] - exact) > 1e-8) { return {false, "Solution Mismatch in Model Problem 1"}; }
		}

		return {true, "Model Problem 1 Passed"};
	}

	// -- Model Problem 2 -- //

	export TestResult RunModelProblem2() {

		SecondOrderODE ODE(

			1.0, 3.0, -4.0,

			modelProb2RHS,

			0.0, M_PI
		);

		BoundaryConditions BC;
		BC.SetLHSNeumannBC(-5.0);
		BC.SetRHSDirichletBC(4.0);

		constexpr std::size_t N { 1001 };

		BVPODE solver(ODE, BC, N);
		solver.SetFilename("Model_Problem_Results2.dat");
		solver.Solve();

		std::vector<double> xs, us;

		ReadIn("Model_Problem_Results2.dat", xs, us);

		if (xs.size() != N || us.size() != N) { return {false, "Incorrect Output Vector Size"}; }

		for (std::size_t i { 0 }; i < N; ++i) {

			const double x = xs[i];

			const double exact =

				(4 * std::exp(x) + std::exp(-4 * x)) /
				(4 * std::exp(M_PI) + std::exp(-4 * M_PI))
				- 5 * std::sin(x)
				- 3 * std::cos(x);

			if (std::abs(us[i] - exact) > 2e-3) { return {false, "Solution Mismatch in Model Problem 2"}; }
		}

		return {true, "Model Problem 2 Passed"};
	}
}

