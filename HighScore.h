#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "Screens.h"
#include <fstream>

struct NameScore {
    string name = "default";
    int score = 0;
};
class HighScoreScreen : public Screens {
    RenderWindow& window; // Reference to sf::RenderWindow
    Image backgroundImage;
    Texture backgroundTexture;
    Sprite background;
    Texture closeButtonTexture;
    Sprite closeButton;
    bool isClosePressed;
    Text scoreText;
    Font scoreFont;
    NameScore updateStruct[3];


    void setupBG() {
        backgroundImage.loadFromFile("Images/HighScore.jpg");
        backgroundTexture.loadFromImage(backgroundImage);

        background.setTexture(backgroundTexture);
        background.setPosition(0, 0);
    }
    void setupButtons() {
        closeButtonTexture.loadFromFile("Images/newclosers.png");
        closeButton.setTexture(closeButtonTexture);
        closeButton.setPosition(1450, 10);

    }

public:
    HighScoreScreen(RenderWindow& window) : window(window) {
        setupBG();
        setupButtons();
        isClosePressed = 0;

    }
    
   
    void readdata() {
        ifstream ifs("score.txt");
        if (!ifs.is_open()) {
            cerr << "Failed to open score.txt\n";
            return;
        }

        for (int i = 0; i < 3; i++) {
            if (!(ifs >> updateStruct[i].name >> updateStruct[i].score)) {
                cerr << "Error reading data from score.txt\n";
                break; // Exit loop if there's an error
            }
        }

        ifs.close();
    }

    void drawScores(RenderWindow& window) {
        for (int i = 0; i < 3; i++) {
            Text text;
            text.setFont(scoreFont);
            text.setCharacterSize(24);
            text.setFillColor(Color::Black);
            text.setPosition(100, 200 + i * 50); // Adjust position as needed

            // Construct the text string to display player name and score without stringstream
            string displayString = updateStruct[i].name + ": " + to_string(updateStruct[i].score);
            text.setString(displayString);

            window.draw(text);
        }
    }

    void handleEvents(RenderWindow& window) override
    {
        readdata();
        if (Mouse::isButtonPressed(Mouse::Left)) {
            int mouseX = Mouse::getPosition(window).x;
            int mouseY = Mouse::getPosition(window).y;
            if (closeButton.getGlobalBounds().contains(mouseX, mouseY)) {
                cout << "Close button clicked!" << endl;
                isClosePressed = 1;
                
                // Switch to gameplay screen
            }

        }
        
    }
    void draw(RenderWindow& window) override
    {
        window.draw(background);
        window.draw(closeButton);
        drawScores(window);
    }
    bool getClose() { return isClosePressed; }
    void resetClose() {this->isClosePressed = 0; }
};


#endif // !HIGHSCORE_H
