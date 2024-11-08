#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
Texture tex_cuadYellow;
Texture tex_rcircle;
Sprite sprite_cuadYellow;
Sprite sprite_rcircle;

float escalaX, escalaY, height_rcircle, width_rcircle, height_yellow, width_yellow;

int main() {
	RenderWindow App(sf::VideoMode(800, 600, 32), "Atrapado");
    Vector2f position(400,300); 

    //Preparo texturas y sprite
    tex_cuadYellow.loadFromFile("../Assets/cuad_yellow.png");
    tex_rcircle.loadFromFile("../Assets/rcircle.png");
    sprite_cuadYellow.setTexture(tex_cuadYellow);

    //Igualamos las texturas
    height_rcircle = (float)tex_rcircle.getSize().y;
    width_rcircle = (float)tex_rcircle.getSize().x;
    height_yellow = (float)tex_cuadYellow.getSize().y;
    width_yellow = (float)tex_cuadYellow.getSize().x;
    escalaX = width_rcircle / width_yellow;
    escalaY = height_rcircle / height_yellow;

    // Establecer el origen del sprite en su centro
    sprite_cuadYellow.setOrigin(sprite_cuadYellow.getGlobalBounds().width / 2,
        sprite_cuadYellow.getGlobalBounds().height / 2);

    //comenzamos con el sprite en el centro
    sprite_cuadYellow.setPosition(position);
    sprite_cuadYellow.setScale(escalaX, escalaY);

    bool isYellow = true;
    int velocidad = 10; //con un valor de 5 se acerca mejor a los bordes

    while (App.isOpen()) {
        Event evt;

        //como el sprite es un cuadrado, la mitad no cambia
        float mitadSprite = sprite_cuadYellow.getGlobalBounds().height / 2;

        // Procesar eventos
        while (App.pollEvent(evt)) {
            switch (evt.type) {
            case Event::Closed:
                App.close();
                break;

            case Event::KeyPressed:
                if (evt.key.code == Keyboard::Up && (position.y > 0 + mitadSprite + velocidad)) {
                    position.y-=velocidad;
                }
                if (evt.key.code == Keyboard::Down && (position.y < 600-mitadSprite-velocidad) ) {
                    position.y+=velocidad
                        ;
                }
                if (evt.key.code == Keyboard::Left && (position.x > 0 + mitadSprite + velocidad)) {
                    position.x-=velocidad;
                }
                if (evt.key.code == Keyboard::Right && (position.x < 800 - mitadSprite - velocidad)) {
                    position.x+=velocidad;
                }
                if (evt.key.code == Keyboard::Space) {
                    isYellow = false;
                    sprite_rcircle.setTexture(tex_rcircle);

                    sprite_rcircle.setOrigin(sprite_rcircle.getGlobalBounds().width / 2,
                       sprite_rcircle.getGlobalBounds().height / 2);
                }
                break;
            }
        }

        sprite_cuadYellow.setPosition(position);
        sprite_rcircle.setPosition(position);

        App.clear();

        if (isYellow)
            App.draw(sprite_cuadYellow);
        else
            App.draw(sprite_rcircle);
        

        App.display();
    }
    return 0;


}