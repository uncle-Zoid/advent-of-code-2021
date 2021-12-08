#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char** argv)
{
    cout << "Day2" << endl;
    if (argc < 2)
    {
        cerr << "zadej soubor" << endl;
        return -1;
    }
    char ch[2];
    ch[3] = 0;
    cout << ch;
    cout << "Cteni: " << argv[1] << endl;

    ifstream ifs(argv[1]);
    if (!ifs)
    {
        cerr << "chyba otevirani " << argv[1] << endl;
        return -1;
    }
//    vector<int> data;

//    int prevdeph = -1;


    /*
    int number = 0;
    string str;
    stringstream ss;
    int deph = 0;
    int forward = 0;
    // part 1
    while(ifs) //getline(ifs, str)
    {
        ifs >> str >> number;
        if (!ifs)
        {
            break;
        }

        switch (*str.c_str())
        {
        case 'f':
            forward += number;
            break;
        case 'd':
            deph += number;
            break;
        case 'u':
            deph -= number;
            break;
        }
    }
    cout << "forward=" << forward << ", deph=" << deph << "\t" << (forward * deph) << endl;*/

    int number = 0;
    string str;
    stringstream ss;
    int deph = 0;
    int forward = 0;
    int aim = 0;
    while(ifs)
    {
        ifs >> str >> number;
        if (!ifs)
        {
            break;
        }

        switch (*str.c_str())
        {
        case 'f':
            forward += number;
            deph += number * aim;
            break;
        case 'd':
            aim += number;
            break;
        case 'u':
            aim -= number;
            break;
        }
    }
    cout << "forward=" << forward << ", deph=" << deph << "\t" << (forward * deph) << endl;


    return 0;
}
