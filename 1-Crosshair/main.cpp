#include <SFML/Window.hpp>
#include <SFML/graphics.hpp>
using namespace sf;

Texture texture_crosshair;
Sprite sprite_crosshair;


int main() {

	texture_crosshair.loadFromFile("../Assets/crosshair.png");
	sprite_crosshair.setTexture(texture_crosshair);

	// Establecer el origen del sprite en su centro
	sprite_crosshair.setOrigin(sprite_crosshair.getGlobalBounds().width / 2,
		sprite_crosshair.getGlobalBounds().height / 2);

	sprite_crosshair.setPosition(400, 300);


	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Crosshair");

	while (App.isOpen()) {




		App.clear();

		App.draw(sprite_crosshair);
		

		App.display();
	}
	return 0;

}