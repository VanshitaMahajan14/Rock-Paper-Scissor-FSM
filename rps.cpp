#include <bits/stdc++.h>
using namespace std;
struct states
{
    char state;
    int r;
    int p;
    int s;
};

vector<states> play;

int flag = 0;
int co = 1;
struct node
{
    struct node *r;
    struct node *p;
    struct node *s;
    char self;
    int id;
};
typedef struct node *treenode;
int rcall = 0, pcall = 0, scall = 0;
map<vector<int>, struct node *> maps; // map of node and states in its set
vector<treenode> store;
struct node *makenode(char self) // make a node and return a pointer to it
{
    treenode node = (struct node *)malloc(sizeof(struct node));
    node->r = NULL;
    node->p = NULL;
    node->s = NULL;
    node->self = self;
    return node;
}
int vector_exists(vector<int> vec)
{
    if (maps.find(vec) != maps.end())
    {
        return 1; // key already exists
    }
    return 0;
}
void dfs(treenode node, vector<int> vec)
{
    flag = 0;
    store.push_back(node);
    char c;
    if (node->self == 'R')
        c = 'r';
    else if (node->self == 'P')
        c = 'p';
    else
        c = 's';
    int r = 0, p = 0, s = 0;

    vector<int> set1, set2, set3;
    char name1, name2, name3;
    treenode new1, new2, new3;
    rcall = 0, pcall = 0, scall = 0;
    int x;

    // cout << node->self << " ";

    // -------------ROCK ------------//  WHEN OPPONENT PLAYS ROCK

    for (int i = 0; i < play.size(); i++)
    {
        char st = play[i].state;
        int ind;
        if (st == 'R') // opp playing rock
        {
            if (c == 'r')
                ind = play[i].r;
            else if (c == 'p')
                ind = play[i].p;
            else
                ind = play[i].s;

            if (find(vec.begin(), vec.end(), (i + 1)) != vec.end()) // checking if there exists any state not present in parent node's set
            {
                flag = 1;
                set1.push_back(ind);
                if (play[ind - 1].state == 'R')
                    r++;
                else if (play[ind - 1].state == 'P')
                    p++;
                else
                    s++;
            }
        }
    }
    // cout << r << " " << p << " " << s << "\n";
    // cout << "rock set: ";

    // for (int i = 0; i < set1.size(); i++)
    //     cout << set1[i] << " ";
    // cout << "\n";
    if (flag == 0)
    {
        // cout << "rock is NULL\n";
        node->r = NULL;
        // cout << node->id << " ";
    }
    else
    {
        if (r >= p && r >= s)
            name1 = 'P';
        else if (p >= r && p >= s)
            name1 = 'S';
        else if (s >= p && s >= r)
            name1 = 'R';
        x = vector_exists(set1);
        if (x == 1)
        {
            // cout << "already exists" << endl;
            auto rep = maps.find(set1);
            node->r = rep->second;
            // cout << node->r->id << " ";
        }
        else
        {
            // cout << "new node" << endl;
            co++;
            new1 = makenode(name1);
            node->r = new1;
            maps.insert({set1, new1});
            node->r->id = co;
            rcall = 1;
            // cout << node->r->id << " ";
            dfs(node->r, set1);
        }
    }
    flag = 0;
    r = 0, p = 0, s = 0;

    //---------------PAPER -------------//  WHEN OPPONENT PLAYS PAPER
    for (int i = 0; i < play.size(); i++)
    {
        char st = play[i].state;
        int ind;
        if (st == 'P') // opp playing rock
        {
            if (c == 'r')
                ind = play[i].r;
            else if (c == 'p')
                ind = play[i].p;
            else
                ind = play[i].s;

            if (find(vec.begin(), vec.end(), (i + 1)) != vec.end()) // checking if there exists any state not present in parent node's set
            {
                flag = 1;
                set2.push_back(ind);
                if (play[ind - 1].state == 'R')
                    r++;
                else if (play[ind - 1].state == 'P')
                    p++;
                else
                    s++;
            }
        }
    }
    // cout << r << " " << p << " " << s << "\n";
    // cout << "paper set: ";
    // for (int i = 0; i < set2.size(); i++)
    //     cout << set2[i] << " ";
    // cout << "\n";
    sort(set2.begin(), set2.end());
    if (flag == 0)
    {
        // cout << "paper is NULL\n";
        node->p = NULL;
        // cout << node->id << " ";
    }
    else
    {
        if (r >= p && r >= s)
            name2 = 'P';
        else if (p >= r && p >= s)
            name2 = 'S';
        else if (s >= p && s >= r)
            name2 = 'R';
        // cout << name2 << " ";
        x = vector_exists(set2);
        if (x == 1)
        {
            // cout << "already exists" << endl;
            auto rep = maps.find(set2);
            node->p = rep->second;
            // cout << node->p->id << " ";
        }
        else
        {
            // cout << "new node" << endl;
            co++;
            new2 = makenode(name2);
            node->p = new2;
            maps.insert({set2, new2});
            node->p->id = co;
            pcall = 1;
            flag = 0;
            // cout << node->p->id << " ";
            dfs(node->p, set2);
        }
    }
    flag = 0;
    r = 0, p = 0, s = 0;

    //------------- SCISSORS -----------//  WHEN OPPONENT PLAYS SCISSORS

    for (int i = 0; i < play.size(); i++)
    {
        char st = play[i].state;
        int ind;
        if (st == 'S') // opp playing rock
        {
            if (c == 'r')
                ind = play[i].r;
            else if (c == 'p')
                ind = play[i].p;
            else
                ind = play[i].s;

            if (find(vec.begin(), vec.end(), (i + 1)) != vec.end()) // checking if there exists any state not present in parent node's set
            {
                flag = 1;
                set3.push_back(ind);
                if (play[ind - 1].state == 'R')
                    r++;
                else if (play[ind - 1].state == 'P')
                    p++;
                else
                    s++;
            }
        }
    }
    // cout << r << " " << p << " " << s << "\n";
    // cout << "scissor set: ";
    // for (int i = 0; i < set3.size(); i++)
    //     cout << set3[i] << " ";
    // cout << "\n";
    sort(set3.begin(), set3.end());
    if (flag == 0)
    {
        // cout << "scissors is NULL\n";
        node->s = NULL;
    }
    else
    {
        if (r >= p && r >= s)
            name3 = 'P';
        else if (p >= r && p >= s)
            name3 = 'S';
        else if (s >= p && s >= r)
            name3 = 'R';
        // cout << name3 << "\n";
        x = vector_exists(set3);
        if (x == 1)
        {
            // cout << "already exists" << endl;
            //  cout << "here\n";
            auto rep = maps.find(set3);
            node->s = rep->second;
            // cout<< node->s->id << " ";
        }
        else
        {
            // cout << "new node" << endl;
            co++;
            new3 = makenode(name3);
            node->s = new3;
            maps.insert({set3, new3});
            node->s->id = co;
            scall = 1;
            // cout << node->s->id << " ";
            dfs(node->s, set3);
        }
    }
    flag = 0;
}
int main()
{
    int n;
    cin >> n;
    states temp;
    int k = 0;
    int rock = 0, paper = 0, scissor = 0;
    while (k < n)
    {
        char st;
        int a, b, c;
        cin >> st >> a >> b >> c;
        temp.state = st;
        temp.r = a;
        temp.p = b;
        temp.s = c;
        play.push_back(temp);
        if (st == 'R')
            rock++;
        else if (st == 'P')
            paper++;
        else if (st == 'S')
            scissor++;
        k++;
    }

    char sel;
    int max, init;
    if (rock >= paper && rock >= scissor)
        max = 1; // rock
    else if (paper >= rock && paper >= scissor)
        max = 2; // paper
    else
        max = 3; // scissor
    init = (max < 3) ? max + 1 : 1;

    if (init == 1)
        sel = 'R';
    else if (init == 2)
        sel = 'P';
    else
        sel = 'S';

    vector<int> vals;
    for (int i = 1; i <= n; i++)
        vals.push_back(i);

    treenode node = (struct node *)malloc(sizeof(struct node));
    node->r = NULL;
    node->p = NULL;
    node->s = NULL;
    node->self = sel;
    node->id = 1;
    maps.insert({vals, node});

    dfs(node, vals);
    cout << store.size() << "\n";
    for (int i = 0; i < store.size(); i++)
    {
        cout << store[i]->self << " ";
        if (store[i]->r != NULL)
            cout << store[i]->r->id << " ";
        else
            cout << store[i]->id << " ";
        if (store[i]->p != NULL)
            cout << store[i]->p->id << " ";
        else
            cout << store[i]->id << " ";
        if (store[i]->s != NULL)
            cout << store[i]->s->id << " ";
        else
            cout << store[i]->id << " ";
        cout << "\n";
    }
    return 0;
}
