#include <ostream>
using namespace std;

template<typename E>
struct Triple
{
    int row;
    int col;
    E value;

    void operator = (Triple& triple)
    {
        row = triple.row;
        col = triple.col;
        value = triple.value;
    }

    friend ostream& operator << (ostream& out, Triple<int>& t);
};

ostream& operator << (ostream& out, Triple<int>& t)
{
    out << t.row << " " << t.col << " " << t.value << endl;
    return out;
}