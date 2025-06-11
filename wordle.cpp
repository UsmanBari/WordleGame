#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Constants for the grid
const int resolutionX = 640;
const int resolutionY = 640;
const int boxSize = 64;
const int gridRows = 6; // 6 guesses
const int gridColumns = 5; // 5-letter words

// Array of 50 words
const string wordList[50] = {
    "apple", "table", "grape", "brush", "cream", "house", "heart", "bread", "dream", "light",
    "stone", "plant", "chair", "river", "cloud", "piano", "money", "grass", "scale", "flame",
    "paper", "pearl", "glass", "space", "clock", "mouse", "crowd", "drama", "water", "flute",
    "white", "smile", "shape", "blood", "round", "dance", "block", "plaza", "store", "beach",
    "shade", "horse", "shine", "ocean", "fruit", "plume", "dance", "sword", "vocal", "wings"
};

// Function to check character feedback
void evaluateGuess(const string& guess, string& feedback, const string& secretWord) {
    feedback = "     "; // Initialize with spaces
    for (int i = 0; i < gridColumns; i++) {
        if (guess[i] == secretWord[i]) {
            feedback[i] = 'G'; // Green for correct position
        }
        else if (secretWord.find(guess[i]) != string::npos) {
            feedback[i] = 'Y'; // Yellow for incorrect position but correct letter
        }
        else {
            feedback[i] = 'R'; // Black for incorrect letter
        }
    }
}

// Class to handle the Wordle grid
class WordleGrid {
private:
    char guesses[gridRows][gridColumns]; // Stores the guesses
    string feedback[gridRows];          // Feedback for each guess
    int currentRow;                     // Current row being guessed

public:
    WordleGrid() : currentRow(0) {
        for (int i = 0; i < gridRows; i++) {
            for (int j = 0; j < gridColumns; j++) {
                guesses[i][j] = ' '; // Initialize empty grid
            }
            feedback[i] = "     "; // Empty feedback
        }
    }

    bool makeGuess(const string& guess, const string& secretWord) {
        if (currentRow >= gridRows) return false; // No more guesses
        for (int i = 0; i < gridColumns; i++) {
            guesses[currentRow][i] = guess[i];
        }
        evaluateGuess(guess, feedback[currentRow], secretWord);
        currentRow++;
        return true;
    }

    void draw(sf::RenderWindow& window, sf::Font& font, const string& currentGuess) {
        sf::RectangleShape box(sf::Vector2f(boxSize, boxSize));
        sf::Text letterText;
        letterText.setFont(font);
        letterText.setCharacterSize(32);
        letterText.setStyle(sf::Text::Bold);

        for (int i = 0; i < gridRows; i++) {
            for (int j = 0; j < gridColumns; j++) {
                // Set the box color based on feedback
                if (feedback[i][j] == 'G') box.setFillColor(sf::Color::Green);
                else if (feedback[i][j] == 'Y') box.setFillColor(sf::Color::Yellow);
                else if (feedback[i][j] == 'R') box.setFillColor(sf::Color::Red);
                else box.setFillColor(sf::Color::White);

                box.setOutlineColor(sf::Color::Black);
                box.setOutlineThickness(2);
                box.setPosition(j * boxSize, i * boxSize);
                window.draw(box);

                // Draw the letters
                if (i < currentRow || (i == currentRow && j < currentGuess.length())) {
                    letterText.setString(string(1, (i == currentRow ? currentGuess[j] : guesses[i][j])));
                    letterText.setFillColor(sf::Color::Black);
                    letterText.setPosition(j * boxSize + boxSize / 4, i * boxSize + boxSize / 4);
                    window.draw(letterText);
                }
            }
        }
    }

    bool isGameOver() {
        return currentRow >= gridRows || feedback[currentRow - 1] == "GGGGG";
    }

    bool hasWon() {
        return feedback[currentRow - 1] == "GGGGG";
    }
};

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Wordle Game");
    sf::Font font;

    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font!" << endl;
        return -1;
    }

    // Select a random word
    string secretWord = wordList[rand() % 50];

    WordleGrid grid;
    string currentGuess = "";
    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle keyboard input
            if (!gameOver) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                        if (currentGuess.length() < gridColumns) {
                            currentGuess += static_cast<char>(event.key.code + 'a' - sf::Keyboard::A);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Backspace && !currentGuess.empty()) {
                        currentGuess.pop_back();
                    }
                    else if (event.key.code == sf::Keyboard::Enter && currentGuess.length() == gridColumns) {
                        gameOver = !grid.makeGuess(currentGuess, secretWord);
                        currentGuess = "";
                    }
                }
            }
        }

        // Game Over logic
        if (grid.isGameOver()) {
            gameOver = true;
        }

        // Clear and render the window
        window.clear(sf::Color::Black);
        grid.draw(window, font, currentGuess);

        if (gameOver) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(36);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setStyle(sf::Text::Bold);

            if (grid.hasWon()) {
                gameOverText.setString("You Won!");
            }
            else {
                gameOverText.setString("Game Over! The word was: " + secretWord);
            }

            gameOverText.setPosition(resolutionX / 10, resolutionY - 100);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
