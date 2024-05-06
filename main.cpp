#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* parent;
    int matrix[3][3];
    int x, y;
    int h, g, f;
};

Node* newNode(int matrix[3][3], int x, int y, int newX, int newY, int h, int g, Node* parent) {
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

int misplacedHeur(int init[3][3], int goal[3][3]) {
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

int euclideanHeur(int init[3][3], int goal[3][3]) {
    double ret = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(init[i][j] != 0)
                for(int k = 0; k < 3; k++)
                    for(int l = 0; l < 3; l++)
                        if(init[i][j] == goal[k][l])
                            ret += sqrt(pow(i - k, 2) + pow(j - l, 2));
    return ret;
}

void printMatrix(int matrix[3][3])
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void printPath(Node* node)
{
    if(node == NULL)
        return;
    printPath(node->parent);
    printMatrix(node->matrix);
	printf("g = %d and h = %d and f = %d", node->g, node->h, node->f);
    printf("\n\n");
}

int inBounds(int x, int y) {
    return ((x >= 0) && (x < 3) && (y >= 0) && (y < 3));
}

bool inSet(Node* a, vector<Node*> b) {
    for(int i = 0; i < b.size(); i++)
    if(misplacedHeur(a->matrix, b[i]->matrix) == 0)
        return true;
    return false;
}

bool smallestF (Node* a, Node* b) {
    return ((a->f) < (b->f));
}

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

void solve(int init[3][3], int x, int y, int goal[3][3], int heur, int &qSize, int &nodesExp) {
    vector<Node*> frontier;
    vector<Node*> explored;
    Node* current;
    int heuristic;

    if(heur == 1)
        heuristic = 0;
    else if(heur == 2)
        heuristic = misplacedHeur(init, goal);
    else if(heur == 3)
        heuristic = euclideanHeur(init, goal);

    Node* node = newNode(init, x, y, x, y, heuristic, 0, NULL);
    node->f = node->h + node->g;
    frontier.push_back(node);
    qSize = 1;

    while(!frontier.empty()) {
        if(qSize < frontier.size())
			qSize = frontier.size();
        sort(frontier.begin(), frontier.end(), smallestF);
        current = frontier[0];

        if(misplacedHeur(current->matrix, goal) == 0) {
            printPath(current);
            return;
        }

        frontier.erase(frontier.begin());
        explored.push_back(current);
        nodesExp++;

        for(int i = 0; i < 4; i++) {
            if(inBounds(current->x + row[i], current->y + col[i])) {
                Node* child = newNode(current->matrix, current->x, current->y, current->x + row[i], current->y + col[i], current->h, current->g + 1, current);

                if(heur == 1)
                    child-> h = 0;
                else if(heur == 2)
                    child->h = misplacedHeur(child->matrix, goal);
                else if(heur == 3)
                    child->h = euclideanHeur(child->matrix, goal);
                
                child->f = child->h + child->g;
                if(!inSet(child, frontier) && !inSet(child, explored))
                    frontier.push_back(child);
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
        {1, 0, 3},
        {4, 2, 6},
        {7, 5, 8}
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

    int qSize = 0;
    int nodesExp = 0;
    if((heur == 1) || (heur == 2) || (heur == 3)) {
        solve(init, x, y, goal, heur, qSize, nodesExp);
	    printf("Max queue size: %d\n", qSize);
        printf("Nodes expanded: %d\n", nodesExp);
    }
    else
        cout << "Invalid input" << endl;
    
    return 0;
}
