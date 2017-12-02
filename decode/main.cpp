#include <iostream>
#include <fstream>
#include <string>
#include "cmdline.h"

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

void calc_input(const std::string & input)
{
    ifstream ifs(input.c_str());
    while (!ifs.eof()) {
        string line;
        getline(ifs, line);
        cout << line << endl;
    }
}

int main(int argc, char *argv[])
{
    cmdline::parser cmd_parser;
    cmd_parser.add<std::string>("input", 'i', "input", true);
    cmd_parser.parse_check(argc, argv);
    std::string input = cmd_parser.get<std::string>("input");


    double **W = NULL;
    double *b = NULL;
    load_w_b(W, b);

    calc_input(input);

    return 0;
}