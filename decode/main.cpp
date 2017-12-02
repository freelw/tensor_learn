#include <iostream>
#include <fstream>

using namespace std;

#define PARAM_PATH "../param"

void load_w_b(double ** & W, double * & b)
{
    ifstream ifs(PARAM_PATH);
    int w = 0;
    int h = 0;
    ifs >> w >> h;
    W = new double*[h];
    for (int i = 0; i < h; ++ i) {
        W[i] = new double[w];
        for (int j = 0; j < w; ++j) {
            W[i][j] = 0;
        }
    }

    b = new double[h];
    for (int i = 0; i < h; ++ i) {
        b[i] = 0;
    }

    cout << w << " " << h << endl;
    for (int i = 0; i < h; ++ i) {
        for (int j = 0; j < w; ++ j) {
            ifs >> W[i][j];
            cout << W[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < h; ++ i) {
        ifs >> b[i];
        cout << b[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    double **W = NULL;
    double *b = NULL;
    load_w_b(W, b);

    return 0;
}