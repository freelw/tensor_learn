#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream ifs("../param");
    int w = 0;
    int h = 0;
    ifs >> w >> h;
    double **W = new (double*)[h];
    for (int i = 0; i < h; ++ i) {
        W[i] = new double[w];
        for (int j = 0; j < w; ++j) {
            W[i][j] = 0;
        }
    }

    double *b = new double[h];
    for (int i = 0; i < h; ++ i) {
        b[i] = 0;
    }

    cout << w << " " << b << endl;
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
    return 0;
}