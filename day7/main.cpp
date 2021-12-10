#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;

void print(const multiset<int> &crabs)
{
    char delim = ' ';
    for (auto &f : crabs)
    {
        cout << delim << f;
        delim = ',';
    }
    cout << endl;
}

int calcFuel(int steps)//4=10
{
    int result = steps;
    while (--steps > 0)
    {
        result += steps;
    }
    return result;
}

int main(int argc, char** argv)
{
    cout << "Day7" << endl;
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

    multiset<int> crabs;

    int N = 0;
    while(ifs)
    {
        ifs >> N;
        if (!ifs)
        {
            break;
        }
        crabs.insert(N);
        ifs>>ch;
    }

    cout << endl << endl;;
    cout << "crabs: "; print(crabs);
    cout << "Min=" << *crabs.begin() << endl;
    cout << "Max=" << *crabs.rbegin() << endl;
    int min = INT_MAX;
    int position = 0;
    for (int i = *crabs.begin(); i < *crabs.rbegin(); ++i)
    {
        int total = 0;
        for (auto it = crabs.cbegin(); it != crabs.cend(); ++it)
        {
            total += calcFuel( abs(i - *it));
        }
        if (total < min)
        {
            min = total;
            position = i;
        }
//        cout << "position is: " << i << ", need fuel=" << total << endl;
    }

    cout << "best position is: " << position << ", need fuel=" << min << endl;
    return 0;
}
