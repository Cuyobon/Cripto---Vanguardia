# Proyecto de Cifrado y Descifrado - Segundo Parcial

Este programa permite cifrar y descifrar un archivo de texto utilizando el algoritmo de **Cifrado César**.

##  ¿Cómo funciona?

El programa realiza lo siguiente:

1. Lee un archivo de texto (`Folder1/datos.txt`) con datos sensibles simulados (como usuario, contraseña, correo).
2. Cifra el contenido utilizando el cifrado César con un desplazamiento de 3.
3. Guarda el resultado cifrado en `Folder2/datos_cif.txt`.
4. Descifra el archivo cifrado y guarda el resultado en `Folder2/datos_descif.txt`.
5. Verifica si el contenido original se recupera correctamente.


##  ¿Qué es el Cifrado César?

El cifrado César es un algoritmo de sustitución en el que cada letra del texto se reemplaza por otra que está un número fijo de posiciones más adelante en el alfabeto.  
Este programa también aplica el mismo desplazamiento a los números del texto.


## 📁 Estructura del Proyecto
      Proyecto/
      ├── Folder1/
      │ └── datos.txt ← Archivo original con información sensible
      ├── Folder2/
      │ ├── datos_cif.txt ← Archivo cifrado generado automáticamente
      │ └── datos_descif.txt ← Archivo descifrado para verificación
      ├── CesarEncryption.h ← Clase que implementa el cifrado y descifrado
      ├── Prerequisites.h ← Librerías estándar utilizadas
      ├── main.cpp ← Programa principal
      └── README.md ← Este archivo

## 🛠️ Instrucciones de Uso

### 1. Preparar el archivo a cifrar
Edita el archivo `Folder1/datos.txt` y escribe el contenido que quieres cifrar.  
Ejemplo:

usuario: usuariogenerico23
contraseña: contraseñagenerica25
correo: correogenerico@gmail,com

### 2. Compilar el programa

### 3. Revisar los resultados
El archivo cifrado estará en Folder2/datos_cif.txt
El archivo descifrado estará en Folder2/datos_descif.txt
La consola mostrará si el descifrado fue exitoso o no

* Requisitos Técnicos
      Proyecto en C++
      Reutiliza una clase de cifrado (César)
      Maneja archivos de entrada y salida
      Verifica que se recupere el contenido original

### Notas Adicionales
El desplazamiento usado en este ejemplo es 3, pero puede modificarse en el código (main.cpp).
Se ignoran espacios y saltos de línea al comparar los textos, para evitar errores por formato.

###
// Proyecto realizado por Cuyobon
// Basado en clases y ejemplos desarrollados por el profesor [@robertocharretonkaplun](https://github.com/robertocharretonkaplun)

// Código con fines educativos para el segundo parcial de Vanguardia Guerrero

