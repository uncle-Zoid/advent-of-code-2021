#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;


int flash = 0;

void print(int *cave, const int N)
{
    cout << endl << endl;
    for(int i = 0; i < N*N; ++i)
    {
        if ((i % N == 0) && i > 0)
            cout << endl;
        cout << setw(5) << setfill(' ') << cave[i];
    }
}

void check(int mi, int mj, int cave[][10], int N)
{
//    print(*cave, N);

    auto &meduse = cave[mi][mj];
    if (meduse > 9)
    {
        meduse = 0;
        for (int i = mi - 1; i <= mi + 1; ++i)
        {
            for (int j = mj - 1; j <= mj + 1; ++j)
            {
                if (!(i < 0 || j < 0 || i >= N || j >= N))
                {
                    if (cave[i][j] != 0 || (i==mi && j==mj))
                    ++cave[i][j];
                    if (cave[i][j] > 9)
                    {
                        check(i,j, cave, N);
                    }
                }
            }
        }
        ++ flash;
        meduse = 0;
        assert(meduse == 0);
//        print(*cave, N);
//        getchar();
    }
}
void round(int cave[][10], int N)
{
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            ++cave[i][j];
        }
    }
//    print(*cave, N);

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            check(i, j, cave, N);
        }
    }
}
bool checkFullFlash(int cave[][10], int N)
{
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(cave[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    cout << "Day11" << endl;
    if (argc < 2)
    {
        cerr << "zadej soubor" << endl;
        return -1;
    }
    cout << "Cteni: " << argv[1] << endl;


    int cave[10][10]{};
    ifstream ifs(argv[1]);
    if (!ifs)
    {
        cerr << "chyba otevirani " << argv[1] << endl;
        return -1;
    }

    string str;
    stringstream ss;
    list<string> r;
    int i = 0;
    while(getline(ifs, str))
    {
        for (size_t j = 0; j < str.size(); ++j)
        {
            cave[i][j] = str[j] - 48;
        }
        ++i;
    }

    print(*cave, 10);
    i = 1;
    for (; i < 500; ++i)
    {
        round(cave,  10);
//        print(*cave, 10);
        if(checkFullFlash(cave,  10))
        {
            break;
        }
//        getchar();
    }
    print(*cave, 10);
    cout << "\nFlash count: " << flash << endl;
    cout << "\nAll flash in round: " << i << endl;
    return 0;
}
