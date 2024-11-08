#include "Juego.h"
#include "stdafx.h"



//main.cpp define el punto de entrada de la aplicacion de consola

int _tmain(int argc, _TCHAR* argv[])
{
	Juego myJuego;  //esta linea crea el objeto y llama al constructor
	myJuego.Loop();

	return 0;
}