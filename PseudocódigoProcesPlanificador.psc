Algoritmo AgregarProceso

    Definir id, prioridad, tiempo Como Entero
    Definir nombre Como Cadena
    Definir colaVacia Como Logico

    colaVacia <- Falso

    Escribir "===== REGISTRO DE PROCESO ====="

    Escribir "Ingrese ID:"
    Leer id

    Escribir "Ingrese nombre:"
    Leer nombre

    Escribir "Ingrese prioridad:"
    Leer prioridad

    Escribir "Ingrese tiempo de ejecucion:"
    Leer tiempo

    Si colaVacia Entonces

        Escribir "Proceso insertado al inicio"

    SiNo

        Escribir "Proceso insertado al final de la cola"

    FinSi

    Escribir "Proceso agregado correctamente"

FinAlgoritmo