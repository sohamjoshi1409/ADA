#include <iostream>
#include <vector>
using namespace std;

// Utility function to print the board
void printBoard(const vector<vector<int>> &board)
{
    int n = board.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << "\n";
    }
    cout << endl;
}

// Check if placing a queen at (row, col) is safe
bool isSafe(const vector<vector<int>> &board, int row, int col)
{
    int n = board.size();
    // Check this row on left side
    for (int j = 0; j < col; j++)
        if (board[row][j])
            return false;
    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    // Check lower diagonal on left side
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        if (board[i][j])
            return false;
    return true;
}

// Backtracking function
bool solveNQueens(vector<vector<int>> &board, int col)
{
    int n = board.size();
    if (col >= n)
    {
        printBoard(board); // print the solution
        return true;
    }
    bool res = false;
    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;
            res = solveNQueens(board, col + 1) || res;
            board[i][col] = 0; // Backtrack
        }
    }
    return res;
}

int main()
{
    int n;
    cout << "Enter number of queens: ";
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (!solveNQueens(board, 0))
        cout << "No solution exists.\n";
    return 0;
}
