#include "Prerequisites.h"
#include "CesarEncryption.h"
#include <fstream>
#include <algorithm>

// Guarda el .txt
void guardarArchivo(const std::string& ruta, const std::string& contenido) {
    std::ofstream out(ruta);
    if (!out) {
        std::cerr << "No se pudo guardar el archivo: " << ruta << "\n";
        return;
    }
    out << contenido;
    out.close();
}

// Lee el .txt
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

// Quita espacios, saltos de línea, etc.
std::string limpiar(const std::string& texto) {
    std::string resultado = texto;
    resultado.erase(std::remove_if(resultado.begin(), resultado.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
        }), resultado.end());
    return resultado;
}

int main() {
    CesarEncryption cesar;
    std::string archivoOriginal = "Folder1/datos.txt";
    std::string archivoCifrado = "Folder2/datos_cif.txt";
    std::string archivoDescifrado = "Folder2/datos_descif.txt";

    int desplazamiento = 3; // Desplazamiento 

    // Leer el .txt original
    std::string contenido = leerArchivo(archivoOriginal);
    if (contenido.empty()) {
        std::cerr << "No se pudo leer el archivo original.\n";
        return 1;
    }

    // Cifrar el contenido
    std::string cifrado = cesar.encode(contenido, desplazamiento);
    guardarArchivo(archivoCifrado, cifrado);
    std::cout << "Archivo cifrado guardado en: " << archivoCifrado << "\n";

    // Descifrar para verificar
    std::string contenidoDescifrado = cesar.decode(cifrado, desplazamiento);
    guardarArchivo(archivoDescifrado, contenidoDescifrado);
    std::cout << "Archivo descifrado guardado en: " << archivoDescifrado << "\n";

    // Mostrar ambos textos para comparar
    std::cout << "\n--- Contenido original ---\n" << contenido << "\n";
    std::cout << "--- Contenido descifrado ---\n" << contenidoDescifrado << "\n";

    // Comparación ignorando espacios y saltos de línea
    if (limpiar(contenido) == limpiar(contenidoDescifrado)) {
        std::cout << "\nTodo bien: el contenido original se recuperó correctamente.\n";
    }
    else {
        std::cout << "\nAlgo salió mal: el contenido descifrado no coincide con el original.\n";
    }

    return 0;
}
