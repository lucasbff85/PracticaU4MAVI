#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

Font fuente;
Text texto;
Text tamanioTexto;
int cantidad = 100;

int main() {
	RenderWindow App(sf::VideoMode(800, 800, 32), "Adaptación");
    Vector2u windowSize = App.getSize(); // Tamaño actual de la ventana
    
    //cargar la fuente
    fuente.loadFromFile("../Fuentes/Montserrat-BlackItalic.ttf");

    // Crear el objeto de texto
    
    texto.setFont(fuente);
    texto.setString("Presiona flechas de dirección");
    texto.setCharacterSize(15); // Tamaño de la fuente
    texto.setFillColor(Color::White); // Color del texto
    texto.setPosition(50, 550); // Posición en la ventana


    // Crear el objeto de texto para mostrar el tamaño de la pantalla
    tamanioTexto.setFont(fuente);
    tamanioTexto.setCharacterSize(15);
    tamanioTexto.setFillColor(Color::White);
    tamanioTexto.setPosition(50, 500); // Posición arriba de las instrucciones


    while (App.isOpen()) {
        Event evt;

        // Procesar eventos
        while (App.pollEvent(evt)) {
            switch (evt.type) {
            case Event::Closed:
                App.close();
                break;


            }
            if (evt.type == Event::KeyPressed) {
                if (evt.key.code == Keyboard::Up && windowSize.y < 1000) {
                    //windowSize.y += cantidad; // Aumenta alto
                    windowSize.y = std::min(1000u, windowSize.y + cantidad); // No aumentar más de 1000
                    App.setSize(windowSize);
                }
                if (evt.key.code == Keyboard::Down && windowSize.y > 100) {
                    //windowSize.y -= cantidad; // Disminuye alto
                    windowSize.y = std::max(100u, windowSize.y - cantidad); // No reducir por debajo de 100
                    App.setSize(windowSize);
                }
                if (evt.key.code == Keyboard::Right && windowSize.x < 1000) {
                    //windowSize.x += cantidad; // Aumenta ancho
                    windowSize.x = std::min(1000u, windowSize.x + cantidad); // No aumentar más de 1000
                    App.setSize(windowSize);
                }
                if (evt.key.code == Keyboard::Left && windowSize.x > 100) {
                    //windowSize.x -= cantidad; // Disminuye ancho
                    windowSize.x = std::max(100u, windowSize.x - cantidad); // No reducir por debajo de 100
                    App.setSize(windowSize);
                }
            }
        }

        // Actualizar el texto del tamaño de pantalla actual
        windowSize = App.getSize(); // Obtener el tamaño actualizado de la ventana
        tamanioTexto.setString(std::to_string(windowSize.x) + " x " + std::to_string(windowSize.y));


        App.clear();

        App.draw(texto);
        App.draw(tamanioTexto);

        App.display();
    }




	
}