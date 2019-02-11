/*
	Autor: www.mtzgod.pw
	Discord: toM#7631
	Discord server: https://discord.gg/k6VZge 
*/

#include "tomMem.h"
#include "csgo.hpp" // Importamos este archivo desde https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.hpp


using namespace hazedumper::netvars; // Aplicamos los namespaces del archivo importado para no tener que hacer: hazedumper::netvars::offset
using namespace hazedumper::signatures; // Lo mismo

TomMem *tm = new TomMem(); // Inicializamos la librería, debería hacer el HANDLE con el juego e importar los modulos.

int main() {
	tm->GetLocalPlayer(dwLocalPlayer); // Debemos utilizar esta función para obtener el LocalPlayer.
	// Vamos a hacer un autobunny básico

	/* Primero debemos declarar los flags, los flags dentro del csgo indican el estado del jugador. Ojo: indican el ESTADO del ""JUGADOR"",
	esto significa que, logicamente, debemos acceder a datos del JUGADOR.

	Para esto, debemos acceder a los flags del jugador, por lo que comenzamos leyendo la memoria utilizando la libreria.

	pd: Los flags son un BYTE, también se pueden leer como un entero pero no es recomendable.

	*/

	// Hacemos un while para que sea un ciclo infinito, esto significará que el autobunny funcionará siempre mientras el programa esté abierto.
	while (true) {
		// Utilizamos la plantilla de funcion -> mRead<TIPO DE DATO A LEER>(DIRECCION DE MEMORIA)
		// Como flags es un BYTE, leeremos un BYTE, y obviamente declaramos la variable flags como un BYTE.
		BYTE flags = tm->mRead<BYTE>(tm->LocalPlayer + m_fFlags); // OJO EN LA DIRECCION: ACCEDEMOS A LA DIRECCION DE MEMORIA DEL JUGADOR + EL OFFSET DONDE SE ENCUENTRA SU ESTADO

		/* Ya tenemos los flags, ahora procederemos a verificar si la tecla de salto está siendo utilizada */
		if (GetAsyncKeyState(VK_SPACE)) {
			// Ahora, procedemos a verificar el estado del jugador.
			if (flags && (1 << 0)) { // Verificamos si flags es distinto a nulo y si el byte corresponde especificamente al estado de "Pisando el suelo". Hay distintos estados que están disponibles en el sdk del csgo.
				/*
				Ahora procedemos a escribir en la memoria la instruccion de saltar, ojo, es una INSTRUCCION del JUEGO, por lo tanto, debemos acceder a una funcion del JUEGO, no del JUGADOR.
				Por lo que accedemos desde la memoria BASE del juego y no desde la del JUGADOR como en los flags.
				*/
				// usamos -> mWrite<tipo de valor a escribir>(direccion de memoria, valor);
				tm->mWrite<INT>(tm->cDLL.dwBase + dwForceJump, 6); // OJO CON LA DIRECCION DE MEMORIA, ACCEDEMOS DESDE LA BASE DE CLIENT_PANORAMA.DLL + EL OFFSET DE LA INSTRUCCION DE FORZAR SALTO.
				// Escribimos el 6 por que el 6	 dentro de la SDK del juego, significa +jump por lo que saltará.
			}
			else {
				// Si no está en tierra, asumimos que está en el aire, por lo tanto vamos a escribir en la memoria el -jump.
			tm->mWrite<INT>(tm->cDLL.dwBase + dwForceJump, 4);
			}
		}
	}
	// Autobunny finalizado, facil.




	return 0;
}