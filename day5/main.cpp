#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;

struct Point
{
    int x = 0;
    int y = 0;

    int getBigger() const
    {
        return max(x,y);
    }

    bool operator<(const Point &p2)
    {
        return x < p2.x || y < p2.y;
    }
};

ostream &operator<<(ostream &stream, const Point &t)
{
    stream << "X=" << t.x << ", Y=" << t.y;
    return stream;
}


void draw(tuple<Point, Point> &l, uint8_t *field, int N)
{
    auto &p1 = std::get<0>(l);
    auto &p2 = std::get<1>(l);

    if ((p1.x == p2.x || p1.y == p2.y))
    {
        int x1 = min(p1.x, p2.x);
        int x2 = max(p1.x, p2.x);
        int y1 = min(p1.y, p2.y);
        int y2 = max(p1.y, p2.y);
        for (int row = y1; row <= y2; ++row)
        {
            for (int col = x1; col <= x2; ++col)
            {
                ++field[row*N + col];
            }
        }
    }
    else
    {
        int x1 = min(p1.x, p2.x);
        int x2 = max(p1.x, p2.x);
        int y1 = min(p1.y, p2.y);
        int y2 = max(p1.y, p2.y);

        int dx = (x1 - x2);
        int dy = (y1 - y2);
        assert (abs(dx) == abs(dy));

        int n = dx;
        int col = p1.x;
        int row = p1.y;
        int mcol = p1.x < p2.x ? -1:1;
        int mrow = p1.y < p2.y ? -1:1;

        for (int i = 0; i <= n; ++i)
        {
            ++field[row*N + col];
            row += mcol;
            col += mrow;

        }
    }
}

void print(uint8_t *field, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            auto val = field[i*N + j];
            cout << setw(3) << setfill(' ') << ((val == 0) ? "." : to_string(val));
        }
        cout << endl;
    }
}

int countOverlap(uint8_t *field, int N)
{
    int o = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (field[i*N + j] > 1)
            {
                ++o;
            }
        }
    }
    return o;
}

int main(int argc, char** argv)
{
    cout << "Day4" << endl;
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

    vector<tuple<Point, Point>> lines;

    int N = 0;
    while(ifs)
    {

        Point p1;
        Point p2;
        ifs >> p1.x >> ch >> p1.y;
        ifs >> str;
        ifs >> p2.x >> ch >> p2.y;

        if (!ifs)
        {
            break;
        }

        N = max(N, max(p1.getBigger(), p2.getBigger()));

        lines.push_back(make_tuple(p1, p2));
        cout << "P1: {" << p1 << "}, P2: {" << p2 << "}" << endl;
    }
//    N=16;
    N += 1;
    cout << endl << endl;;
    cout << "N=" << N << endl;


    uint8_t *field = new uint8_t[N*N]();

    for (auto &l : lines)
    {
        cout << "P1: {" << get<0>(l) << "}, P2: {" << get<1>(l) << "}" << endl;
        draw(l, field, N);
//        cout << "Overlaps: " << countOverlap(field, N) << endl;
        print(field, N);
        cout << endl;
        getchar();
    }

//    print(field, N);
    cout << "Overlaps: " << countOverlap(field, N) << endl;

    delete [] field;

    return 0;
}
