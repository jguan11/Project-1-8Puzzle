#ifndef OPERATORS_H_
#define OPERATORS_H_
#include <iostream>
using namespace std;


struct Node
{
    Node* parent;
    int matrix[3][3];
    int x, y;
    int h, g, f;
};

Node* Up(Node* n)
{   
    for (int i=0;i<3;i++)
    {
        if (n->matrix[0][i] == 0)
            return n;
    }
    
    int row;
    int column;

    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (n->matrix[i][j]==0)
            {
                row = i;
                column = j;
            }
        }
    }

   n->matrix[row][column] = n->matrix[row-1][column];
   n->matrix[row-1][column] = 0;

    return n;
}

Node* Down(Node* n)
{   
    for (int i=0;i<3;i++)
    {
        if (n->matrix[2][i] == 0)
            return n;
    }
    
    int row;
    int column;

    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (n->matrix[i][j]==0)
            {
                row = i;
                column = j;
            }
        }
    }

   n->matrix[row][column] = n->matrix[row+1][column];
   n->matrix[row+1][column] = 0;

    return n;
}

Node* Left(Node* n)
{   
    for (int i=0;i<3;i++)
    {
        if (n->matrix[i][0] == 0)
            return n;
    }
    
    int row;
    int column;

    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (n->matrix[i][j]==0)
            {
                row = i;
                column = j;
            }
        }
    }

   n->matrix[row][column] = n->matrix[row][column-1];
   n->matrix[row][column-1] = 0;

    return n;
}

Node* Right(Node* n)
{   
    for (int i=0;i<3;i++)
    {
        if (n->matrix[i][2] == 0)
            return n;
    }
    
    int row;
    int column;

    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            if (n->matrix[i][j]==0)
            {
                row = i;
                column = j;
            }
        }
    }

   n->matrix[row][column] = n->matrix[row][column+1];
   n->matrix[row][column+1] = 0;

    return n;
}

#endif