#include<valarray>
#include<vector>
#include<string>
#include"../include/ValArray.hpp"

using namespace std;

// val_test
namespace val_test_3 {
    int test_load(void) {
        npy::ValArray<double> data;
        for (auto path : {"data/f8.npy", "data/f8_t.npy"}) {
            data.resize(0);
            data.load(path);

            cout << "shape: ";
            for (size_t i = 0; i < data.shape.size(); i++){
                cout << data.shape[i] << ", ";
            }
            cout << endl;
            cout << "fortran order: " << (data.fortran_order ? "+" : "-") << endl
                << "data: ";
            for (size_t i = 0; i<data.size(); i++){
                cout << data[i] << ", ";
            }
            cout << endl;
        }

        return 0;
    }

    int test_save(void) {
        npy::ValArray<double> data { 1, 2, 3, 3, 4, 5 };
        data.shape = { 2,3 };
        data.save("data/out.npy");
        cout << "dim:" << data.get_dim() << endl;

        data.shape = {6};
        data.save("data/out2.npy");
        cout << "dim:" << data.get_dim() << endl;

        return 0;
    }
}
