#pragma once

#include "Prerequisites.h"

class CesarEncryption {
public:
    CesarEncryption() = default;
    ~CesarEncryption() = default;

    // Método para cifrar texto usando cifrado César
    std::string encode(const std::string& texto, int desplazamiento) {
        std::string result = "";

        for (char c : texto) {
            if (c >= 'A' && c <= 'Z') {
                result += (char)(((c - 'A' + desplazamiento) % 26) + 'A');
            }
            else if (c >= 'a' && c <= 'z') {
                result += (char)(((c - 'a' + desplazamiento) % 26) + 'a');
            }
            else if (c >= '0' && c <= '9') {
                result += (char)(((c - '0' + desplazamiento) % 10) + '0');
            }
            else {
                result += c;
            }
        }

        return result;
    }

    // Método para descifrar texto cifrado con César
    std::string decode(const std::string& texto, int desplazamiento) {
        std::string result = "";

        for (char c : texto) {
            if (c >= 'A' && c <= 'Z') {
                result += (char)(((c - 'A' - desplazamiento + 26) % 26) + 'A');
            }
            else if (c >= 'a' && c <= 'z') {
                result += (char)(((c - 'a' - desplazamiento + 26) % 26) + 'a');
            }
            else if (c >= '0' && c <= '9') {
                result += (char)(((c - '0' - desplazamiento + 10) % 10) + '0');
            }
            else {
                result += c;
            }
        }

        return result;
    }

    // Prueba de fuerza bruta para descifrar
    void bruteForceAttack(const std::string& texto) {
        std::cout << "\nIntentos de descifrado por fuerza bruta:\n";
        for (int clave = 0; clave < 26; clave++) {
            std::string intento = decode(texto, clave);
            std::cout << "Clave " << clave << ": " << intento << std::endl;
        }
    }

    // Estimación de clave usando análisis de frecuencia
    int evaluatePossibleKey(const std::string& texto) {
        int frecuencias[26] = { 0 };

        for (char c : texto) {
            if (c >= 'a' && c <= 'z') {
                frecuencias[c - 'a']++;
            }
            else if (c >= 'A' && c <= 'Z') {
                frecuencias[c - 'A']++;
            }
        }

        const char letrasEsp[] = { 'e', 'a', 'o', 's', 'r', 'n', 'i', 'd', 'l', 'c' };

        int indiceMax = 0;
        for (int i = 1; i < 26; ++i) {
            if (frecuencias[i] > frecuencias[indiceMax]) {
                indiceMax = i;
            }
        }

        int mejorClave = 0;
        int mejorPuntaje = -1;

        for (char letraRef : letrasEsp) {
            int clave = (indiceMax - (letraRef - 'a') + 26) % 26;
            int puntaje = 0;

            std::string descifrado = decode(texto, clave);
            std::string comunes[] = { "el", "de", "la", "que", "en", "y", "los", "se" };

            for (const std::string& palabra : comunes) {
                if (descifrado.find(palabra) != std::string::npos) {
                    puntaje++;
                }
            }

            if (puntaje > mejorPuntaje) {
                mejorPuntaje = puntaje;
                mejorClave = clave;
            }
        }

        return mejorClave;
    }

private:
    // No hay atributos privados necesarios para esta clase
};
