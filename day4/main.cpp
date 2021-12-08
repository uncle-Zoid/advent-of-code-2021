#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;


struct BingoNumber
{
    bool isChecked = false;
    int value      = 0;
};

struct Bingo
{
    static const int N = 5;
    BingoNumber board[N][N];
    bool isWon = false;

    void push (int index, int value)
    {
        int x = index / N;
        int y = index % N;
        board[x][y].value = value;
        board[x][y].isChecked = false;
    }
    void print() const
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                auto &val = board[i][j];
                cout << setw(6) << setfill(' ') << left << (to_string(val.value) + (val.isChecked ? "*":""));
            }
            cout << endl;
        }
    }
    int score() const
    {
        int score = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                auto &val = board[i][j];
                if (val.isChecked == false)
                {
                    score += val.value;
                }
            }
        }
        return score;
    }

    void select (int value)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                auto &val = board[i][j];
                if (val.value == value)
                {
                    val.isChecked = true;
                }
            }
        }
    }

    bool findFullRow ()
    {
        if (isWon)
            return true;

        for (int i = 0; i < N; ++i)
        {
            int j = 1;
            auto &val1 = board[i][0];
            if (val1.isChecked)
            {
                for (; j < N; ++j)
                {
                    auto v = board[i][j];
                    if(!board[i][j].isChecked)
                        break;
                }
                if((isWon=(j == N)))
                {
                    break;
                }
            }
            auto val2 = board[0][i];
            if (val2.isChecked)
            {
                for (j=1; j < N; ++j)
                {
                    auto v = board[j][i];
                    if(!board[j][i].isChecked)
                        break;
                }
                if((isWon=(j == N)))
                {
                    break;
                }
            }

            if (isWon)
                break;
        }
        return isWon;
    }
};

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

    vector<int> order;
    vector <Bingo> bingos;

    getline(ifs, str);
    //1,2,3,
    size_t pos1 = 0;
    size_t pos2 = 0;
    do
    {
        pos1 = str.find(',', pos2);

        auto s = str.substr(pos2, pos1 - pos2);
        order.push_back(stoi(s, 0, 10));

        pos2 = pos1 + 1;
    } while (pos1 != string::npos);

    int num;
    while(ifs)
    {
        Bingo bingo;
        for (int i = 0; i < 25; ++i)
        {
            ifs >> num;
            if (!ifs)
            {
                break;
            }
            bingo.push(i, num);
        }
        if (!ifs)
        {
            break;
        }

        bingos.push_back(bingo);

        cout << "Board " << bingos.size() << endl;
        bingo.print();
        cout << endl << endl;;
    }

    cout << "PLAY" << endl << endl;;
    cout << "Pull: ";
    bool win = false;
    for (auto &o : order)
    {
        int i = 0;
        cout << "\n\nPull=" << o << ", " << endl;
        for (auto it = bingos.begin(); it != bingos.end(); )
        {
            it->select(o);
            ++i;
            if(it->findFullRow())
            {
                cout << "Board " << i << " won" << endl;
                it->print();

//                getchar();
//                if (count_if(bingos.begin(), bingos.end(), [](const Bingo &b){ return b.isWon;}) == int(bingos.size()))
                if (bingos.size() == 1)
                {
                    auto score = it->score();
                    cout << "you win!!!" << score << "\t" << score * o << endl;
                    win = true;
                    break;
                }
                it = bingos.erase(it);
            }
            else ++it;
        }

        if (win)
            break;
    }


    return 0;
}
