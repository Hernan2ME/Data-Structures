SituacionDeJuego::SecuenciasOptimas SituacionDeJuego::ObtenerSecuenciasOptimas(int numero, bool esAtaque) const {
    SecuenciasOptimas secuenciasOptimas;

    // Obtener el jugador activo (el que conduce el balón)
    const Jugador& jugadorActivo = m_Jugadores[numero];

    // Crear una cola para realizar la búsqueda en anchura (BFS)
    std::queue<std::vector<int>> cola;

    // Agregar la secuencia inicial con el jugador activo a la cola
    cola.push(std::vector<int>{numero});

    while (!cola.empty()) {
        std::vector<int> secuenciaActual = cola.front();
        cola.pop();

        // Obtener el último jugador de la secuencia actual
        int ultimoJugador = secuenciaActual.back();

        // Verificar si se alcanzó el número máximo de pases en la secuencia
        if (secuenciaActual.size() >= numero) {
            secuenciasOptimas.push_back(NodoSecuenciasOptimas{ultimoJugador});
            continue;
        }

        // Obtener los posibles receptores para el siguiente pase
        for (int i = 0; i < m_Jugadores.size(); i++) {
            // Evitar pasar el balón al mismo jugador o a un jugador que ya ha recibido el balón en la secuencia actual
            if (i != ultimoJugador && std::find(secuenciaActual.begin(), secuenciaActual.end(), i) == secuenciaActual.end()) {
                // Calcular la efectividad del pase entre los jugadores
                const Jugador& receptor = m_Jugadores[i];
                float efectividad = jugadorActivo.CalcularEfectividadHasta(receptor);

                // Verificar si el pase es efectivo en función de si es un ataque o defensa
                if ((esAtaque && efectividad > receptor.ObtenerDesempenoAtaque()) || (!esAtaque && efectividad > receptor.ObtenerDesempenoDefensa())) {
                    // Agregar el receptor a la secuencia actual y agregarla a la cola para continuar la búsqueda
                    secuenciaActual.push_back(i);
                    cola.push(secuenciaActual);
                    secuenciaActual.pop_back();
                }
            }
        }
    }

    return secuenciasOptimas;
}
