#include <SFML/Window.hpp>
#include <SFML/graphics.hpp>
using namespace sf;

Texture texture_rcircle;
Sprite sprite_rcircle1;
Sprite sprite_rcircle2;
Sprite sprite_rcircle3;
Sprite sprite_rcircle4;

// Variables de estado para el arrastre
bool dragging = false;
Sprite* selectedSprite = nullptr;


int main() {

	

	texture_rcircle.loadFromFile("../Assets/rcircle.png");
	sprite_rcircle1.setTexture(texture_rcircle);
	sprite_rcircle2.setTexture(texture_rcircle);
	sprite_rcircle3.setTexture(texture_rcircle);
	sprite_rcircle4.setTexture(texture_rcircle);

	sprite_rcircle2.setPosition(730, 0);
	sprite_rcircle3.setPosition(0, 530);
	sprite_rcircle4.setPosition(730, 530);

	sprite_rcircle1.setScale(0.5f, 0.5f);
	sprite_rcircle2.setScale(0.5f, 0.5f);
	sprite_rcircle3.setScale(0.5f, 0.5f);
	sprite_rcircle4.setScale(0.5f, 0.5f);

	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Drag");

	while (App.isOpen()) {

		sf::Event evt;
		while (App.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::MouseButtonPressed:
				if (evt.mouseButton.button == sf::Mouse::Left) {
					Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));

					

					// Verificar si el mouse está sobre alguno de los círculos
					if (sprite_rcircle1.getGlobalBounds().contains(mousePos)) {
						dragging = true;
						selectedSprite = &sprite_rcircle1;
					}
					else if (sprite_rcircle2.getGlobalBounds().contains(mousePos)) {
						dragging = true;
						selectedSprite = &sprite_rcircle2;
					}
					else if (sprite_rcircle3.getGlobalBounds().contains(mousePos)) {
						dragging = true;
						selectedSprite = &sprite_rcircle3;
					}
					else if (sprite_rcircle4.getGlobalBounds().contains(mousePos)) {
						dragging = true;
						selectedSprite = &sprite_rcircle4;
					}
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (evt.mouseButton.button == sf::Mouse::Left) {
					dragging = false;
					selectedSprite = nullptr;
				}
				break;
			}
		}

		// Si se está arrastrando un sprite, actualizar su posición al seguir el mouse
		if (dragging && selectedSprite) {
			Vector2f mousePos = App.mapPixelToCoords(Mouse::getPosition(App));
			selectedSprite->setPosition(mousePos);
		}
			
		

		App.clear();
		App.draw(sprite_rcircle1);
		App.draw(sprite_rcircle2);
		App.draw(sprite_rcircle3);
		App.draw(sprite_rcircle4);
		App.display();
	}
	return 0;
}