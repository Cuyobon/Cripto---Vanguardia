#pragma once
#include "Prerequisites.h"

class 
XOREncoder {
public:
  /**
  * @brief Constructor y destructor por omisión
  */
  XOREncoder() = default;
  ~XOREncoder() = default;

  /**
   * @brief Realiza codificación XOR sobre una cadena usando una clave específica.
   * @param input Texto de entrada a codificar. Ejemplo: "Hola Mundo"
   * @param key Clave utilizada para el proceso de codificación. Ejemplo: "clave"
   * @return Devuelve el resultado codificado como string.
   */
  std::string
  encode(const std::string& input, const std::string& key) {
    std::string output = input;
    for (int i = 0; i < input.size(); i++) {
      output[i] = input[i] ^ key[i % key.size()];
    }

    return output;
  }

  /**
   * @brief Convierte una cadena con valores hexadecimales en un arreglo de bytes.
   * @param input Entrada que representa valores en formato hexadecimal.
   * @return Vector resultante con los bytes convertidos.
   */
  std::vector<unsigned char>
  HexToBytes(const std::string& input) {
    std::vector<unsigned char> bytes;
    std::istringstream iss(input);
    std::string hexVal;

    while (iss >> hexVal) {
      if (hexVal.size() == 1) {
        hexVal = "0" + hexVal;
      }
      unsigned int byte;
      std::stringstream ss;
      ss << std::hex << hexVal;
      ss >> byte;
      bytes.push_back(static_cast<unsigned char>(byte));
    }
    return bytes;
  }

  /**
   * @brief Muestra cada carácter de una cadena en formato hexadecimal.
   * @param input Cadena a imprimir en consola como valores hexadecimales.
   */
  void
  printHex(const std::string& input) {
    for (unsigned char c : input) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    }
  }

  /**
   * @brief Determina si el texto contiene únicamente caracteres legibles.
   * @param data Cadena a comprobar.
   * @return true si todos los caracteres son válidos, false si no.
   */
  bool 
  isValidText(const std::string& data) {
    return std::all_of(data.begin(), data.end(), [](unsigned char c) {
      return isprint(c) || isspace(c) || c == '\n' || c == ' ';
      });
  }

  /**
   * @brief Realiza un ataque de fuerza bruta usando claves de un solo byte.
   * @param cifrado Vector de bytes con el texto codificado.
   */
  void
  bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
    for (int clave = 0; clave < 256; clave++) {
      std::string result;

      for (unsigned char c : cifrado) {
        result += c ^ clave;
      }

      if (isValidText(result)) {
        std::cout << "============================\n";
        std::cout << "Clave 1 byte: " << static_cast<char>(clave)
          << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
        std::cout << "Texto posible: " << result << "\n";
      }
    }
  }

  /**
   * @brief Fuerza bruta para probar combinaciones de claves de 2 bytes.
   * @param cifrado Texto cifrado como arreglo de bytes.
   */
  void
  bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {
    for (int b1 = 0; b1 < 256; b1++) {
      for (int b2 = 0; b2 < 256; b2++) {
        std::string result;
        unsigned char key[2] = { static_cast<unsigned char>(b1), static_cast<unsigned char>(b2) };

        for (int i = 0; i < cifrado.size(); i++) {
          result += cifrado[i] ^ key[i % 2];
        }
        
        if (isValidText(result)) {
          std::cout << "============================\n";
          std::cout << "Clave 2 bytes: " << static_cast<char>(b1) << static_cast<char>(b2)
            << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
            << "0x " << std::setw(2) << std::setfill('0') << b2 << ")\n";
          std::cout << "Texto posible: " << result << "\n";
        }
      }
    }
  }

  /**
   * @brief Prueba claves comunes desde un diccionario para descifrar un mensaje.
   * @param cifrado Texto cifrado representado como bytes.
   */
  void 
  bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
    std::vector<std::string> clavesComunes = {
      "clave", "admin", "1234", "root", "test", "abc", "hola", "user",
      "pass", "12345", "0000", "password", "default", "Koromaru", "Sans e e e e e"
    };

    for (const auto& clave : clavesComunes) {
      std::string result;
      for (int i = 0; i < cifrado.size(); i++) {
        result += static_cast<unsigned char>(cifrado[i] ^ clave[i & clave.size()]);
      }

      if (isValidText(result)) {
        std::cout << "============================\n";
        std::cout << "Clave de diccionario: " << clave << "\n";
        std::cout << "Texto posible: " << result << "\n";
      }
    }
  }

  /**
   * @brief Aplica fuerza bruta utilizando listas externas de contraseñas filtradas.
   * @param cifrado Vector de bytes que representa el texto cifrado.
   * @param mensajeOG Texto original esperado; si coincide, se considera éxito.
   * 
   * Listas obtenidas de: https://github.com/danielmiessler/SecLists/tree/master/Passwords/Leaked-Databases
   */
  void
  bruteForceByFile(const std::vector<unsigned char>& cifrado, const std::string& mensajeOG) {
    std::vector<std::string> fileNames = {
        "bin/adobe100.txt",
        "bin/bible.txt",
        "bin/elitehacker.txt",
        "bin/fortinet-2021_passwords.txt",
        "bin/Lizard-Squad.txt"
    };

    for (size_t i = 0; i < fileNames.size(); i++) {
      std::ifstream file(fileNames[i]);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << fileNames[i] << std::endl;
        continue;
      }

      std::string clave;
      while (std::getline(file, clave)) {
        if (clave.empty()) {
          continue;
        }

        std::string result;
        for (int j = 0; j < cifrado.size(); j++) {
          result += static_cast<unsigned char>(cifrado[j] ^ clave[j % clave.size()]);
        }

        if (isValidText(result) && result == mensajeOG) {
          std::cout << "============================\n";
          std::cout << "Archivo: " << fileNames[i] << std::endl;
          std::cout << "Clave: " << clave << std::endl;
          std::cout << "Texto posible: " << result << std::endl;
          return;
        }
      }
      file.close();
    }
  }

private:

};
