#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Sudoku {
private:
    int board[9][9];

public:
    Sudoku();
    void display();
    bool isSafe(int row, int col, int num);
    bool solve();
    void generatePuzzle(int difficulty = 30); // Number of cells to remove. Change it to change difficulty.
    void setBoard(int input[9][9]);
    void fillBox(int board[9][9], int row, int col);
	bool isUnusedInBox(int board[9][9], int rowStart, int colStart, int num);
};

Sudoku::Sudoku() {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j] = 0;
}

void Sudoku::display() {
    std::cout << "+-------+-------+-------+\n";
    for (int i = 0; i < 9; i++) {
        std::cout << "| ";
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0)
                std::cout << ". ";
            else
                std::cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0)
                std::cout << "| ";
        }
        std::cout << "\n";
        if ((i + 1) % 3 == 0)
            std::cout << "+-------+-------+-------+\n";
    }
}

bool Sudoku::isSafe(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool Sudoku::solve() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(row, col, num)) {
                        board[row][col] = num;
                        if (solve()) return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void Sudoku::generatePuzzle(int difficulty) {
    srand(time(0));
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j] = 0;

    fillBox(board, 0, 0);
    fillBox(board, 3, 3);
    fillBox(board, 6, 6);

    solve();

    int cellsRemoved = difficulty;
    while (cellsRemoved > 0) {
        int i = rand() % 9;
        int j = rand() % 9;
        if (board[i][j] != 0) {
            board[i][j] = 0;
            cellsRemoved--;
        }
    }
}

void Sudoku::fillBox(int board[9][9], int row, int col) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num;
            do {
                num = rand() % 9 + 1;
            } while (!isUnusedInBox(board, row, col, num));
            board[row + i][col + j] = num;
        }
    }
}

bool Sudoku::isUnusedInBox(int board[9][9], int rowStart, int colStart, int num) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[rowStart + i][colStart + j] == num)
                return false;
    return true;
}

void inputCustomPuzzle(Sudoku &puzzle) {
    cout << "Enter your puzzle (9 lines of 9 digits, use 0 for blanks):\n";
    int temp[9][9];
    for (int i = 0; i < 9; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < 9; j++) {
            temp[i][j] = line[j] - '0';
        }
    }
    puzzle.setBoard(temp);
    cout << "Custom puzzle loaded.\n";
}

void Sudoku::setBoard(int input[9][9]) {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j] = input[i][j];
}

int main() {
    Sudoku puzzle;
    int choice;
    bool running = true;

    while (running) {
        cout << "\n===== Sudoku Solver Menu =====\n";
        cout << "1. Generate New Puzzle\n";
        cout << "2. Input Custom Puzzle\n";
        cout << "3. Solve Puzzle\n";
        cout << "4. Display Current Puzzle\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                puzzle.generatePuzzle(40);
                cout << "New puzzle generated.\n";
                puzzle.display();
                break;
            case 2:
                inputCustomPuzzle(puzzle);
                break;
            case 3:
                if (puzzle.solve()) {
                    cout << "Puzzle solved successfully!\n";
                    puzzle.display();
                } else {
                    cout << "No solution found.\n";
                }
                break;
            case 4:
                puzzle.display();
                break;
            case 5:
                running = false;
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}


