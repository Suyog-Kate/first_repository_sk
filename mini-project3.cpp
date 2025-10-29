#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

struct Move {
    int row, col;
};

void printBoard(const vector<vector<char>>& board) {
    cout << "\n";
    cout << "  0   1   2\n";  // Column numbers for clarity
    for (int i = 0; i < 3; i++) {
        cout << i << " "; // Row number for clarity
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << " ---+---+---\n";
    }
    cout << "\n";
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board)
        for (char c : row)
            if (c == EMPTY)
                return true;
    return false;
}

int evaluate(const vector<vector<char>>& board) {
    // Check rows and columns for victory
    for (int i = 0; i < 3; i++) {
        // Rows
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == COMPUTER)
                return +10;
            else if (board[i][0] == HUMAN)
                return -10;
        }
        // Columns
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            if (board[0][i] == COMPUTER)
                return +10;
            else if (board[0][i] == HUMAN)
                return -10;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER)
            return +10;
        else if (board[0][0] == HUMAN)
            return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER)
            return +10;
        else if (board[0][2] == HUMAN)
            return -10;
    }

    // No winner
    return 0;
}

int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    // If AI won
    if (score == 10)
        return score - depth; // Prefer faster wins

    // If human won
    if (score == -10)
        return score + depth; // Prefer slower losses

    // If no moves left - draw
    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    int val = minimax(board, depth + 1, false, alpha, beta);
                    best = max(best, val);
                    alpha = max(alpha, best);
                    board[i][j] = EMPTY;

                    if (beta <= alpha)
                        return best;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    int val = minimax(board, depth + 1, true, alpha, beta);
                    best = min(best, val);
                    beta = min(beta, best);
                    board[i][j] = EMPTY;

                    if (beta <= alpha)
                        return best;
                }
            }
        }
        return best;
    }
}

Move findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    Move bestMove{-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

char checkGameOver(const vector<vector<char>>& board) {
    int score = evaluate(board);
    if (score == 10) return COMPUTER;
    else if (score == -10) return HUMAN;
    else if (!isMovesLeft(board)) return 'D'; // Draw
    return 'N'; // Not finished
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    cout << "Tic-Tac-Toe: You (X) vs Computer (O)\n";
    cout << "Enter your move as row and column numbers (0-based index)\n";

    printBoard(board);

    while (true) {
        int r, c;
        // Human move
        while (true) {
            cout << "Your move (row col): ";
            if (!(cin >> r >> c)) {
                // Clear error state and ignore bad input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter two numbers (row and col).\n";
                continue;
            }
            if (r >= 0 && r < 3 && c >= 0 && c < 3 && board[r][c] == EMPTY)
                break;
            cout << "Invalid move, try again.\n";
        }
        board[r][c] = HUMAN;

        printBoard(board);

        char status = checkGameOver(board);
        if (status == HUMAN) {
            cout << "You win! Congratulations!\n";
            break;
        } else if (status == 'D') {
            cout << "It's a draw!\n";
            break;
        }

        // Computer move
        cout << "Computer is making a move...\n";
        Move bestMove = findBestMove(board);
        board[bestMove.row][bestMove.col] = COMPUTER;

        printBoard(board);

        status = checkGameOver(board);
        if (status == COMPUTER) {
            cout << "Computer wins! Better luck next time.\n";
            break;
        } else if (status == 'D') {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}
