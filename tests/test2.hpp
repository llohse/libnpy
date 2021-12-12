#include<valarray>
#include<vector>
#include<string>
#include "../include/npy.hpp"

using namespace std;

// val_test
namespace val_test_2{
    int test_load(void) {
        vector<npy::ndarray_len_t> shape;
        bool fortran_order = false;
        valarray<double> data;
        unsigned int n_dims = 0;
        for (auto path : {"data/f8.npy", "data/f8_t.npy"}) {
            shape.clear();
            data.resize(0);
            npy::LoadArrayFromNumpy<double>(
                path, fortran_order, n_dims,
                shape, data
            );

            cout << "shape: ";
            for (size_t i = 0; i<shape.size(); i++){
                cout << shape[i] << ", ";
            }
            cout << endl;
            cout << "fortran order: " << (fortran_order ? "+" : "-") << endl
                << "data: ";
            for (size_t i = 0; i<data.size(); i++){
                cout << data[i] << ", ";
            }
            cout << endl;
        }

        return 0;
    }

    int test_save(void) {
        const vector<unsigned long> leshape = {2,3};
        valarray<double> data {1, 2, 3, 4, 5, 6};
        npy::SaveArrayAsNumpy("data/out.npy", false, 2, leshape, data);

        const vector<unsigned long> leshape2 = {6};
        npy::SaveArrayAsNumpy("data/out2.npy", false, 1, leshape2, data);

        return 0;
    }
}
