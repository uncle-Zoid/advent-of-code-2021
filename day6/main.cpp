#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;

void print(const vector<int> &fishes)
{
    char delim = ' ';
    for (auto &f : fishes)
    {
        cout << delim << f;
        delim = ',';
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    cout << "Day6" << endl;
    if (argc < 2)
    {
        cerr << "zadej soubor" << endl;
        return -1;
    }
    cout << "Cteni: " << argv[1] << endl;

    ifstream ifs(argv[1]);
    if (!ifs)
    {
        cerr << "chyba otevirani " << argv[1] << endl;
        return -1;
    }

    string str;
    stringstream ss;
    char ch;

    vector<int> fishes;

    int N = 0;
    while(ifs)
    {
        ifs >> N;
        if (!ifs)
        {
            break;
        }
        fishes.push_back(N);
        ifs>>ch;
    }

    cout << endl << endl;;
    cout << "initial: "; print(fishes);

    for (int i = 0; i < 256 ; ++i)
    {
        int max = fishes.size();
        for (int j = 0; j < max; ++j)
        {
            fishes[j] -= 1;
            if (fishes[j] < 0)
            {
                fishes[j] = 6;
                fishes.push_back(8);
            }
        }
//        cout << "day " << left << setw(3) << setfill(' ') << (i+1) << ": "; print(fishes);
    }

    cout << "Total fishes: " << fishes.size() << endl;
    return 0;
}
