#pragma once
#include "stdafx.h"

using namespace sf;

class Enemigo {
	//TODO: compartir las texturas 
	Texture _enemyTex;
	Sprite _enemySprite;
	bool _estaVivo;
	bool _estaVisible;
	sf::Clock _clock;
	float _tiempoVisible;
	float _tiempoApagado;

	Vector2f _randomPos(Vector2u maxPos) {

		// Obtiene las dimensiones del enemigo
		float enemigoAncho = _enemySprite.getGlobalBounds().width;
		float enemigoAlto = _enemySprite.getGlobalBounds().height;


		// Calcula una posición aleatoria dentro de los límites de la ventana
		float x = (float)(rand() % (maxPos.x - (int)enemigoAncho));
		float y = (float)(rand() % (maxPos.y - (int)enemigoAlto));

		return Vector2f(x, y);

	}

public:

	Enemigo() {
		_enemyTex.loadFromFile("../Assets/et.png");
		_enemySprite.setTexture(_enemyTex);
		_enemySprite.setScale(0.1f, 0.1f);
		_estaVivo = true;
		_estaVisible = false;
		_tiempoVisible = 1.0f;
		_tiempoApagado = 0.5f;

	}



	bool EstaVivo() {
		return _estaVivo;
	}

	bool EstaActivo() {
		return _estaVivo && _estaVisible;
	}

	bool EstaEncima(float x, float y) {
		//devuelve un rectangulo
		FloatRect bounds = _enemySprite.getGlobalBounds();
		return bounds.contains(x, y);
	}

	void Derrotar() {
		_estaVivo = false;
	}

	void Dibujar(RenderWindow* wnd) {
		//sistema de particulas, colores, efectos o lo que tenga que ver con dibujar el enemigo iria aca
		wnd->draw(_enemySprite);
	}

	void Actualizar(RenderWindow* wnd) {
		if (!_estaVivo)
			return;
		if (!_estaVisible) { //tiramos una probabilidad para ver si lo activamos
			if (_clock.getElapsedTime().asSeconds() > _tiempoApagado) {
				_clock.restart();
				if (rand() % 100 < 25) {
					_estaVisible = true;
					_enemySprite.setPosition(_randomPos(wnd->getSize()));
				}

			}
		}
		else {
			if (_clock.getElapsedTime().asSeconds() > _tiempoVisible) {
				_estaVisible = false;
				_clock.restart();
			}
		}
	}

};