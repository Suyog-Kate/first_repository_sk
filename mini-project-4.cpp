#include <iostream>
#include <vector>

using namespace std;

class NQueens {
    int N;
    vector<int> queens; // queens[row] = col position of queen in that row
    vector<bool> cols;  // columns occupied
    vector<bool> diag1; // major diagonal occupied (row + col)
    vector<bool> diag2; // minor diagonal occupied (row - col + N - 1)
    bool foundSolution;

public:
    NQueens(int n) : N(n), queens(n, -1), cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false), foundSolution(false) {}

    void printBoard() {
        cout << "Solution:\n";
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (queens[r] == c) cout << " Q ";
                else cout << " . ";
            }
            cout << "\n";
        }
    }

    // Backtracking + Branch and Bound (using cols, diag1, diag2 arrays to prune)
    bool solve(int row = 0) {
        if (row == N) {
            foundSolution = true;
            printBoard();
            return true; // return true if you want only 1 solution
            // return false; // uncomment to find all solutions
        }

        for (int c = 0; c < N; c++) {
            if (isSafe(row, c)) {
                placeQueen(row, c);
                if (solve(row + 1))
                    return true; // stop at first solution
                removeQueen(row, c);
            }
        }
        return false;
    }

private:
    bool isSafe(int row, int col) {
        // Branch & Bound pruning - check columns and diagonals
        return !cols[col] && !diag1[row + col] && !diag2[row - col + N - 1];
    }

    void placeQueen(int row, int col) {
        queens[row] = col;
        cols[col] = true;
        diag1[row + col] = true;
        diag2[row - col + N - 1] = true;
    }

    void removeQueen(int row, int col) {
        queens[row] = -1;
        cols[col] = false;
        diag1[row + col] = false;
        diag2[row - col + N - 1] = false;
    }
};

int main() {
    int N;
    cout << "Enter size of board (N for N-Queens): ";
    cin >> N;

    NQueens solver(N);
    if (!solver.solve()) {
        cout << "No solution exists for N = " << N << "\n";
    }

    return 0;
}
