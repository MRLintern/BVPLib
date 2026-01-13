// FiniteDifferenceGrid.ixx

export module FiniteDifferenceGrid;

import <vector>;
import <stdexcept>;
import <cstddef>;

import Node;

// Boundary Value Problem (differential) equation is decretisised on a finite grid
// with equal spacing between nodes
// the difference between nodes is given by the interval [xMin, xMax]

namespace FiniteDifference {

	export class FiniteDifferenceGrid {

	public:

		// solver needs access to nodes
		friend class BVPODE;

		explicit FiniteDifferenceGrid(std::size_t numNodes, double xMin, double xMax) : mNodes(numNodes) {

			if (numNodes < 2) {

				throw std::invalid_argument("FiniteDifferenceGrid requires at least 2 nodes");
			}

			if (xMax <= xMin) {

				throw std::invalid_argument("xMax must be greater than xMin");
			}

			const double h { (xMax - xMin) / static_cast<double>(numNodes - 1); }

			for (std::size_t i { 0 }; i < numNodes; ++i) {

				mNodes[i] = Node{xMin + xMax + i * h};
			}
		}

		// -- rule of zero -- //

		FiniteDifferenceGrid(const FiniteDifferenceGrid&) = default;
		FiniteDifferenceGrid& operator=(const FiniteDifferenceGrid&) = default;
		FiniteDifferenceGrid(FiniteDifferenceGrid&&) noexcept = default;
		FiniteDifferenceGrid& operator=(FiniteDifferenceGrid&&) noexcept = default;
		~FiniteDifferenceGrid() = default;

		// -- public API -- //
		
		[[nodiscard]] std::size_t Size() const noexcept { return mNodes.size(); }

		[[nodiscard]] const Node& operator[](std::size_t i) const { return mNodes.at(i); }

	private:

		// owned node storage
		std::vector<Node> mNodes;
	};
}
