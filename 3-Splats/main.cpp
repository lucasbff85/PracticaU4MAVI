#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

// Estructura para almacenar el tipo de sprite y su posición
struct CircleData {
    Vector2f position;
    bool isRed;  // true si es un rcircle, false si es un bcircle
};

Texture texture_rcircle;
Sprite sprite_rcircle;
Texture texture_bcircle;
Sprite sprite_bcircle;

int main() {
    // Cargar texturas y asignarlas a los sprites
    texture_rcircle.loadFromFile("../Assets/rcircle.png");
    sprite_rcircle.setTexture(texture_rcircle);
    texture_bcircle.loadFromFile("../Assets/rcircleb.png");
    sprite_bcircle.setTexture(texture_bcircle);

    // Establecer el origen de los sprites en su centro
    sprite_rcircle.setOrigin(sprite_rcircle.getGlobalBounds().width / 2,
        sprite_rcircle.getGlobalBounds().height / 2);
    sprite_bcircle.setOrigin(sprite_bcircle.getGlobalBounds().width / 2,
        sprite_bcircle.getGlobalBounds().height / 2);
    //achico los circulos
    sprite_rcircle.setScale(0.5f, 0.5f);
    sprite_bcircle.setScale(0.5f, 0.5f);


    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SPlats");

    // Vector para almacenar los datos de todos los círculos en orden de aparición
    std::vector<CircleData> circles;

    while (App.isOpen()) {
        Event evt;

        // Procesar eventos
        while (App.pollEvent(evt)) {
            switch (evt.type) {
            case Event::Closed:
                App.close();
                break;

            case Event::MouseButtonPressed:
                // Obtener la posición del mouse relativa a la ventana
                Vector2f circle_position = App.mapPixelToCoords(Mouse::getPosition(App));

                if (evt.mouseButton.button == Mouse::Button::Left) {
                    // Agregar un rcircle al vector
                    circles.push_back({ circle_position, true });
                }
                else if (evt.mouseButton.button == Mouse::Button::Right) {
                    // Agregar un bcircle al vector
                    circles.push_back({ circle_position, false });
                }
                break;
            }
        }

        App.clear();

        // Dibujar todos los círculos en el orden en que fueron agregados
        for (const auto& circle : circles) {
            if (circle.isRed) {
                sprite_rcircle.setPosition(circle.position);
                App.draw(sprite_rcircle);
            }
            else {
                sprite_bcircle.setPosition(circle.position);
                App.draw(sprite_bcircle);
            }
        }

        App.display();
    }
    return 0;
}
