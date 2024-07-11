#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

#define hardspaces 40
#define hardmaxguess 50
#define mediumspaces 20
#define mediummaxguess 30
#define easymaxguess 20
using namespace std;


class Board {
public:
    int grid[3][3] = {
                {4,9,2},
                {3,5,7},
                {8,1,6}
    };
    void display() {

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (c == 3 || c == 6)
                    cout << " | ";
                cout << grid[r][c] << " ";
            }
            if (r == 2 || r == 5) {
                cout << endl;
                for (int i = 0; i < 3; i++)
                    cout << "---";
            }

            cout << endl;

        }
    }
};

class Tips : public Board {
public:
    Board b;
    int c, d;
    void display() {
        cout << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Alrighty! Here are the controls on how to play our Sudoku game!\n" << endl;
        cout << "You will be presented with a board that is either\na)Easy\tb)Medium\tc)Hard!\nYou get to choose which one you want to play!" << endl;
        cout << "All three boards are 9x9, the only difference between them being the number of guesses and the number of missing spaces in the board!\nFor example a Hard Mode Board has 30/81 missing spaces with only 50 guesses!" << endl;
        cout << "You have to make sure you finish the board in the number of guesses given - otherwise you lose :(\n" << endl;
        cout << "So! How do we navigate the board?\nLet's summon up the simple 3x3 board to help you navigate!\n" << endl;
        system("PAUSE");
        system("CLS");
        b.display();
        cout << endl;
        cout << "The rows and coloumns on the board can be navigated with co-ordinates! The co-ordinates of the axises starts from 0-2 in a 3x3 board!\nIn a 9x9 board they range from 0-8" << endl;
        cout << "As an example we take the number '3' on the board ... It's row number is Row: 1 and it's column number is Column:0\n" << endl;
        cout << "As a little test! Tell me what row and column number does the number '2' have on the board?" << endl;
        cin >> c;
        cout << endl;
        cin >> d;
        if (c == 0 && d == 2) {
            cout << "Thats correct! I'm proud of you!" << endl;
        }
        else {
            cout << "Thats incorrect! The answer is Row:0 and Column:2! I hope you understood it better now!" << endl;
        }
        cout << "After Navigation, the next control I'll tell you some simple tips!\n" << endl;
        cout << "1. In order to exit the game you just need to input '-1' in the row and column.\n" << endl;
        cout << "2. Another thing to keep in mind is that the empty spaces in the grid is represented by the number '0'!\n" << endl;
        cout << "That's all you need to know about the controls about the game! We hope you have fun!" << endl;
        system("PAUSE");
        system("CLS");
    }

};


class Tutorial : public Board, virtual public Tips {
public:
    Tips tt;
    Board b;
    string name;
    Tutorial() {}
    Tutorial(string a) {
        name = a;
    }
    void sudoku() {
        cout << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Hi! " << name << " I'll be telling you the basics of playing Sudoku today <3" << endl;
        cout << "Okay, so first things first. The game is played on a 9x9 grid\nWhich is like a big square made up of 9 smaller squares. Each of those smaller squares is a 3x3 grid." << endl;
        cout << "Here's what a basic 3x3 looks like!: " << endl;
        b.display();
        cout << endl;
        cout << "\nThe goal of the game is to fill in all the squares with numbers from 1 to 9.\nBut, there's a catch! You can't use the same number twice in any row, column, or 3x3 grid." << endl;
        cout << "Don't worry, though! The game will give you some numbers to start with, so you're not starting from scratch." << endl;
        cout << "\nTo solve the puzzle, you have to figure out which numbers go where by using logic.\nDon't just randomly guess number though - that won't get you anywhere!" << endl;
        cout << "Start by analyzing the numbers already filled! That way you can see which ones are missing :o" << endl;
        cout << "Then, you start filling in the empty squares one by one.\nTry to think about which numbers could possibly fit in each square based on what's already in the row, column, & the grid." << endl;
        cout << "As you get better at the game, you'll start noticing patterns! & soon you'll be able to solve the grids in no time!" << endl;
        cout << "\n\nPlaying Sudoku feels like as if youre cracking a secret code! The more you practice the better you will get at it!\nI hope you have tonnes of fun!" << endl;
        cout << "And now I'll tell you the controls on how to play our Sudoku!" << endl;

        system("PAUSE");
        system("CLS");
        tt.display();
    }
};



class Sudoku {
public:
    fstream file;
    int guessleft;
    int correctguess = 0;
    //default table of dynamic size generated
    int grid[9][9];
    int game[9][9];
    int size = 9;
    int maxguess;
    int spaces;
    float newscore = 0;
    //assign virtual functions for all modes
    virtual void boardgeneration() = 0;
    virtual void settotalguess() = 0;


    //decrementing number of guesses
    void guessleftt() {
        guessleft--;

    }
    int getguess() {
        return guessleft;
    }
    //game over
    int gameover(int a) {
        if (a == 0) {
            cout << "\n\nGame Over!!!" << endl;
            cout << "Solved Table:" << endl;
            sudokuGrid();
            return 0;
        }
        else {
            return 1;
        }

    }
    //check game over conditions a: row b:col c:guesses d:correct ans
    int checkgameover(int a, int b) {
        if (a == -1 && b == -1 || guessleft == 0) {
            gameover(0);
            return 0;
        }
        else if (correctguess == spaces) {
            cout << "\n\nYou Win!! Well Played:)" << endl;
            return 0;
        }
        else {
            return 1;
        }
    }
    bool isPresentInCol(int col, int num) { //check whether num is present in col or not
        for (int row = 0; row < size; row++)
            if (grid[row][col] == num)
                return true;
        return false;
    }
    bool isPresentInRow(int row, int num) { //check whether num is present in row or not
        for (int col = 0; col < size; col++)
            if (grid[row][col] == num)
                return true;
        return false;
    }
    bool isPresentInBox(int boxStartRow, int boxStartCol, int num) {
        //check whether num is present in 3x3 box or not
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;
        return false;
    }

    void sudokuGrid() { //print the sudoku grid after solve
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (col == 3 || col == 6)
                    cout << " | ";
                cout << grid[row][col] << " ";
            }
            if (row == 2 || row == 5) {
                cout << endl;
                for (int i = 0; i < size; i++)
                    cout << "---";
            }

            cout << endl;

        }
    }

    bool findEmptyPlace(int& row, int& col) { //get empty location and update row and column
        for (row = 0; row < size; row++)
            for (col = 0; col < size; col++)
                if (grid[row][col] == 0) //marked with 0 is empty
                    return true;
        return false;
    }
    bool isValidPlace(int row, int col, int num) {
        //when item not found in col, row and current 3x3 box
        return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3,
            col - col % 3, num);
    }
    bool solveSudoku() {
        int row, col;
        if (!findEmptyPlace(row, col))
            return true; //when all places are filled
        for (int num = 1; num <= 9; num++) { //valid numbers are 1 - 9
            if (isValidPlace(row, col, num)) { //check validation, if yes, put the number in the grid
                grid[row][col] = num;
                if (solveSudoku()) //recursively go for other rooms in the grid
                    return true;
                grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
            }
        }
        return false;
    }
    void checkvalue(int a, int b, int c) {
        guessleftt();
        if (grid[a][b] == c && game[a][b] == 0) {
            cout << "Value guessed correctly." << endl;
            correctguess++;
            game[a][b] = c;
            system("PAUSE");
            cout << "Press any key to continue......." << endl;
            system("CLS");
            displayupdatedgame();

        }
        else if (game[a][b] == 0) {
            cout << "Incorrect guess. Try Again." << endl;
            system("PAUSE");
            cout << "Press any key to continue......." << endl;
            system("CLS");
            displayupdatedgame();

        }
        else if (game[a][b] != 0) {
            cout << "Value already exists. Enter new number in place of 0." << endl;
            system("PAUSE");
            cout << "Press any key to continue......." << endl;
            system("CLS");
            displayupdatedgame();
        }
        else if (a == -1 && b == -1) {
            system("CLS");
            gameover(0);
        }
        else if (correctguess == spaces) {
            cout << "You have solved the table!" << endl;
        }

    }
    int savevalues(int x, int z) {

        return grid[x][z];

    }
    //global variable for saving values
    void transfervalues() {
        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                game[x][z] = savevalues(x, z);
            }
        }
    }
    void displayupdatedgame() {

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (c == 3 || c == 6)
                    cout << " | ";
                cout << game[r][c] << " ";
            }
            if (r == 2 || r == 5) {
                cout << endl;
                for (int i = 0; i < size; i++)
                    cout << "---";
            }

            cout << endl;

        }
    }
    void showguessleft() {
        cout << "Guess Left: " << guessleft << "/" << maxguess << endl;
    }

};
class HardMode :public Sudoku {
public:
    void boardgeneration() {
        int hardgrid[9][9] = {
       {3, 0, 6, 5, 0, 8, 4, 0, 0},
       {5, 2, 0, 0, 0, 4, 0, 0, 8},
       {0, 8, 7, 0, 2, 0, 0, 3, 1},
       {0, 0, 3, 0, 1, 0, 0, 8, 0},
       {9, 0, 0, 8, 6, 3, 0, 0, 5},
       {0, 5, 1, 0, 9, 0, 6, 4, 0},
       {1, 3, 0, 0, 0, 0, 2, 5, 0},
       {0, 9, 0, 3, 0, 1, 0, 7, 4},
       {7, 0, 5, 2, 0, 6, 3, 0, 0}
        };
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = hardgrid[i][j];
            }
        }
    }
    void settotalguess() {
        guessleft = 50;
        maxguess = hardmaxguess;
        spaces = 40;
    }
    void createHighscoreFile() {
        ofstream highscoreFile("hardhighscore.txt");
        highscoreFile << "0\n";
        highscoreFile.close();
    }
    void updateHighscore(int score) {
        ifstream highscoreFile("hardhighscore.txt");
        int currentScore;
        highscoreFile >> currentScore;
        highscoreFile.close();

        if (score > currentScore) {
            cout << "CONGRATULATIONS! YOU SET A NEW RECORD!" << endl;
            ofstream highscoreFile("hardhighscore.txt");
            highscoreFile << score << "\n";
            highscoreFile.close();
        }
    }
    void displayhighscore() {
        ifstream highscoreFile("hardhighscore.txt");
        int currentScore;
        highscoreFile >> currentScore;
        cout << "************HIGH SCORE: " << currentScore << "*******************" << endl;
        cout << "Hope you had fun playing! See you next time T_T" << endl;
        highscoreFile.close();

    }
};

class MediumMode : public Sudoku {
public:
    void boardgeneration() {
        int mediumgrid[9][9] = {
            {8,2,0,1,5,0,3,9,0},
            {9,0,5,0,2,7,0,4,8},
            {3,4,1,6,8,9,7,5,2},
            {5,9,0,4,6,8,0,7,1},
            {4,7,2,5,0,3,6,0,9},
            {0,1,8,0,7,2,4,3,5},
            {0,8,0,2,3,5,9,1,0},
            {1,5,4,0,9,6,0,2,3},
            {2,0,9,8,4,0,5,6,0}
        };
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = mediumgrid[i][j];
            }
        }
    }
    void settotalguess() {
        guessleft = 30;
        maxguess = mediummaxguess;
        spaces = 20;
    }
    void createHighscoreFile() {
        ofstream highscoreFile("mediumhighscore.txt");
        highscoreFile << "0\n";
        highscoreFile.close();
    }
    void updateHighscore(int score) {
        ifstream highscoreFile("mediumhighscore.txt");
        int currentScore;
        highscoreFile >> currentScore;
        highscoreFile.close();

        if (score > currentScore) {

            cout << "CONGRATULATIONS! YOU SET A NEW RECORD!" << endl;
            ofstream highscoreFile("mediumhighscore.txt");
            highscoreFile << score << "\n";
            highscoreFile.close();
        }
    }
    void displayhighscore() {
        ifstream highscoreFile("mediumhighscore.txt");
        int currentScore;
        highscoreFile >> currentScore;
        cout << "************HIGH SCORE: " << currentScore << "*******************" << endl;
        cout << "Hope you had fun playing! See you next time T_T" << endl;
        highscoreFile.close();

    }
};

class EasyMode :public Sudoku {
public:
    void createHighscoreFile() {
        ofstream highscoreFile("easyhighscore.txt");
        highscoreFile << "0\n";
        highscoreFile.close();
    }
    void updateHighscore(int score) {
        ifstream highscoreFile("easyhighscore.txt");
        int currentScore;
        highscoreFile >> currentScore;
        highscoreFile.close();

        if (score > currentScore) {

            cout << "CONGRATULATIONS! YOU SET A NEW RECORD!" << endl;
            ofstream highscoreFile("easyhighscore.txt");
            highscoreFile << score << "\n";
            highscoreFile.close();
        }
    }
    void displayhighscore() {
        ifstream highscoreFile("easyhighscore.txt");
        int currentScore;
        highscoreFile >> currentScore;
        cout << "************HIGH SCORE: " << currentScore << "*******************" << endl;
        cout << "Hope you had fun playing! See you next time T_T" << endl;
        highscoreFile.close();

    }

    void boardgeneration() {
        int easygrid[9][9] = {
            {4,3,0,2,6,9,7,8,1},
            {6,8,2,0,7,1,4,9,3},
            {0,9,7,8,3,4,5,6,2},
            {8,2,6,1,9,0,3,4,7},
            {3,7,4,6,8,2,0,1,5},
            {9,5,1,7,4,3,0,2,8},
            {5,1,0,3,2,6,8,7,4},
            {2,4,8,0,5,7,1,3,6},
            {0,6,3,4,1,8,0,5,9}
        };
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = easygrid[i][j];
            }
        }
    }
    void settotalguess() {
        guessleft = 20;
        maxguess = easymaxguess;
        spaces = 10;
    }

};

int main() {
    string a;
    int b;
    Tutorial t(a);
    Tips ti;
    cout << "PLEASE ENTER YOUR NAME!" << endl;
    cin >> a;
    cout << "\tHELLO! " << a << " & WELCOME TO A SIMPLE TUTORIAL ON OUR SUDOKU GAME\t" << endl;
    cout << "" << endl;
    cout << "If you are a complete beginner on how to play Sudoku, please press [1]\nIf you would like to learn the controls on how to play our C++ designed Sudoku, please press [2]";
    cout << endl;
    cin >> b;
    if (b == 1) {
        system("CLS");
        t.sudoku();

    }
    else if (b == 2) {
        system("CLS");
        ti.display();
    }
    else {
        cout << "INVALID INPUT";
    }
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << "We hope this tutorial was helpful to you! Please enjoy the game!\n";
    cout << "--------------------------------------------------------------------------------------------------" << endl;

    string name, mode;
    int rowno, colno, guessno, end = 1, score = 0, choice = 0;

    cout << "Select level of difficulty:" << "\n1.Easy [Spaces:10  Tries:20]\n2.Medium [Spaces:20  Tries:30]\n3.Hard [Spaces:40  Tries:50]" << endl;
    cin >> choice;
    if (choice == 1) {
        EasyMode H1;
        H1.boardgeneration(); H1.settotalguess(); H1.sudokuGrid();  H1.transfervalues();  H1.solveSudoku();
        do {
            cout << "Enter row number (0-8):  "; cin >> rowno;
            cout << "Enter column number (0-8):  "; cin >> colno;
            cout << "Enter your guess:  "; cin >> guessno;   H1.checkvalue(rowno, colno, guessno);  end = H1.checkgameover(rowno, colno);  H1.showguessleft();
        } while (end != 0);
        //find score by subtracting guesses used from total guesses 
        score = H1.maxguess - H1.getguess(); cout << "Your Score: " << score << endl; H1.createHighscoreFile();  H1.updateHighscore(score); H1.displayhighscore();
    }
    else if (choice == 2) {
        MediumMode H1;
        H1.boardgeneration(); H1.settotalguess(); H1.sudokuGrid();  H1.transfervalues();  H1.solveSudoku();
        do {
            cout << "Enter row number (0-8):  "; cin >> rowno; cout << "Enter column number (0-8):  "; cin >> colno;
            cout << "Enter your guess:  "; cin >> guessno;
            H1.checkvalue(rowno, colno, guessno);  end = H1.checkgameover(rowno, colno);  H1.showguessleft();
        } while (end != 0);
        //find score by subtracting guesses used from total guesses 
        score = H1.maxguess - H1.getguess(); cout << "Your Score: " << score << endl; H1.createHighscoreFile(); H1.updateHighscore(score); H1.displayhighscore();

    }
    else if (choice == 3) {
        HardMode H1;
        H1.boardgeneration(); H1.settotalguess(); H1.sudokuGrid();  H1.transfervalues();  H1.solveSudoku();
        do {
            cout << "Enter row number (0-8):  "; cin >> rowno;
            cout << "Enter column number (0-8):  "; cin >> colno;
            cout << "Enter your guess:  "; cin >> guessno;
            H1.checkvalue(rowno, colno, guessno);  end = H1.checkgameover(rowno, colno);  H1.showguessleft();
        } while (end != 0);
        //find score by subtracting guesses used from total guesses 
        score = H1.maxguess - H1.getguess(); cout << "Your Score: " << score << endl; H1.createHighscoreFile(); H1.updateHighscore(score); H1.displayhighscore();
    }
    else {
        cout << "ERROR! INVALID MODE SELECTED." << endl;
    }

}