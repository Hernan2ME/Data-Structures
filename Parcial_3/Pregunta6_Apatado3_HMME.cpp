SituacionDeJuego::SecuenciaOptima SituacionDeJuego::ObtenerSecuenciaOptima(int numero, bool esAtaque) const {
    SecuenciasOptimas secuenciasOptimas = ObtenerSecuenciasOptimas(numero, esAtaque);

    SecuenciaOptima mejorSecuencia;
    float mejorProbabilidadFinal = 0.0f;

    // Recorrer las secuencias óptimas y encontrar la que tenga la probabilidad final más alta
    for (const auto& secuencia : secuenciasOptimas) {
        float probabilidadFinal = 1.0f;

        for (int i = 0; i < secuencia.Secuencia.size(); i++) {
            const Jugador& jugadorActual = m_Jugadores[secuencia.Secuencia[i]];
            const Jugador& jugadorSiguiente = m_Jugadores[secuencia.Secuencia[(i + 1) % secuencia.Secuencia.size()]];
            probabilidadFinal *= jugadorActual.CalcularEfectividadHasta(jugadorSiguiente);
        }

        if (probabilidadFinal > mejorProbabilidadFinal) {
            mejorProbabilidadFinal = probabilidadFinal;
            mejorSecuencia.Secuencia = secuencia.Secuencia;
            mejorSecuencia.ProbabilidadFinal = probabilidadFinal;
            mejorSecuencia.TodosLosJugadores = (secuencia.Secuencia.size() == m_Jugadores.size());
        }
    }

    return mejorSecuencia;
}
