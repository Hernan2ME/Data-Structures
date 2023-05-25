float Jugador::CalcularEfectividadHasta(const Jugador& otro) const {
    float distancia = std::sqrt(std::pow(m_PosX - otro.m_PosX, 2) + std::pow(m_PosY - otro.m_PosY, 2));
    // Mapear la distancia a un valor en el rango [0, 1]
    float efectividad = 1.0f - distancia / m_TamanoTerreno;
    return std::max(0.0f, std::min(efectividad, 1.0f)); // Asegurarse de que la efectividad esté en el rango correcto
}
