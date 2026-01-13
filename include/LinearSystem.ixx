// LinearSystem.ixx

export module LinearSystem;

import Matrix;
import Vector;

import <stdexcept>;

namespace LinearAlgebra {

	// linear system takes the form:

	// Ax = b

	// A is the matrix of coefficients of the (unknown) vector x, and b represents the force/source terms acting on the system

	export class LinearSystem {

	protected:

		std::size_t mSize{}; // system size
		const Matrix& mA; // coefficient matrix
		const Vector& mb; // source vector

	public:

		// enforce system creation
		explicit LinearSystem(const Matrix& A, const Vector& b) : mSize(A.GetNumRows()), mA(A), mb(b) {

			if (A.GetNumRows() != A.GetNumCols()) {

				throw std::invalid_argument("Matrix A must be Square");
			}

			if (A.GetNumRows() != static_cast<std::size_t>(b.GetSize())) {

				throw std::invalid_argument("Matrix A and Vector b size Mismatch");
			}
		}

		// -- rule of zero -- //

		LinearSystem(const LinearSystem&) = default;
		LinearSystem& operator=(const LinearSystem&) = default;
		LinearSystem(LinearSystem&&) noexcept = default;
		LinearSystem& operator=(LinearSystem&&) noexcept = default;
		virtual ~LinearSystem() = default;

		// solve method
		[[nodiscard]]
		virtual Vector Solve() const {

			{ throw std::logic_error("Solve() not implemented: use a derived LinearSystem solver"); }
		}

		// -- accessors -- //

		// get size of system
		[[nodiscard]] std::size_t Size() const noexcept { return mSize; }

		// get matrix A 
		[[nodiscard]] const Matrix& GetMatrix() const noexcept { return mA; }

		[[nodiscard]] const Vector& GetRHS() const noexcept { return mb; }
	};
}
