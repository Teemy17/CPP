#include <iostream>
#include <vector>
#include <list>
using namespace std;

void remove_negative_vec(vector<double> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] < 0)
        {
            vec.erase(vec.begin() + i);
            i--;
        }
    }
}

void remove_negative_lst(list<double> &lst)
{
    for (auto it = lst.begin(); it != lst.end();)
    {
        if (*it < 0)
        {
            it = lst.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

int main()
{
    vector<double> vec = {0.8, -5.1, 1.6, -6.5, -10.5};
    cout << "Original vector: ";
    for (double num : vec)
    {
        cout << num << " ";
    }
    cout << endl;

    remove_negative_vec(vec);
    cout << "After removing negative numbers: ";
    for (double num : vec)
    {
        cout << num << " ";
    }
    cout << endl;

    list<double> lst = {0.8, -5.1, 1.6, -6.5, -10.5};
    cout << "Original list: ";
    for (double num : lst)
    {
        cout << num << " ";
    }
    cout << endl;

    remove_negative_lst(lst);
    cout << "After removing negative numbers: ";
    for (double num : lst)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}