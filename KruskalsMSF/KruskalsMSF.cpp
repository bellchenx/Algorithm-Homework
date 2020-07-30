#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

// Edge Struct
struct Edge
{
    int vi, vj, w;
};

// Quick Sort Comparison Function
int EdgeCMP(const void *a, const void *b)
{
    const Edge *a_cast = (const Edge *)a;
    const Edge *b_cast = (const Edge *)b;
    return a_cast->w - b_cast->w;
}

// Disjoint Set (Union-Find) Impletation
class DisjointSetOfGraph
{

    int *height;      // Height of Trees
    int *parent;      // Parent Node of each Node
    int maxNumOfItem; // Maxmum Num. of Items
    int n;            // Current Num. of Item

public:
    /* 
        Constructor of Disjoint Set
        args
            numOfItem (int): number of total item
    */
    DisjointSetOfGraph(int maxNumOfItem)
    {
        height = new int[maxNumOfItem];
        parent = new int[maxNumOfItem];
        this->maxNumOfItem = maxNumOfItem;
        this->n = 0;
        // Initialize Parents
        for (int i = 0; i < maxNumOfItem; i++)
        {
            parent[i] = i; // Make Parent Itself
        }
    }

    /* 
        Find the root node of given item.
        args
            numOfItem (int): number of total item
    */
    int find(int nodeNum)
    {
        if (parent[nodeNum] != nodeNum)
        {
            parent[nodeNum] = find(parent[nodeNum]);
        }
        return parent[nodeNum];
    }

    /* 
        Find the root node of given item.
        args
            m (int): first node to union
            n (int): second node to union
        return
            true: they've already in same set
            false: they were not in same set but now is
    */
    bool unionSet(int m, int n)
    {
        int rootM = find(m);
        int rootN = find(n);

        // Check whether they are in the same tree
        if (rootM == rootN)
        {
            return true;
        }

        // Union shorter tree to higher tree.
        if (height[rootM] > height[rootN])
        {
            parent[rootN] = rootM;
        }
        else if (height[rootM] < height[rootN])
        {
            parent[rootM] = rootN;
        }
        else
        {
            parent[rootM] = rootN;
            height[rootN]++;
        }
        return false;
    }
};

/* 
    Main function.
    args
        arg(int): number of args from command line
        argv[](char*): the pointer of args array
    return 
        return value to system
*/
int main(int arg, char *argv[])
{
    int n; // number of vertices
    FILE *input = fopen(argv[1], "r");
    fscanf(input, "%d", &n);
    vector<Edge> inputBuffer;

    //Input Graph
    int vi, vj, w;
    while(fscanf(input, "%d,%d:%d\n", &vi, &vj, &w) != -1)
    {
        Edge temp;
        temp.vi = vi;
        temp.vj = vj;
        temp.w = w;
        inputBuffer.push_back(temp);
    }

    // Initialization
    int numOfEdge = inputBuffer.size();
    Edge *graph = &inputBuffer[0];
    DisjointSetOfGraph ds_graph(n);

    // Sort Edge Length
    qsort(graph, numOfEdge, sizeof(struct Edge), EdgeCMP);
    int count = 0;
    while (count < numOfEdge)
    {
        Edge e = graph[count];
        if (ds_graph.find(e.vi) != ds_graph.find(e.vj))
        {
            printf("%d %d:%d\n", e.vi, e.vj, e.w);
            ds_graph.unionSet(e.vi, e.vj);
        }
        count ++;
    }
    return 0;
}