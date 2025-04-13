#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "Screens.h"

class InstructionsScreen : public Screens {
    RenderWindow& window; // Reference to sf::RenderWindow
    Image backgroundImage;
    Texture backgroundTexture;
    Sprite background;
    Texture closeButtonTexture;
    Sprite closeButton;
    bool isClosePressed;

    void setupBG() {
        backgroundImage.loadFromFile("Images/Instructiongpt.jpg");
        backgroundTexture.loadFromImage(backgroundImage);

        background.setTexture(backgroundTexture);
        background.setPosition(0, 0);
    }
    void setupButtons(){
        closeButtonTexture.loadFromFile("Images/newclosers.png");
        closeButton.setTexture(closeButtonTexture);
        closeButton.setPosition(1450, 10);

    }

public:
    InstructionsScreen(RenderWindow& window) : window(window) {
        setupBG();
        setupButtons();
        isClosePressed = 0;
    
    }



    void handleEvents(sf::RenderWindow& window) override
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int mouseX = sf::Mouse::getPosition(window).x;
            int mouseY = sf::Mouse::getPosition(window).y;
            if (closeButton.getGlobalBounds().contains(mouseX, mouseY)) {
                cout << "Close button clicked!" << endl;
                isClosePressed = 1;
                // Switch to gameplay screen
            }
            
        }
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(background);
        window.draw(closeButton);
    }
    bool getClose() { return isClosePressed; }
    void resetClose() { isClosePressed = 0; }
};

#endif // !INSTRUCTIONS_H
