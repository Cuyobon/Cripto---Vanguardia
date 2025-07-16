#include "Prerequisites.h"
#include "CesarEncryption.h"
#include "Vigenere.h"
#include "DES.h"
#include "AsciiBinary.h"
#include "XOREncoder.h"
#include <fstream>
#include <algorithm>
#include <map>


//Función para cargar claves desde un archivo de texto
//Las claves se puede modificar desde el archivo claves.txt
 
std::map<std::string, std::string> cargarClaves(const std::string& ruta) {
    std::map<std::string, std::string> claves;
    std::ifstream archivo(ruta);
    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t pos = linea.find('=');
        if (pos != std::string::npos) {
            std::string nombre = linea.substr(0, pos);
            std::string valor = linea.substr(pos + 1);
            claves[nombre] = valor;
        }
    }
    return claves;
}
/*
 Guarda contenido en un archivo de texto en la ruta indicada
 Si no puede abrirse el archivo, muestra un mensaje de error
 */
void guardarArchivo(const std::string& ruta, const std::string& contenido) {
    std::ofstream out(ruta);
    if (!out) {
        std::cerr << "No se pudo guardar el archivo: " << ruta << "\n";
        return;
    }
    out << contenido;
    out.close();
}

/*
 Lee el contenido de un archivo de texto y lo retorna como string
 Si no puede abrirse, devuelve una cadena vacía
 */
std::string leerArchivo(const std::string& ruta) {
    std::ifstream in(ruta);
    if (!in) {
        std::cerr << "No se pudo leer el archivo: " << ruta << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    in.close();
    return buffer.str();
}

/*
 Elimina espacios en blanco y saltos de línea de un texto
 Útil para comparar textos cifrados/descifrados ignorando formato.
 */
std::string limpiar(const std::string& texto) {
    std::string resultado = texto;
    resultado.erase(std::remove_if(resultado.begin(), resultado.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
        }), resultado.end());
    return resultado;
}

/*
 Verifica si el texto descifrado coincide con el original.
 Muestra mensaje en consola indicando si está correcto o no.
 */
void verificar(const std::string& nombre, const std::string& original, const std::string& descifrado) {
    std::cout << "\n--- Verificación: " << nombre << " ---\n";
    if (limpiar(original) == limpiar(descifrado)) {
        std::cout << "[OK] El contenido fue recuperado correctamente.\n";
    }
    else {
        std::cout << "[ERROR] El contenido NO coincide con el original.\n";
    }
}

/*
						ENCRIPTADO CÉSAR
 Realiza el cifrado y descifrado usando el algoritmo César.
 Lee texto de un archivo, lo cifra y descifra, guarda los resultados y verifica.
 */
void cifrarCesar(const std::string& clave) {
    if (clave.empty()) {
        std::cerr << "[ERROR] Clave para César vacía. Revisa claves.txt\n";
        return;
    }

    int desplazamiento = 0;
    try {
        desplazamiento = std::stoi(clave);
    }
    catch (...) {
        std::cerr << "[ERROR] Clave de César inválida (no es un número): " << clave << "\n";
        return;
    }

    CesarEncryption cesar;
    std::string entrada = leerArchivo("Folder1/datos_cesar.txt");
    std::string cifrado = cesar.encode(entrada, desplazamiento);
    std::string descifrado = cesar.decode(cifrado, desplazamiento);

    guardarArchivo("Folder2/cifrado_cesar.txt", cifrado);
    guardarArchivo("Folder2/descifrado_cesar.txt", descifrado);
    verificar("Cifrado César", entrada, descifrado);
}

/*
 						ENCRIPTADO XOR      
 Realiza cifrado y descifrado con algoritmo XOR.
 Aplica la clave dos veces (cifrar y descifrar) y verifica el resultado.
 */
void cifrarXOR(const std::string& clave) {
    if (clave.empty()) {
        std::cerr << "[ERROR] Clave XOR vacía. Revisa claves.txt\n";
        return;
    }

    XOREncoder xorEnc;
    std::string entrada = leerArchivo("Folder1/datos_xor.txt");
    if (clave.empty()) {
        std::cerr << "[ERROR] Clave XOR vacía.\n";
        return;
    }

    std::string cifrado = xorEnc.encode(entrada, clave);
    std::string descifrado = xorEnc.encode(cifrado, clave);

    guardarArchivo("Folder2/cifrado_xor.txt", cifrado);
    guardarArchivo("Folder2/descifrado_xor.txt", descifrado);
    verificar("Cifrado XOR", entrada, descifrado);
}

/*
					ENCRIPTADO VIGENÈRE
 Realiza el cifrado y descifrado usando el algoritmo Vigenère.
 Lee texto de archivo, cifra, descifra y guarda resultados.
 */
void cifrarVigenere(const std::string& clave) {
    if (clave.empty()) {
        std::cerr << "[ERROR] Clave para Vigenère vacía. Revisa claves.txt\n";
        return;
    }

    try {
        Vigenere vig(clave);
        std::string entrada = leerArchivo("Folder1/datos_vigenere.txt");
        std::string cifrado = vig.encode(entrada);
        std::string descifrado = vig.decode(cifrado);

        guardarArchivo("Folder2/cifrado_vigenere.txt", cifrado);
        guardarArchivo("Folder2/descifrado_vigenere.txt", descifrado);
        verificar("Cifrado Vigenère", entrada, descifrado);
    }
    catch (std::invalid_argument& e) {
        std::cerr << "[ERROR] Clave inválida para Vigenère: " << e.what() << "\n";
    }
}

/*
					ENCRIPTADO DES
 Realiza cifrado y descifrado con DES.
 Procesa texto en bloques de 8 bytes, cifra y descifra cada bloque.
 */
void cifrarDES(const std::string& claveBinaria) {
    if (claveBinaria.length() != 64 || claveBinaria.find_first_not_of("01") != std::string::npos) {
        std::cerr << "[ERROR] Clave DES inválida. Debe tener exactamente 64 bits en formato binario.\n";
        return;
    }

    std::string entrada = leerArchivo("Folder1/datos_des.txt");
    while (entrada.size() % 8 != 0) {
        entrada += '\0'; // Rellenar para completar bloques
    }

    std::bitset<64> claveBits(claveBinaria);
    DES des(claveBits);

    std::string cifrado, descifrado;

    for (size_t i = 0; i < entrada.size(); i += 8) {
        std::string bloque = entrada.substr(i, 8);
        auto bloqueBits = des.stringToBitset64(bloque);
        auto bloqueCifrado = des.encode(bloqueBits);
        cifrado += des.bitset64ToString(bloqueCifrado);
    }

    for (size_t i = 0; i < cifrado.size(); i += 8) {
        std::string bloque = cifrado.substr(i, 8);
        auto bloqueBits = des.stringToBitset64(bloque);
        auto bloqueDescifrado = des.decode(bloqueBits);
        descifrado += des.bitset64ToString(bloqueDescifrado);
    }

    guardarArchivo("Folder2/cifrado_des.txt", cifrado);
    guardarArchivo("Folder2/descifrado_des.txt", descifrado);
    verificar("Cifrado DES", entrada, descifrado);
}

/*
					CIFRADO BINARIO ASCII
 Realiza conversión de texto ASCII a binario y viceversa.
 Guarda archivos con el resultado de la conversión.
 */
void cifrarBinario() {
    AsciiBinary ascii;
    std::string entrada = leerArchivo("Folder1/datos_extra.txt");
    std::string cifrado = ascii.stringToBinary(entrada);
    std::string descifrado = ascii.binaryToString(cifrado);

    guardarArchivo("Folder2/cifrado_extra.txt", cifrado);
    guardarArchivo("Folder2/descifrado_extra.txt", descifrado);
    verificar("Cifrado Binario ASCII", entrada, descifrado);
}

// MAIN 

/*
                    Función principal.
 Carga las claves, ejecuta cada cifrado y verifica los resultados.
 */
int main() {
    std::cout << "=== Segundo Parcial - Cifrados múltiples ===\n";

    auto claves = cargarClaves("claves.txt");

    cifrarCesar(claves["cesar"]);
    cifrarXOR(claves["xor"]);
    cifrarVigenere(claves["vigenere"]);
    cifrarDES(claves["des"]);
    cifrarBinario(); // No necesita clave

    std::cout << "\nProceso completado.\n";
    return 0;
}
