#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

char mostCommon(vector<string> &v, int bit)
{
    int ones = 0;
    int zeros = 0;

    for (auto &s : v)
    {
        if(s[bit] == '1')  ++ones;
        else                ++ zeros;
    }
    return ones >= zeros ? '1' : '0';
}
void eraseElse(vector<string> &v, int pos, char bit)
{
    v.erase(remove_if(v.begin(), v.end(), [=](const string &s) { return s[pos] != bit; }), v.end());
}

int main(int argc, char** argv)
{
    cout << "Day2" << endl;
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

    vector<int> ones;
    vector<string> full;
    int lines = 0;
    while(ifs)
    {
        ifs >> str;
        if (!ifs)
        {
            break;
        }
        full.push_back(str);

        ones.resize(str.length());
        for (size_t i = 0; i < str.length(); ++i)
        {
            ones[i] += str[i] == '1';
        }
        ++ lines;
    }

    int zeros = 0;
    int gama = 0;
    int epsilon = 0;
    for (auto it = ones.begin(); it != ones.end(); ++it)
    {
        gama <<= 1;
        epsilon <<= 1;

        zeros = lines - *it;
        gama |= *it > zeros;
        epsilon |= zeros > *it;

    }
    cout << "part one" << endl;
    cout << "gama=" << gama << ", epsilon=" << epsilon << "\t" << (gama * epsilon) << endl;


    auto oxy = full;
    cout  << "part two" << endl;
    for (size_t i = 0; i < oxy.front().size(); ++i)
    {
        char mc = mostCommon(oxy, i);
        eraseElse(oxy, i, mc);
        if (oxy.size() == 1)
            break;
    }
    auto valoxy = stoi(oxy.front(), 0, 2);
    cout << "OXY=" << oxy.size() << "\t" << oxy.front()  << " = " << valoxy << endl;


    auto co2 = full;
    for (size_t i = 0; i < co2.front().size(); ++i)
    {
        char mc = mostCommon(co2, i);
        eraseElse(co2, i, mc == '1' ? '0' : '1');

        if (co2.size() == 1)
            break;
    }
    auto valco2 = stoi(co2.front(), 0, 2);
    cout << "CO2=" << co2.size() << "\t" << co2.front() << " = " << valco2 << endl;

    cout << "result=" << valco2 * valoxy << endl;
    return 0;
}
