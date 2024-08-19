#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Hangman stages represented as ASCII art
const string hangmanStages[] = {
    "  --------  \n"
    "  |      |  \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "---------\n",

    "  --------  \n"
    "  |      |  \n"
    "  |      O  \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "---------\n",

    "  --------  \n"
    "  |      |  \n"
    "  |      O  \n"
    "  |      |  \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "---------\n",

    "  --------  \n"
    "  |      |  \n"
    "  |      O  \n"
    "  |     /|  \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "---------\n",

    "  --------  \n"
    "  |      |  \n"
    "  |      O  \n"
    "  |     /|\\ \n"
    "  |         \n"
    "  |         \n"
    "  |         \n"
    "---------\n",

    "  --------  \n"
    "  |      |  \n"
    "  |      O  \n"
    "  |     /|\\ \n"
    "  |     /    \n"
    "  |         \n"
    "  |         \n"
    "---------\n",

    "  --------  \n"
    "  |      |  \n"
    "  |      O  \n"
    "  |     /|\\ \n"
    "  |     / \\ \n"
    "  |         \n"
    "  |         \n"
    "---------\n"
};

// Function to read words from a file
vector<string> readWords(string filename) {
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    return words;
}

// Function to select a random word
string selectWord(vector<string>& words) {
    srand(time(NULL));
    int index = rand() % words.size();
    return words[index];
}

// Function to display the current state of the word
void displayWord(string& word, vector<char>& guesses) {
    for (char c : word) {
        if (count(guesses.begin(), guesses.end(), tolower(c)) > 0 || count(guesses.begin(), guesses.end(), toupper(c)) > 0) {
            cout << c;
        } else {
            cout << "_";
        }
    }
    cout << endl;
}

int main() {
    vector<string> words = readWords("words.txt");
    string word = selectWord(words);
    vector<char> guesses;
    int remainingGuesses = 6;

    while (true) {
        // Display the hangman based on remaining guesses
        cout << hangmanStages[6 - remainingGuesses];

        cout << "Remaining guesses: " << remainingGuesses << endl;
        displayWord(word, guesses);

        char guess;
        cout << "Guess a letter: ";
        cin >> guess;

        if (count(guesses.begin(), guesses.end(), tolower(guess)) > 0 || count(guesses.begin(), guesses.end(), toupper(guess)) > 0) {
            cout << "You already guessed that letter. Try again." << endl;
            continue;
        }

        guesses.push_back(tolower(guess));

        if (word.find_first_of(guess) == string::npos && word.find_first_of(toupper(guess)) == string::npos) {
            remainingGuesses--;
        }

        if (remainingGuesses == 0) {
            cout << "You lose! The word was: " << word << endl;
            break;
        }

        bool won = true;
        for (char c : word) {
            if (count(guesses.begin(), guesses.end(), tolower(c)) == 0 && count(guesses.begin(), guesses.end(), toupper(c)) == 0) {
                won = false;
                break;
            }
        }

        if (won) {
            cout << "Congratulations, you won!" << endl;
            break;
        }
    }

    return 0;
}