// Matrix.ixx
// class (module which performs matrix/linear algebra)

export module Matrix;

import <vector>;
import <stdexcept>;
import <cmath>;

// Vector.ixx module
import Vector;

namespace LinearAlgebra {

	export class Matrix {

	private:

		std::vector<double> mData; // contiguuous row-majour storage
		std::size_t mRows {};
		std::size_t mCols {};

		constexpr std::size_t index(std::size_t i, std::size_t j) const noexcept { // note: i, j are positions of matrix elements

			return i * mCols + j;
		}

	public:

		// -- Constructors -- //

		Matrix() = default;

		Matrix(std::size_t rows, std::size_t cols) : mData(rows * cols, 0.0), mRows(rows), mCols(cols) {}

		// -- Rule of zero -- //

		Matrix(const Matrix&) = default;
		Matrix& operator=(const Matrix&) = default;
		Matrix(Matrix&&) noexcept = default;
		Matrix& operator=(Matrix&&) noexcept = default;
		~Matrix() = default;

		// -- accessors -- //

		// get number of matrix rows
		[[nodiscard]] std::size_t GetNumRows() const noexcept { return mRows; }

		// get number of matrix columns
		[[nodiscard]] std::size_t GetNumCols() const noexcept { return mCols; }

		// -- *** -- //

		double& operator()(std::size_t i, std::size_t j) {

			if (i == 0 || j == 0 || i > mRows || j > mCols) {

				throw std::out_of_range("Matrix Index out of Range");
			}

			return mData[index(i - 1, j - 1)];
		}

		double operator()(std::size_t i, std::size_t j) const {

			if (i == 0 || j == 0 || i > mRows || j > mCols) {

				throw std::out_of_range("Matrix Index out of Range");
			}

			return mData[index(i - 1, j - 1)];
		}

		// unary operator
		Matrix operator-() const {

			Matrix result(*this);

			for (auto& v : result.mData) { v = -v; }

			return result;
		}

		// -- binary operators -- //

		// addition
		Matrix operator+(const Matrix& other) const {

			// check rows and columns other Matrix object equal those of another Matrix object
			if (mRows != other.mRows || mCols != other.mCols) {

				throw std::invalid_argument("Matrix Size Mismatch");
			}

			Matrix result(mRows, mCols);

			for (std::size_t i { 0 }; i < mData.size(); ++i) {

				result.mData[i] = mData[i] + other.mData[i];
			}

			return result;
		}

		// subtraction
		Matrix operator-(const Matrix& other) const {

			if (mRows != other.mRows || mCols != other.mCols) {

				throw std::invalid_argument("Matrix Size Mismatch");
			}

			Matrix result(mRows, mCols);

			for (std::size_t i { 0 }; i < mData.size(); ++i) {

				result.mData[i] = mData[i] - other.mData[i];
			}

			return result;
		}

		// scalar multiplication
		Matrix operator*(double a) const {

			for (auto& v : result.mData) { v *= a; }

			return result;
		}

		// determinant: simple recursive version; square matrices only
		[[nodiscard]] double CalculateDeterminant() const {

			if (mRows != mCols) { throw std::logic_error("Determinant requires matrix"); }

			if (mRows == 2) { return(*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1); }

			double det { 0.0 };

			for (std::size_t col { 1 }; col <= mCols; ++col) {

				Matrix minor(mRows - 1, mCols - 1);

				for (std::size_t i { 2 }; i <= mRows; ++i) {

					std::size_t mj { 1 };

					for (std::size_t j { 1 }; j <= mCols; ++j) {

						if (j == col) continue;

						minor(i - 1, mj++) = (*this)(i, j);
					}
				}

				det += ((col % 2 == 1) ? 1.0 : -1.0)
					* (*this)(1, col)
					* minor.CalculateDeterminant();
			}

			return det;
		}

		// (friend) vector multiplication
		friend VectorOps::Vector operator*(const Matrix& m, const VectorOps::Vector& v);
	};

	// Matrix * Vector
	export VectorOps::Vector operator*(const Matrix& m, const VectorOps::Vector& v) {

		if (m.GetNumCols() != static_cast<std::size_t>(v.GetSize())) {

			throw std::invalid_argument("Matrix-Vector size Mismatch");
		}

		VectorOps::Vector result(static_cast<int>(m.GetNumRows()));

		for (std::size_t i { 1 }; i <= m.GetNumRows(); ++i) {

			double sum { 0.0 };

			for (std::size_t j { 1 }; i <= m.GetNumCols(); ++j) {

				sum += m(i, j) * v(j);
			}

			result(i) = sum;
		}

		return result;
	}
}
