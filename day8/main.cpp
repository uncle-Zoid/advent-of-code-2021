#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;



struct Rowy
{
    string part1[10];
    string part2[4];

    void print () const
    {
        for (int i = 0; i < 10; ++i) cout << part1[i] << " ";
        cout << "|";
        for (int i = 0; i < 4; ++i) cout << part2[i] << " ";

        cout << endl;
    }

    int countUnique() const
    {
        // 1=2, 4=4, 7=3, 8=7
        int res = 0;
        for (int i = 0; i < 4; ++i)
        {
            auto si = part2[i].size();
            if (si == 7 || (si >= 2 && si <= 4))
            {
                ++res;
            }
        }
        return res;
    }

    int decodeNumber(const string &number) const
    {
        auto si = number.size();
        switch (number.size())
        {
        case 2: return 1;
        case 4: return 4;
        case 3: return 7;
        case 7: return 8;
        }

        if (si == 7 || (si >= 2 && si <= 4))
        {
            return si;
        }

        list <std::map <int, string>::const_iterator> its;

        // 1.  naplt seznam
        for (auto d = decoder.cbegin(); d != decoder.cend(); ++d)
        {
            auto r = std::count(d->second.begin(), d->second.end(), number.back());
            if (r == 1 && d->second.size() == number.size())
            {
                its.push_back(d);
            }
        }
        // 2. projit a hledat obsahujici vsechny znaky ze vzoru
        for (auto &letter : number)
        {
            for (auto it = its.begin(); it != its.end();)//its.size() > 1 && copy.size() > 0)
            {
                auto & val = (*it)->second; // string z mapy
                auto r = std::count(val.begin(), val.end(), letter);
                if (r == 0)
                {
                    it = its.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        assert (its.size() == 1);

        return its.front()->first;
    }

    int decodePart2() const
    {
        int res = 0;
        for (int i = 0; i < 4; ++i)
        {
            auto subres = decodeNumber(part2[i]);

            res += subres * pow(10, 3-i);

        }
        return res;


    }

    std::map <int, string> decoder = {
          {0, "cagedb"}
//        , {1, "ab"}
        , {2, "gcdfa"}
        , {3, "fbcad"}
//        , {4, "eafb"}
        , {5, "cdfbe"}
        , {6, "cdfgeb"}
//        , {7, "dab"}
//        , {8, "acedgfb"}
        , {9, "cefabd"}
    };
};

int main(int argc, char** argv)
{
    cout << "Day8" << endl;
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

    list<Rowy> rowy;

    while(ifs)
    {
        Rowy rw;
        for (int i = 0; i < 10; ++i) ifs >> rw.part1[i];
        ifs >> ch;
        if (ch != '|') exit(-1);
        for (int i = 0; i < 4; ++i) ifs >> rw.part2[i];


        if (!ifs)
        {
            break;
        }

        rowy.emplace_back(std::move(rw));

    }

    // 1=2, 4=4, 7=3, 8=7
    int total = 0;
    for (const auto &rw : rowy)
    {
//        rw.print();
        int cu = rw.countUnique();
//        cout << cu << endl;

        total += cu;
    }
    cout << "\npart 1: Total unique: " << total << endl;

    // part2
    for (const auto &rw : rowy)
    {
        rw.print();
        int cu = rw.decodePart2();
        cout << cu << endl;

        total += cu;
    }


    return 0;
}
