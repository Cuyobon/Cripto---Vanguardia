#pragma once
#include "Prerequisites.h"

class
AsciiBinary {
public:
  /**
   * @brief Constructor y destructor por defecto.
   */
  AsciiBinary() = default;
  ~AsciiBinary() = default;

  /**
   * @brief Convierte un carácter ASCII a su representación binaria de 8 bits.
   * @param c Carácter a convertir.
   * @return Cadena de 8 caracteres que representa el valor binario.
   */
  std::string
  bitset(char c) {
    std::string result(8, '0');
    int value = static_cast<unsigned char>(c);
    for (int i = 7; i >= 0; --i) {
      if (value % 2 == 1) {
        result[i] = '1';
      }
      value /= 2;
    }
    return result;
  }

  /**
   * @brief Convierte una cadena de texto a su representación binaria.
   * @param input Texto a convertir.
   * @return Cadena con valores binarios separados, donde cada carácter ocupa 8 bits.
   */
  std::string
  stringToBinary(const std::string input) {
    std::ostringstream oss;
    for (char c : input) {
      oss << bitset(c) << " ";
    }
    return oss.str();
  }

  /**
   * @brief Convierte una cadena de 8 bits a su carácter ASCII equivalente.
   * @param binary Cadena de 8 bits a convertir.
   * @return Carácter correspondiente al valor binario ingresado.
   */
  char 
  binaryToChar(const std::string& binary) {
    int value = 0;
    for (char bit : binary) {
      value = value * 2 + (bit - '0');
    }

    return static_cast<char>(value);
  }

  /**
   * @brief Convierte una cadena compuesta por múltiples bloques de 8 bits a texto ASCII.
   * @param binaryInput Cadena binaria (ej.: "01001000 01101111 ...").
   * @return Texto resultante de convertir cada bloque a su carácter correspondiente.
   */
  std::string
  binaryToString(const std::string& binaryInput) {
    std::istringstream iss(binaryInput);
    std::string result;
    std::string binary;

    while (iss >> binary) {
      result += binaryToChar(binary);
    }
    return result;
  }

private:

};
