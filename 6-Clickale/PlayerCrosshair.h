#pragma once  //evita que este .h pueda ser incluido varias veces por un cpp, evita el error de redundancia ciclica
#include "stdafx.h" //cuando usamos encabezados por compilados, sino no hace falta

using namespace sf; //le decimos que usamos el namespace de SFML

class PlayerCrosshair {

	Texture _crossTex;
	Sprite _crossSprite;

public:

	PlayerCrosshair() {

		_crossTex.loadFromFile("../Assets/crosshair.png");
		_crossSprite.setTexture(_crossTex);
		_crossSprite.setScale(0.5f, 0.5f);
		Vector2u size = _crossTex.getSize();
		_crossSprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(_crossSprite);
	}

	void Posicionar(float x, float y) {
		_crossSprite.setPosition(x, y);
	}

	Vector2f ObtenerPosicion() {
		return _crossSprite.getPosition();
	}

};