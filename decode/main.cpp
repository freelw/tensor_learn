#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
#include "cmdline.h"

using namespace std;

#define PARAM_PATH "../param"

void load_w_b(double ** & W, double * & b, int & w, int & h)
{
    ifstream ifs(PARAM_PATH);
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

void get_tag_and_vec(const string & line, int & tag, vector<double> & vec, int width)
{
    string str;
    if (2 < line.length()) {
        if ('0' == line[0]) {
            tag = 0;
        } else {
            tag = 1;
        }
        str = line.substr(2, width);
    } else {
        tag = 0;
        str = "";
    }
    
    for (int i = 0; i < (int)str.length(); ++ i) {
        vec.push_back(double(str[i]));
    }
    for (int i = (int)str.length(); i < width; ++ i) {
        vec.push_back(0);
    }
}

void mul(const vector<double> vec, int width, int height, double **W, double *b, vector<double> & res)
{
    assert((int)vec.size() == width);
    for (int i = 0; i < height; ++ i) {
        double tmp = 0;
        for (int j = 0; j < width; ++ j) {
            tmp += W[i][j] * vec[j];
        }
        tmp += b[i];
        res.push_back(tmp);
    }
}

void print_res(const vector<double> & res)
{
    for (int i = 0; i < (int)res.size(); ++ i) {
        cout << res[i] << " ";
    }
    cout << endl;
}

double safe_div(double a, double b) {
    if (0 == b) {
        b = 0.000000001;
    }
    return a/b;
}

void calc_input(const std::string & input, int width, int height, double **W, double *b)
{
    ifstream ifs(input.c_str());
    int calc_bad_req_count = 0;
    int fault_count = 0;
    int tag_bad_count = 0;
    while (!ifs.eof()) {
        string line;
        getline(ifs, line);
        int tag = 0;
        vector<double> vec;
        get_tag_and_vec(line, tag, vec, width);
        vector<double> res;
        mul(vec, width, height, W, b, res);
        if (0 < res[1]) {
            ++ calc_bad_req_count;
            if (0 == tag) {
                cout << line << endl;
                ++ fault_count;
            }
        }
        if (1 == tag) {
            ++ tag_bad_count;
        }
    }

    cout << "calc_bad_req_count : " << calc_bad_req_count << endl;
    cout << "fault_count : " << fault_count << endl;
    cout << "tag_bad_count : " << tag_bad_count << endl;
    cout << "fault rate : " << safe_div(fault_count, calc_bad_req_count) * 100 << "%" << endl;
    cout << "hit rate : " << safe_div(calc_bad_req_count, tag_bad_count) * 100 << "%" << endl;
}

int main(int argc, char *argv[])
{
    cmdline::parser cmd_parser;
    cmd_parser.add<std::string>("input", 'i', "input", true);
    cmd_parser.parse_check(argc, argv);
    std::string input = cmd_parser.get<std::string>("input");

    double **W = NULL;
    double *b = NULL;
    int width = 0;
    int height = 0;
    load_w_b(W, b, width, height);

    calc_input(input, width, height, W, b);

    return 0;
}