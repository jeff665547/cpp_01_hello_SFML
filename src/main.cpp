#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(700, 200), "Hello! This is the SFML Window!");
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("../resource/LingWaiTC-Medium.otf"))
        return EXIT_FAILURE;
    sf::Text text(L"Hello SFML!! 妳好！", font, 80);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}