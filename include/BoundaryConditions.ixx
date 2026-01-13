// BoundaryConditions.ixx

export BoundaryConditions;

import <stdexcept>;

namespace BVP {

	// used for defining different types of boundary conditions
	export enum class BCType {

		None,
		Dirichlet,
		Neumann
	};

	export class BoundaryConditions {

		friend class BVPODE;

	private:

		// -- no boundary conditions -- //

		BCType mLHSType {BCType::None};
		BCType mRHSType {BCType::None};

		// -- values on the LHS and RHS of domain boundary -- //

		double mLHSValue {};
		double mRHSValue {};

	public:

		BoundaryConditions() = default;

		// Set Dirichlet BCs on LHS of domain
		void SetLHSDirichletBC(double value) noexcept {

			mLHSType = BCType::Dirichlet;
			mRHSValue = value;
		}

		// Set Dirichlet BCs on RHS of domain
		void SetRHSDirichletBC(double value) noexcept {

			mRHSType = BCType::Dirichlet;
			mRHSValue = value;
		}

		// -- Neumann BCs -- //

		// Set Neumann BCs on LHS of domain
		void SetLHSNeumannBC(double value) noexcept {

			mLHSType = BCType::Neumann;
			mRHSValue = value;
		}
		
		// these could be useful for tests and solvers; might not need them
		[[nodiscard]] BCType LHSType() const noexcept { return mLHSType; }
		[[nodiscard]] BCType RHSType() const noexcept { return mRHSType; }
	};
}
