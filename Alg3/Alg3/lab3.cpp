#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
#include "list_of_lists.h"

using namespace std;

class OrGraph
{
    Adj_List* adj_list;
    bool* visited;
    int* weights;

   

    void find_shortest_way(Adj_List_Elem* Beg)
    {
        Adj_List_Elem* Cur1 = Beg;
        Adj_List_Elem* Cur2;
        Adj_List_Elem* Next = nullptr;
        int min_weight, i;

        while (Cur1)
        {
            step(Cur1, adj_list->get_index_of(Cur1->name));

            Cur2 = adj_list->at(0);
            min_weight = INT_MAX;
            Next = nullptr;
            for (i = 0; Cur2; i++)
            {
                if (!visited[i])
                {
                    if (min_weight > weights[i])
                    {
                        min_weight = weights[i];
                        Next = Cur2;
                    }
                }
                Cur2 = Cur2->next;
            }
            Cur1 = Next;
        }
    }

   

    bool string_working(ifstream* input)
    {
        string cur;
        getline(*input, cur);
        if (cur.empty())
            return 0;

        size_t p1 = 0, p2 = 0;
        string name1, name2, rib;

        for (int i = 0; i < cur.length(); i++)
        {
            if (cur[i] == ';')
            {
                if (p1 == 0)
                    p1 = i;
                else if (p2 == 0)
                    p2 = i;
                else
                    return 0;
            }
        }
        if (p1 == 0 || p2 == 0)
            return 0;

        rib = cur.substr(p2 + 1);
        cur.erase(p2);
        name2 = cur.substr(p1 + 1);
        cur.erase(p1);
        name1 = cur;

        if (!crt_rib(name1, name2, rib))
            return 0;
        return 1;
    }
    void step(Adj_List_Elem* E, int index_of_E)
    {
        ElemL2* Cur = E->inf->at(0);
        while (Cur)
        {
            if (!visited[Cur->inf])
            {
                if (weights[Cur->inf] > Cur->key + weights[index_of_E])
                    weights[Cur->inf] = Cur->key + weights[index_of_E];
            }
            Cur = Cur->next;
        }
        visited[index_of_E] = 1;
    }
    void input(string filename)
    {
        ifstream input;
        input.open(filename);
        if (!input.is_open())
            throw runtime_error("Could not open file " + filename);
        while (!input.eof())
        {
            if (!string_working(&input))
            {
                input.close();
                delete adj_list;
                throw invalid_argument("Incorrect input");
            }
        }
        input.close();
    }
    bool crt_rib(string name1, string name2, string rib)
    {
        if (rib.empty() || name2.empty())
            return 0;

        int weight;
        try { weight = stoi(rib); }
        catch (exception) { return 0; }

        return adj_list->create_rib(name1, name2, weight);
    }
public:

    OrGraph(string filename)
    {
        adj_list = new Adj_List;
        input(filename);

        int len = adj_list->get_size();

        visited = new bool[len];
        weights = new int[len];
        for (int i = 0; i < len; i++)
        {
            visited[i] = 0;
            weights[i] = INT_MAX;
        }
    }

    int get_shortest_way(string from, string to)
    {
        Adj_List_Elem* F = adj_list->find(from);

        if (!F || !adj_list->find(to))
            throw invalid_argument("There are no such elements");

        weights[adj_list->get_index_of(from)] = 0;

        find_shortest_way(F);

        int ans = weights[adj_list->get_index_of(to)];
        for (int i = 0; i < adj_list->get_size(); i++)
        {
            visited[i] = 0;
            weights[i] = INT_MAX;
        }

        return ans;
    }

    ~OrGraph()
    {
        delete adj_list;
        delete visited;
        delete weights;
    }
};

int main()
{
    string filename, to, from;
    cout << "Enter name of file:\n";
    getline(cin, filename);
    cout << "Enter start position:\n";
    getline(cin, from);
    cout << "Enter destination:\n";
    getline(cin, to);
    try
    {
        OrGraph G(filename);
        int ans = G.get_shortest_way(from, to);
        if (ans == INT_MAX)
            cout << "There is no way from " << from << " to " << to << endl;
        else
            cout << "Shortest way from " << from << " to " << to << " is " << ans << endl;
    }
    catch (exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}
