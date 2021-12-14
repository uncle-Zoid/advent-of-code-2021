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



struct Navigation
{
    struct Line
    {
        string line;
        char invalid = 0;
    };

    list<Line> lines;

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
            Line l;
            l.line = str;
            lines.emplace_back(std::move(l));
        }

        return 0;
    }

    void print () const
    {
        int score = 0;
        for (auto &l : lines)
        {
            cout << l.line << (l.invalid == 0x7F ? "incomplede" : (l.invalid == 0x00 ? "" : ("corrupted with " + string(1, l.invalid)))) << endl;
            if (l.invalid > 0 && l.invalid < 0x7F)
            {
                auto it = illegalPoints.find(l.invalid);
                score += it->second;
            }
        }
        cout << "Score=" << score << endl;
        cout << endl;
        cout << endl;
    }

    static constexpr const char* chunksOpen = "([{<";
    static constexpr const char* chunksClose = ")]}>";
    const map<char, int> illegalPoints = {{')',3},{']',57},{'}',1197},{'>',25137}};

    char findClosingChunkFor(char chunk)
    {
        auto it = find(chunksOpen, chunksOpen + 4, chunk);
        int pos = std::distance(chunksOpen, it);
        return chunksClose[pos];
    }

    void findInvalidLines()
    {
        const char chunks [][2] = {{'(', ')'} , {'[', ']'} , {'{', '}'} , {'<', '>'}};
        for (auto &l : lines)
        {
            list<char> p;
            for (char ch : l.line)
            {
                if(find(chunksOpen, chunksOpen + 4, ch) != chunksOpen + 4)
                {
                    p.push_back(ch);
                }
                else
                {
                    auto shallclosing = findClosingChunkFor(p.back());
                    if (shallclosing != ch)
                    {
                        l.invalid = ch; // corrupted
                        break;
                    }
                    p.pop_back();
                }
            }
            if (l.invalid == 0 && p.size() > 0)
            {
                l.invalid = 0x7F; // incomplete
            }
        }
    }
};

int main(int argc, char** argv)
{
    cout << "Day10" << endl;
    if (argc < 2)
    {
        cerr << "zadej soubor" << endl;
        return -1;
    }
    cout << "Cteni: " << argv[1] << endl;


    Navigation navi;
    if(navi.load(argv[1]) < 0)
    {
        return -1;
    }

    navi.print();
    navi.findInvalidLines();
    navi.print();
    return 0;
}
