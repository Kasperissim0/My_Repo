#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode({900, 600}), "SFML window");

  sf::Font font("arial.ttf");
  sf::Text text(font, "Hello SFML", 50);

  // Draw the string
  window.draw(text);

  // Wait for 5 seconds
  std::this_thread::sleep_for(std::chrono::seconds(5));

  return 0;
}