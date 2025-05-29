#include <SFML/Graphics.hpp> // For Graphics
#include <iostream>
#include <random>
#include <string>

std::string GetHexColor () {
  
  std::string HexString;

  std::random_device GetSeed;
  std::mt19937 GenerateNumber(GetSeed());
  std::uniform_int_distribution<> GenRange(0, 15);

  for (int i = 0; i < 6; i++) {

    int TempNumber = GenRange(GenerateNumber);

    if (TempNumber > 9) {

      HexString += static_cast<char>('A' + (TempNumber - 10));

    }

    else {

      HexString += std::to_string(TempNumber);

    }

  }

  return "#" + HexString;

}

int GetRandomColor () {

  std::random_device GetSeed;
  std::mt19937 GenerateNumber(GetSeed());
  std::uniform_int_distribution<> GenRange(0, 255);

  return GenRange(GenerateNumber);
}

int GetRandomColor (bool overload) {

  std::random_device GetSeed;
  std::mt19937 GenerateNumber(GetSeed());
  std::uniform_int_distribution<> GenRange(0, 255);

  return GenRange(GenerateNumber);
}

using namespace sf;

int main () {
  
  unsigned int Width_Window = 900;
  unsigned int Height_Window = 600;
  Color BackgroundColor = Color(GetRandomColor(), GetRandomColor(), GetRandomColor());

  RenderWindow* window = new RenderWindow(VideoMode({Width_Window, Height_Window}), "Fucking Around With SFML");
  RectangleShape rectangle({float(Width_Window * 0.3), float(Height_Window * 0.3)});
  CircleShape center(float((Width_Window * Height_Window) * 0.0000099));

  center.setFillColor(Color::Red);
  center.setOrigin({center.getGeometricCenter().x, center.getGeometricCenter().y});
  center.setPosition({Width_Window / 2.f, Height_Window / 2.f});

  rectangle.setFillColor(Color(GetRandomColor(), GetRandomColor(), GetRandomColor()));
  rectangle.setOutlineColor(Color(GetRandomColor(), GetRandomColor(), GetRandomColor()));
  rectangle.setOutlineThickness(float(((Width_Window * 0.3) * (Height_Window * 0.3)) * 0.0003));
  rectangle.setOrigin({rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f}); // set origin to the middle of the rectangle
  rectangle.setPosition({Width_Window / 2.f, Height_Window / 2.f}); // set the rectangle in the middle of the screen


  
  while (window->isOpen()) {
    
    while (auto event = window->pollEvent()) { 
      
      if (event->is<Event::Closed>()) { // closing the window
        
        window->close();
        std::cout << "Window Closed" << std::endl;
        
      }
      
      else if (const auto* KeyPressed = event->getIf<Event::KeyPressed>()) { // close window using escape key + line breaks

        if (KeyPressed->scancode == Keyboard::Scancode::Escape) {
          
          window->close();
          std::cout << "Window Closed" << std::endl;
          
        }

        else if (KeyPressed->scancode == Keyboard::Scancode::Enter) {

          std::cout << '\n';

        }
        
      }
      
      else if (const auto* WindowResized = event->getIf<Event::Resized>()) { // when the window is resized

        Width_Window = WindowResized->size.x;
        Height_Window = WindowResized->size.y;

        // Create a new view with the current window dimensions
        View windowView;
        windowView.setCenter({Width_Window / 2.f, Height_Window / 2.f});
        windowView.setSize({float(Width_Window), float(Height_Window)});
        window->setView(windowView);

        center.setPosition({Width_Window / 2.f, Height_Window / 2.f}); 

        rectangle.setSize({float(Width_Window * 0.3), float(Height_Window * 0.3)});
        rectangle.setOutlineThickness(float(((Width_Window * 0.3) * (Height_Window * 0.3)) * 0.0003));
        rectangle.setOrigin({rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f});
        rectangle.setPosition({Width_Window / 2.f, Height_Window / 2.f});

        std::cout << "New Window Height - " << Height_Window << std::endl;
        std::cout << "New Window Width - " << Width_Window << std::endl;
        std::cout << std::endl; // line break

        std::cout << "New Rectangle Origin x Coordinates - " << rectangle.getOrigin().x << std::endl;
        std::cout << "New Rectangle Origin y Coordinates - " << rectangle.getOrigin().y << std::endl;
        std::cout << std::endl; // line break

        std::cout << "The Center Of The Window x Coordinates - " << center.getPosition().x << std::endl;
        std::cout << "The Center Of The Window y Coordinates - " << center.getPosition().y << std::endl;
        std::cout << std::endl; // line break

      }

      else if (const auto* EnteredText = event->getIf<Event::TextEntered>()) { // get input + display text
      
        std::cout << static_cast<char>(EnteredText->unicode); // translate ascii into text
        BackgroundColor = Color(GetRandomColor(true), GetRandomColor(true), GetRandomColor(true)); // ✅ Set new color
      
      }
      
      else if (Mouse::isButtonPressed(Mouse::Button::Right)) { // get mouse input

        std::cout << "Right Mouse Button Clicked" << std::endl;
        std::cout << std::endl; // line break

        rectangle.setFillColor(Color(GetRandomColor(), GetRandomColor(), GetRandomColor()));
        
        
      }

      else if (Mouse::isButtonPressed(Mouse::Button::Left)) { // get mouse input

        std::cout << "Left Mouse Button Clicked" << std::endl;
        std::cout << std::endl; // line break

        rectangle.setOutlineColor(Color(GetRandomColor(), GetRandomColor(), GetRandomColor()));
        
      }
        
      else if (event->is<Event::FocusLost>()) {

        std::cout << "Window Has Gone Out Of Focus" << std::endl;
        std::cout << std::endl; // line break

      }

      
      
    }
    
    window->clear(BackgroundColor); // set background

    window->draw(rectangle);
    window->draw(center);
      
      window->display(); // display the drawing on the window

  }
  
  delete window;
  return 0;
  
}