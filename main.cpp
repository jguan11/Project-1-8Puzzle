<<<<<<< HEAD
/* 
    1) Problem Class Implementation
    2) A* Search Implementation
    3) Puzzle State Represenation
    4) Testing and Debugging
    5) Integration and Main Program (GUI)
*/
=======
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node* parent;
    int matrix[3][3];
    int x, y;
    int h, g, f;
};

Node* newNode(int matrix[3][3], int x, int y, int newX, int newY, int h, int g, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->matrix, matrix, sizeof node->matrix);
    swap(node->matrix[x][y], node->matrix[newX][newY]);
    node->h = h;
    node->g = g;
    node->f = node->h + node->g;
    node->x = newX;
    node->y = newY;
    return node;
}

int misplacedHeur(int init[3][3], int goal[3][3])
{
    int ret = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++) {
	  	    if(init[i][j] == 0)
		        continue;
            if(init[i][j] != goal[i][j])
                ret++;
	    }
    return ret;
}

int manhattanHeur(int init[3][3], int goal[3][3]) {
	int ret = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
	  	    if(init[i][j] != 0)
        	    for(int k = 0; k < 3; k++)
            	    for(int l = 0; l < 3; l++)
                	    if(init[i][j] == goal[k][l])
                    	    ret += abs(i - k) + abs(j - l);
    return ret;
}

void printMatrix(int matrix[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void printPath(Node* node)
{
    if (node == NULL)
        return;
    printPath(node->parent);
    printMatrix(node->matrix);
	printf("h = %d and g = %d and f = %d", node->h, node->g, node->f);
    printf("\n\n");
}

int inBounds(int x, int y)
{
    return (x >= 0 && x < 3 && y >= 0 && y < 3);
}

bool smallestF(Node* a, Node* b) {
  return a->f < b->f;
}

int qSize = 0;
int nodesExp = 0;
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

void Astar(int init[3][3], int x, int y, int goal[3][3], int heur)
{
    vector<Node*> openset;
    vector<Node*> closedset;
    vector<Node*>::iterator it;
    Node* current;

    int heuristic;
    if(heur == 2) {
        heuristic = misplacedHeur(init, goal);
    }
    else if(heur == 3) {
        heuristic = manhattanHeur(init, goal);
    }

    Node* node = newNode(init, x, y, x, y, heuristic, 0, NULL);
    openset.push_back(node);
    qSize = openset.size();

    while (!openset.empty())
    {
        sort(openset.begin(), openset.end(), smallestF);
        current = openset[0];

        if (current->h == 0)
        {
            printPath(current);
            return;
        }

        openset.erase(openset.begin());
        closedset.push_back(current);
        if(qSize < openset.size())
			qSize = openset.size();
        nodesExp++;

        for (int i = 0; i < 4; i++)
        {
            if (inBounds(current->x + row[i], current->y + col[i]))
            {
                Node* child = newNode(current->matrix, current->x,
                              current->y, current->x + row[i],
                              current->y + col[i],
                              heuristic, current->g + 1, current);

                if(heur == 2)
                    child->h = misplacedHeur(child->matrix, goal);
                else if(heur == 3)
                    child->h = manhattanHeur(child->matrix, goal);
                
                child->f = child->h + child->g;
                it = find(openset.begin(), openset.end(), child);
                if(it == openset.end())
                    openset.push_back(child);
            }
        }
    }
}

int main()
{
    int heur, x, y;
    cout << "Type 1 for Uniformed Cost Search, 2 for Misplaced Tiles, and 3 for Euclidean Distance... ";
    cin >> heur;
	cout << endl;

	/*
    //Trivial
    int init[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    //Very Easy
    int init[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8}
    };
    //Easy
    int init[3][3] =
    {
        {1, 2, 0},
        {4, 5, 3},
        {7, 8, 6}
    };
    //Doable
    int init[3][3] =
    {
        {0, 1, 2},
        {4, 5, 3},
        {7, 8, 6}
    };
    //Oh Boy
    int init[3][3] =
    {
        {8, 7, 1},
        {6, 0, 2},
        {5, 4, 3}
    };
    //Impossible
    int init[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {8, 7, 0}
    };
    */

    int init[3][3] =
    {
        {8, 7, 1},
        {6, 0, 2},
        {5, 4, 3}
    };

    int goal[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(init[i][j] == 0) {
				x = i;
				y = j;
				break;
			}
		}
	}
 
    Astar(init, x, y, goal, heur);
	printf("Max queue size: %d\n", qSize);
    printf("Nodes expanded: %d\n", nodesExp);

    return 0;
}
>>>>>>> 706bc9442ae1987ee98f010b06e2f4a7413d4d93
