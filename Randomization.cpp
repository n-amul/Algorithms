#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

inline int sign(int x)
{
    return (x > 0) ? 1 : -1;
}

bool verify(vector<vector<int>> &clauses, vector<int> &res)
{
    int cnt = 0;

    for (size_t i = 0; i < clauses.size(); ++i)
    {
        if ((sign(clauses[i][0]) == res[abs(clauses[i][0]) - 1]) ||
            (sign(clauses[i][1]) == res[abs(clauses[i][1]) - 1]) ||
            (sign(clauses[i][2]) == res[abs(clauses[i][2]) - 1]))
        {
            cnt++;
        }
    }

    return (cnt * 8 >= clauses.size() * 7);
}

int main()
{
    int totalVariables, totalClauses;
    cin >> totalVariables >> totalClauses;

    vector<vector<int>> clauses;

    for (int i = 0; i < totalClauses; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        vector<int> clause = {x, y, z};
        clauses.push_back(clause);
    }

    vector<int> res(totalVariables, 0);
    srand(static_cast<unsigned>(time(NULL)));

    do
    {
        for (int i = 0; i < totalVariables; i++)
        {
            res[i] = (rand() % 2) * 2 - 1; //-1 or 1
        }
    } while (!verify(clauses, res));

    for (int i = 0; i < totalVariables; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}