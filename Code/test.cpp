#include <SFML/Graphics.hpp> // For Graphics
#include <optional>

using namespace sf;

int main () {
  
  const int Width_Window = 900;
  const int Heigh_Window = 600;

  RenderWindow* window = new RenderWindow(VideoMode({Width_Window, Heigh_Window}), "Fucking Around With SFML");

  
  while (window->isOpen()) {
    
    while (std::optional event = window->pollEvent()) { 
      
      if (event->is<Event::Closed>()) { // closing the window
        
        window->close();
        
      }
      
      else if (const auto* KeyPressed = event->getIf<Event::KeyPressed>()) {
        
        if (KeyPressed->scancode == Keyboard::Scancode::Escape) { // quit with escape
          
          window->close();
          
        }
        
      }
      
      // Draw Here

      window->clear(Color(238, 98, 128));
      window->display();
      
      
    }
    
  }
  
  delete window;
  return 0;
  
}