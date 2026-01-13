export module Vector;

import <vector>;

namespace VectorOps {

	export class Vector {

	private:

		// data stored in the vector
		std::vector<double> vData;

		// int vecSize; // size of vector; from Vector.hpp

	public:

		// define how a new different vector is created via the copy constructor

		// Vector(const Vector& otherVector);

		// you don't need to implement the copy constructor manually
		// std::vector already knows how to copy its data
		// therefore, we can just write:

		Vector(const Vector&) = default;

		// size of vector to be initialised

		// Vector(int size);

		// alter this to initialise a vector with a given size

		vector(int size) : vData(size) {}

		// free memory; std::vector takes care of memory management
		//~Vector();

		// function to get the size of the vector;
		int GetSize() const;
	};


}
