#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char** argv)
{
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
    vector<int> data;
    string str;

    int deph = 0;
    int prevdeph = -1;


//    while(getline(ifs, str))
//    {
//        deph = stoi(str, 0, 10);
//        data.push_back(deph);
//    }
    getline(ifs, str);
    prevdeph = stoi(str, 0, 10);
    data.push_back(prevdeph);

    int increaseCounter = 0;
    cout << str << "\t" << endl;
    while(getline(ifs, str))
    {
        deph = stoi(str, 0, 10);
        if (deph > prevdeph)
        {
            ++increaseCounter;
        }

        cout << str << "\t" << ((deph > prevdeph) ? "inc" : "desc") << endl;

        prevdeph = deph;
        data.push_back(deph);
    }

    cout << endl << endl;
    cout << "count inc=" << increaseCounter << endl;

    increaseCounter = 0;
    prevdeph = INT_MAX;
    for (size_t i = 0; i < data.size() - 2; ++i)
    {
        deph = data[i] + data[i+1] + data[i+2];

        if (deph > prevdeph)
        {
            ++increaseCounter;
        }

        cout << deph << "\t" << ((deph > prevdeph) ? "inc" : (deph == prevdeph ? "no-change" : "desc")) << endl;

        prevdeph = deph;
    }

    cout << endl << endl;
    cout << "count inc=" << increaseCounter << endl;



    return 0;
}
