#pragma once
#include "stdafx.h"
#include "PlayerCrosshair.h"
#include "Enemigo.h"

using namespace sf;


class Juego
{
	RenderWindow* _wnd;  //variable dinamica porque instanciamos enm el constructor, es el objeto central en SFML
	PlayerCrosshair* _player;
	//Enemigo _enemigos[10];    //contenedor estatico
	Enemigo* _enemigos;
	Font _fuente;
	Text _puntaje;
	int _puntos;
	bool _juegoGanado; // Nueva variable para controlar si el juego ha terminado


	void _actualizarPuntaje() {
		//char pts[100];
		//itoa(_puntos, pts, 10);   ya no funciona
		//_puntaje.setString(pts);
		if (_puntos < 5) {
			_puntaje.setString(std::to_string(_puntos));			
		}
		else {
			_puntaje.setString("¡Ganaste!");
			_puntaje.setFillColor(Color::Green); // Cambia el color del mensaje
			_juegoGanado = true;
		}
		
		
	}


public:
	//constructor
	Juego() {
		_wnd = new RenderWindow(VideoMode(1000, 1000), "Clickale");
		_player = new PlayerCrosshair();
		_enemigos = new Enemigo[10];
		_juegoGanado = false;
		_fuente.loadFromFile("../Fuentes/Montserrat-BlackItalic.ttf");
		_puntaje.setFont(_fuente);
		_puntaje.setPosition(0.0f, 0.0f);
		_puntaje.setCharacterSize(50.0f);
		//_puntaje.setColor(Color::Cyan); quedo obsoleta 
		_puntaje.setFillColor(Color::Cyan);
		_wnd->setMouseCursorVisible(false);

		_puntos = 0;
		_actualizarPuntaje();
	}


	//loop principal 
	void Loop() {
		while (_wnd->isOpen()) {
			if (!_juegoGanado) {
				ProcesarEventos();
				Actualizar();
				Dibujar();
			}
			else {
				// Muestra el mensaje de "¡Ganaste!" y espera unos segundos antes de cerrar
				Dibujar(); // Dibujar una última vez para mostrar el mensaje de victoria
				sleep(seconds(2));  // Pausa para que el jugador vea el mensaje
				_wnd->close();  // Cierra la ventana después de la pausa
			}
			
		}
		
	}

	//ProcesarEventos contiene el loop principal de eventos del juego
	//CON BUFFER
	void ProcesarEventos() {
		Event evt;
		while (_wnd->pollEvent(evt)) {
			if (evt.type == Event::Closed) {
				_wnd->close();
			}
			if (!_juegoGanado) { // Solo procesar eventos si el juego no ha sido ganado
				if (evt.type == Event::MouseMoved) {
					_player->Posicionar(evt.mouseMove.x, evt.mouseMove.y);
				}
				if (evt.type == Event::MouseButtonPressed) {
					if (evt.mouseButton.button == Mouse::Button::Left)
						Disparar();
				}
			}
		}
	}

	void Actualizar() {

		//actualizamos la posicion del crosshair

		//UTILIZAMOS INPUT SIN BUFFERS (no hay eventos) para actualizar la posicion de la mira
		//Vector2i mousePos = Mouse::getPosition(*_wnd); //si no le ponemos parametro, toma la posicion relativa al escritorio
		//_player->Posicionar(mousePos.x, mousePos.y);


		_actualizarPuntaje();
		
		
		if (!_juegoGanado) {
			for (size_t i = 0; i < 10; i++) {
				_enemigos[i].Actualizar(_wnd);
			}

		}	

	}

	void Disparar() {
		//chequeamos colisiones con el disparo
		Vector2f playerPos = _player->ObtenerPosicion();
		for (int i = 0; i < 10; i++) {
			if (_enemigos[i].EstaActivo()) {
				if (_enemigos[i].EstaEncima(playerPos.x, playerPos.y)) {
					_enemigos[i].Derrotar();
					_puntos++;
				}


			}
		}
		_actualizarPuntaje();
	}

	void Dibujar() {

		_wnd->clear(); //limpia la ventana, podemos darle un color de fondo como parametro
		//_wnd->clear(Color::White);




		//Dibujar los elementos del juego


		for (int i = 0; i < 10; i++) {
			if (_enemigos[i].EstaActivo())
				_enemigos[i].Dibujar(_wnd);
		}
		_wnd->draw(_puntaje);
		_player->Dibujar(_wnd);  //como argumento recibe la ventana sobre la que dibujamos

		_wnd->display(); //muestra los objetos en escena

	}

	//por cada new que ponemos, hay que agregar tambien un destructor
	~Juego() {
		//en el orden inverso, para no destruir un objeto que contenga otro que todavia no fue destruido
		delete[]_enemigos;
		delete _player;
		delete _wnd;
	}


};

