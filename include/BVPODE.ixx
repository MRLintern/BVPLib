// BVPODE.ixx

export module BVPODE;

import <string>;
import <memory>;
import <stdexcept>;

import Matrix;
import Vector;
import LinearSystem;
import FiniteDifferenceGrid;
import SecondOrderODE;
import BoundaryConditions;

namespace BVP {

	export class BVPODE {

	private:

		std::size_t nNumNodes {};
		FiniteDifferenceGrid mGrid;

		const SecondOrderODE& mODE;
		const BoundaryConditions& mBC

		Vector mSolution;
		Vector mRHS;
		Vector mLHS;

		LinearSystem mLinearSystem;

		std::string mFilename {"BVP_Solution.dat"};

		// -- assembly steps -- //

		void PopulateMatrix();
		void PopulateVector();
		void ApplyBoundaryConditions();

	public:

		explicit BVPODE(const SecondOrderODE& ODE, const BoundaryConditions& BC, std::size_t numNodes)

				 : mNumNodes(numNodes), 
				   mGrid(numNodes, ODE.XMin(), ODE.XMax()),
				   mODE(ODE),
				   mBC(BC),
				   mSolution(static_cast<int>(numNodes)),
				   mRHS(static_cast<int>(numNodes)),
				   mLHS(numNodes, numNodes),
				   mLinearSystem(mLHS, mRHS)

		{
			if (numNodes < 2) { throw std::invalid_argument("BVPODE Requires at Least 2 Nodes."); }
		}

		// -- rule of zero -- //

		BVPODE(const BVPODE&) = default;
		BVPODE& operator=(const BVPODE&) = default;
		BVPODE(BVPODE&&) noexcept = default;
		BVPODE& operator=(BVPODE&&) noexcept = default;
		~BVPODE() =default;

		void Solve();
		void WriteSolutionFile() const;
	};
}

