#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

class Player
{
public:
    int id;
    string name;
    int skill;
    int waitTime;

    Player(int i = 0, string n = "", int s = 0, int w = 0)
    {
        id = i;
        name = n;
        skill = s;
        waitTime = w;
    }
};

class AVLNode
{
public:
    int skill;
    Player player;
    AVLNode *left, *right;
    int height;

    AVLNode(Player p)
    {
        player = p;
        skill = p.skill;
        left = right = NULL;
        height = 1;
    }
};

class AVLTree
{
    int height(AVLNode *n) { return n ? n->height : 0; }
    int balanceFactor(AVLNode *n) { return n ? height(n->left) - height(n->right) : 0; }

    AVLNode *rightRotate(AVLNode *y)
    {
        AVLNode *x = y->left, *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode *leftRotate(AVLNode *x)
    {
        AVLNode *y = x->right, *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

public:
    AVLNode *root = NULL;

    AVLNode *insert(AVLNode *node, Player p)
    {
        if (!node)
            return new AVLNode(p);
        if (p.skill < node->skill)
            node->left = insert(node->left, p);
        else
            node->right = insert(node->right, p);

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && p.skill < node->left->skill)
            return rightRotate(node);
        if (balance < -1 && p.skill > node->right->skill)
            return leftRotate(node);
        if (balance > 1 && p.skill > node->left->skill)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && p.skill < node->right->skill)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void insertPlayer(Player p) { root = insert(root, p); }

    void inorder(AVLNode *node)
    {
        if (!node)
            return;
        inorder(node->left);
        cout << "  ID:" << node->player.id
             << "  Name:" << node->player.name
             << "  Skill:" << node->player.skill << "\n";
        inorder(node->right);
    }
};

class Graph
{
public:
    int V;
    vector<pair<int, int>> adj[100];

    Graph(int v) : V(v) {}

    void addEdge(int u, int v, int wt)
    {
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    void dijkstra(int src)
    {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty())
        {
            int node = pq.top().second, d = pq.top().first;
            pq.pop();
            for (auto edge : adj[node])
            {
                int next = edge.first, weight = edge.second;
                if (dist[next] > d + weight)
                {
                    dist[next] = d + weight;
                    pq.push({dist[next], next});
                }
            }
        }

        cout << "\n--- Minimum Latency from Server 0 ---\n";
        for (int i = 0; i < V; i++)
            cout << "  Server " << i << " : " << dist[i] << " ms\n";
    }
};
void separator(const string &title)
{
    cout << "\n========================================\n";
    cout << "  " << title << "\n";
    cout << "========================================\n";
}

int main()
{
    AVLTree rankIndex;
    queue<Player> waitingQueue;
    stack<Player> history;
    unordered_map<int, Player> playerLookup;
    priority_queue<pair<int, int>> fairnessHeap;
    vector<Player> players;
    Graph network(5);

    network.addEdge(0, 1, 20);
    network.addEdge(0, 2, 10);
    network.addEdge(1, 3, 15);
    network.addEdge(2, 3, 5);
    network.addEdge(3, 4, 12);

    vector<Player> samplePlayers = {
        Player(1, "Alice", 85, 30),
        Player(2, "Bob", 42, 60),
        Player(3, "Charlie", 73, 15),
        Player(4, "Diana", 91, 45),
        Player(5, "Eve", 58, 20),
        Player(6, "Frank", 66, 50),
    };

    separator("1. ADDING PLAYERS");
    for (auto &p : samplePlayers)
    {
        rankIndex.insertPlayer(p);
        waitingQueue.push(p);
        history.push(p);
        playerLookup[p.id] = p;
        fairnessHeap.push({p.waitTime, p.id});
        players.push_back(p);
        cout << "  Added -> ID:" << p.id
             << "  Name:" << p.name
             << "  Skill:" << p.skill
             << "  WaitTime:" << p.waitTime << "s\n";
    }

    separator("2. WAITING QUEUE (arrival order)");
    queue<Player> temp = waitingQueue;
    while (!temp.empty())
    {
        Player p = temp.front();
        temp.pop();
        cout << "  ID:" << p.id << "  " << p.name << "  Skill:" << p.skill << "\n";
    }

    separator("3. UNDO LAST ADDITION (stack)");
    if (!history.empty())
    {
        Player p = history.top();
        history.pop();
        waitingQueue.push(p);
        cout << "  Player '" << p.name << "' re-queued via undo.\n";
    }

    separator("4. PLAYER LOOKUP BY ID (hash map)");
    for (int id : {2, 4, 99})
    {
        if (playerLookup.count(id))
            cout << "  Found ID " << id << " -> " << playerLookup[id].name
                 << "  Skill:" << playerLookup[id].skill << "\n";
        else
            cout << "  ID " << id << " -> Not found.\n";
    }

    separator("5. PLAYERS SORTED BY SKILL (descending)");
    sort(players.begin(), players.end(), [](Player a, Player b)
         { return a.skill > b.skill; });
    for (auto &p : players)
        cout << "  " << p.name << "  Skill:" << p.skill << "\n";

    separator("6. AVL RANK INDEX (ascending inorder)");
    rankIndex.inorder(rankIndex.root);

    separator("7. FASTEST SERVER PATH (Dijkstra)");
    network.dijkstra(0);

    separator("8. FAIRNESS BALANCER (max-heap by wait time)");
    priority_queue<pair<int, int>> tempHeap = fairnessHeap;
    cout << "  Priority order (longest wait first):\n";
    int rank = 1;
    while (!tempHeap.empty())
    {
        pair<int, int> current = tempHeap.top();
        int wait = current.first;
        int id = current.second;

        tempHeap.pop();

        cout << "  #" << rank++ << "  ID:" << id
             << "  " << playerLookup[id].name
             << "  WaitTime:" << wait << "s\n";
    }
    cout << "  ArenaX simulation complete.\n";

    return 0;
}