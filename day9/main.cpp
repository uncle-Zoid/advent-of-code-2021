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



struct Cave
{
    struct Point
    {
        int heigth;
        bool visited;
        bool canBeMinimum;
        bool minimum;


        friend ostream& operator <<(ostream&os, const Point &p)
        {
            os << p.heigth << (p.minimum ? "+" : (p.visited ? "*":" "));
            return os;
        }

        bool operator <(const Point &p)
        {
            return heigth < p.heigth;
        }
    };

    int rows;
    int columns;
    Point **heightmap;

    int load(const char *filename)
    {
        ifstream ifs(filename);
        if (!ifs)
        {
            cerr << "chyba otevirani " << filename << endl;
            return -1;
        }

        string str;
        stringstream ss;
        list<string> r;
        while(getline(ifs, str))
        {
            r.push_back(str);
        }
        rows = r.size();
        columns = r.front().size();

        heightmap = new Point*[rows]();
        auto it = r.begin();
        for (int i = 0; i < rows; ++i)
        {
            heightmap[i] = new Point[columns]();

            int j = 0;
            for (auto &p : *it)
            {
                heightmap[i][j++].heigth = p - 48;
            }
            ++it;
        }
        return 0;
    }

    void print () const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << setw(2) << setfill(' ') << heightmap[i][j];
            }
            cout << endl;
        }
    }

    void findMinimum(int i, int j)
    {
        print();cout << endl; getchar();
        //if (heightmap[i][j].visited) return true;

        heightmap[i][j].visited = true;

        // dolu
        if (i+1 < rows)
        {
            bool canBeMin = heightmap[i+1][j] < heightmap[i][j];
            if (canBeMin && heightmap[i+1][j].visited == false)
            {
                heightmap[i+1][j].canBeMinimum = true;
                findMinimum(i+1, j);
            }
            heightmap[i+1][j].visited = true;
//            return;
        }
        // nahoru
        if (i-1 >= 0)
        {
            bool canBeMin = heightmap[i-1][j] < heightmap[i][j];
            if (canBeMin && heightmap[i-1][j].visited == false)
            {
                heightmap[i-1][j].canBeMinimum = true;
                findMinimum(i-1, j);
            }
            heightmap[i-1][j].visited = true;
//            return;
        }
        // doprava
        if (j+1 < columns)
        {
            bool canBeMin = heightmap[i][j+1] < heightmap[i][j];
            if (canBeMin && heightmap[i][j+1].visited == false)
            {
                heightmap[i][j+1].canBeMinimum = true;
                findMinimum(i, j+1);
            }
            heightmap[i][j+1].visited = true;
//            return;
        }
        // doleva
        if (j-1 >= 0)
        {
            bool canBeMin = heightmap[i][j-1] < heightmap[i][j];
            if (canBeMin && heightmap[i][j-1].visited == false)
            {
                heightmap[i][j-1].canBeMinimum = true;
                findMinimum(i, j-1);
            }
            heightmap[i][j-1].visited = true;
//            return;
        }
        if(heightmap[i][j].canBeMinimum)
            heightmap[i][j].minimum = true;
    }

    bool check(int i, int j, int val)
    {
        if(heightmap[i][j].heigth < val)
        {
            expandAll(i,j);
        }
    }
    void expandAll(int i, int j)
    {
        print();cout << endl; getchar();
        //if (heightmap[i][j].visited) return true;

        heightmap[i][j].visited = true;

        // dolu
        if (i+1 < rows)
        {
        }
        // nahoru
        if (i-1 >= 0)
        {
        }
        // doprava
        if (j+1 < columns)
        {
        }
        // doleva
        if (j-1 >= 0)
        {

        }
    }

    void findMinimas()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                findMinimum(i,j);
            }
        }

    }

};

int main(int argc, char** argv)
{
    cout << "Day9" << endl;
    if (argc < 2)
    {
        cerr << "zadej soubor" << endl;
        return -1;
    }
    cout << "Cteni: " << argv[1] << endl;


    Cave cave;
    if(cave.load(argv[1]) < 0)
    {
        return -1;
    }
    cave.print();


    cave.findMinimas();
    return 0;
}
