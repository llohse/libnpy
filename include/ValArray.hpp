#pragma once
#include<valarray>
#include<vector>
#include"npy.hpp"

namespace npy {
	using std::string;
	using std::vector;
	using std::valarray;

	template<typename _Ty>
	class ValArray : public valarray<_Ty>{
	private:
		unsigned int n_dims = 0;
	public:
		using valarray<_Ty>::valarray;

		bool fortran_order = false;
		vector<npy::ndarray_len_t> shape;

		unsigned int get_dim() {
			this->n_dims = shape.size();
			return this->n_dims;
		}

		void load(const string& filePath) {
			LoadArrayFromNumpy<_Ty>(
				filePath, this->fortran_order, this->n_dims,
				this->shape, static_cast<valarray<_Ty>>(*this)
			);
		}

		void save(const string& filePath) {
			this->n_dims = shape.size();
			SaveArrayAsNumpy<_Ty> (
				filePath, this->fortran_order, this->n_dims,
				this->shape, static_cast<valarray<_Ty>>(*this)
			);
		}
	};
}

