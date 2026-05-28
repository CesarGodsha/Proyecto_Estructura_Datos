Algoritmo CambiarEstadoProceso

    Definir idBuscado Como Entero
    Definir encontrado Como Logico
    Definir nuevoEstado Como Cadena

    encontrado <- Falso

    Escribir "===== CAMBIO DE ESTADO ====="

    Escribir "Ingrese el ID del proceso:"
    Leer idBuscado

    Escribir "Buscando proceso..."

    Si encontrado = Verdadero Entonces

        Escribir "Proceso encontrado"

        Escribir "Ingrese nuevo estado:"
        Leer nuevoEstado

        Escribir "Estado actualizado correctamente"

    SiNo

        Escribir "Proceso no encontrado"

    FinSi

FinAlgoritmo