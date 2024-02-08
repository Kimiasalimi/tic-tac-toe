#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void display_table(char table[9]) {
    cout << "\n";
    cout << table[0] << " | " << table[1] << " | " << table[2] << "\n";
    cout << "---------\n";
    cout << table[3] << " | " << table[4] << " | " << table[5] << "\n";
    cout << "---------\n";
    cout << table[6] << " | " << table[7] << " | " << table[8] << "\n";
    cout << "\n";
}

// A function to check if a player has won the game
bool is_winner(char table[9], char symbol) {
    
    if (table[0] == symbol && table[1] == symbol && table[2] == symbol) return true;
    if (table[3] == symbol && table[4] == symbol && table[5] == symbol) return true;
    if (table[6] == symbol && table[7] == symbol && table[8] == symbol) return true;
    
    if (table[0] == symbol && table[3] == symbol && table[6] == symbol) return true;
    if (table[1] == symbol && table[4] == symbol && table[7] == symbol) return true;
    if (table[2] == symbol && table[5] == symbol && table[8] == symbol) return true;

    if (table[0] == symbol && table[4] == symbol && table[8] == symbol) return true;
    if (table[2] == symbol && table[4] == symbol && table[6] == symbol) return true;
    // No winner
    return false;
}


bool is_full(char table[9]) {
    for (int i = 0; i < 9; i++) {
        if (table[i] == ' ') return false;
    }
    return true;
}

// A function to get the player's move
int get_move(char table[9], string player, char symbol) {
    int move;
    cout << player << "'s turn (" << symbol << "): ";
    cin >> move;
    while (move < 1 || move > 9 || table[move - 1] != ' ') {
        cout << "Invalid move. Please enter a number between 1 and 9 that is not already occupied: ";
        cin >> move;
    }
    return move;
}

// A function to play the game
void play_game(string scores[100][2], int& n) {
    // Initialize the board
    char table[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    // Display the table
    display_table(table);
    // Get the players' names
    string player1, player2;
    cout << "Enter the name of player 1: ";
    cin >> player1;
    cout << "Enter the name of player 2: ";
    cin >> player2;
    // Assign the symbols
    char symbol1 = 'X', symbol2 = 'O';
    // Start the game loop
    bool game_over = false;
    string winner;
    while (!game_over) {
        // Player 1's move
        int move1 = get_move(table, player1, symbol1);
        table[move1 - 1] = symbol1;
        display_table(table);
        // Check if player 1 has won
        if (is_winner(table, symbol1)) {
            game_over = true;
            winner = player1;
            break;
        }
        // Check if the board is full
        if (is_full(table)) {
            game_over = true;
            winner = "tie";
            break;
        }
        // Player 2's move
        int move2 = get_move(table, player2, symbol2);
        table[move2 - 1] = symbol2;
        display_table(table);
        // Check if player 2 has won
        if (is_winner(table, symbol2)) {
            game_over = true;
            winner = player2;
            break;
        }
        // Check if the table is full
        if (is_full(table)) {
            game_over = true;
            winner = "tie";
            break;
        }
    }
    // Display the result
    if (winner == "tie") {
        cout << "The game is a tie.\n";
    }
    else {
        cout << "The winner is " << winner << ".\n";
    }
    // Update the scores
    bool found1 = false, found2 = false;
    for (int i = 0; i < n; i++) {
        if (scores[i][0] == player1) {
            found1 = true;
            if (winner == player1) {
                scores[i][1] = to_string(stoi(scores[i][1]) + 1);
            }
            else if (winner == player2) {
                scores[i][1] = to_string(max(0, stoi(scores[i][1]) ));
            }
        }
        if (scores[i][0] == player2) {
            found2 = true;
            if (winner == player2) {
                scores[i][1] = to_string(stoi(scores[i][1]) + 1);
            }
            else if (winner == player1) {
                scores[i][1] = to_string(max(0, stoi(scores[i][1]) ));
            }
        }
    }
if(!found1){
    scores[n][0] = player1;
    scores[n][1] = (winner==player1) ? "1" : "0";
    n++;
}
if(!found2){
    scores[n][0] = player2;
    scores[n][1] = (winner==player2) ? "1" : "0";
    n++;
}
}

// A function to display the scoreboard
void display_scoreboard(string scores[100][2], int n) {
    cout << "\n";
    cout << "Scoreboard:\n";
    cout << "Name\tWins\n";
    for (int i = 0; i < n; i++) {
        cout << scores[i][0] << "\t" << scores[i][1] << "\n";
    }
    cout << "\n";
}

// A function to display the menu
void display_menu() {
    cout << "\n";
    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Please choose an option:\n";
    cout << "1) Start game\n";
    cout << "2) Scoreboard\n";
    cout << "3) Exit\n";
    cout << "\n";
}

// The main function
int main() {
    // Initialize the scores
    string scores[100][2];
    int n = 0;
    // Display the menu
    display_menu();
    // Get the user's choice
    int choice;
    cin >> choice;
    while (choice != 3) {
        switch (choice) {
            case 1:
                // Start the game
                play_game(scores, n);
                break;
            case 2:
                // Display the scoreboard
                display_scoreboard(scores, n);
                break;
            default:
                // Invalid choice
                cout << "Invalid choice. Please enter a number between 1 and 3.\n";
                break;
        }
        // Display the menu again
        display_menu();
        // Get the user's choice again
        cin >> choice;
    }
    // Exit the program
    cout << "Thank you for playing. Goodbye!\n";
    return 0;
}
