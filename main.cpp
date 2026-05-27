#include <iostream>

using namespace std;

#define MAX 50

struct Paquete {
    int id;
    char destino[50];
    float peso;
};

Paquete pila[MAX];
int tope = -1;

bool estavacia() {
    return tope == -1;
}

void insertar(Paquete dato) {
    if (tope == MAX - 1) {
        cout << "La pila está llena. No se puede insertar más elementos." << endl;
    } else {
        tope++;
        pila[tope] = dato;
        cout << "Paquete ID " << dato.id << " insertado." << endl;
    }
}

void eliminar() {
    if (tope == -1) {
        cout << "La pila está vacía. No se puede hacer eliminar." << endl;
    } else {
        cout << "Paquete ID " << pila[tope].id << " eliminado." << endl;
        tope--;
    }
}

// DEFINIDA COMO INT: Devuelve el ID del paquete en la cima
int cima() {
    if (tope == -1) {
        return -1; 
    }
    return pila[tope].id; // Retorna un entero (el ID) tal como pide el ejemplo
}

void imprimir() {
    if (estavacia()) {
        cout << "La pila está vacía." << endl;
    } else {
        cout << "Contenido de la pila (de cima a base): " << endl;
        for (int i = tope; i >= 0; i--) {
            cout << "ID: " << pila[i].id << " | Destino: " << pila[i].destino << " | Peso: " << pila[i].peso << " kg" << endl;
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_CTYPE, "Spanish");
    int opcion;

    Paquete pTemp;
    Paquete pilaAux[MAX];
    int topeAux;
    bool encontrado;
    int idBuscar;
    float pesoLimite;

    do {
        cout << "\n====================================";
        cout << "\n     SISTEMA DE ENVIOS   ";
        cout << "\n====================================";
        cout << "\n[1] Registro de datos ";
        cout << "\n[2] Ordenamiento ";
        cout << "\n[3] Búsqueda ";
        cout << "\n[4] Actualización ";
        cout << "\n[5] Eliminación según criterio ";
        cout << "\n[6] Mostrar datos";
        cout << "\n[7] Salir";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // ==========================================
                // ESTRUCTURA: REGISTRO DE DATOS
                // ==========================================
                cout << "\n--- REGISTRAR PAQUETE ---\n";
                cout << "Ingrese ID: ";
                cin >> pTemp.id;
                cin.ignore();
                cout << "Ingrese Destino: ";
                cin.getline(pTemp.destino, 50);
                cout << "Ingrese Peso (kg): ";
                cin >> pTemp.peso;
                insertar(pTemp);
                break;

            case 2:
                // ==========================================
                // ESTRUCTURA: ORDENAMIENTO
                // ==========================================
                if (estavacia()) {
                    cout << "La pila está vacía. No se puede ordenar." << endl;
                } else {
                    topeAux = -1;
                    while (tope != -1) {
                        Paquete temporal = pila[tope]; // Guardamos el paquete completo
                        eliminar();

                        while (topeAux != -1 && pilaAux[topeAux].peso < temporal.peso) {
                            insertar(pilaAux[topeAux]);
                            topeAux--;
                        }
                        topeAux++;
                        pilaAux[topeAux] = temporal;
                    }
                    while (topeAux != -1) {
                        insertar(pilaAux[topeAux]);
                        topeAux--;
                    }
                    cout << "Pila ordenada por peso correctamente." << endl;
                }
                break;

            case 3:
                // ==========================================
                // ESTRUCTURA: BÚSQUEDA
                // ==========================================
                if (estavacia()) {
                    cout << "La pila está vacía." << endl;
                } else {
                    cout << "Ingrese el ID a buscar: ";
                    cin >> idBuscar;
                    encontrado = false;
                    topeAux = -1;

                    while (tope != -1) {
                        // Usamos cima() para comparar el entero (ID) de forma exacta a tu ejemplo
                        if (cima() == idBuscar) { 
                            encontrado = true;
                            pTemp = pila[tope]; 
                        }
                        topeAux++;
                        pilaAux[topeAux] = pila[tope];
                        eliminar();
                    }
                    while (topeAux != -1) {
                        insertar(pilaAux[topeAux]);
                        topeAux--;
                    }

                    if (encontrado) {
                        cout << "\n[Paquete Encontrado]\n";
                        cout << "ID: " << pTemp.id << "\nDestino: " << pTemp.destino << "\nPeso: " << pTemp.peso << " kg\n";
                    } else {
                        cout << "Paquete con ID " << idBuscar << " no encontrado." << endl;
                    }
                }
                break;

            case 4:
                // ==========================================
                // ESTRUCTURA: ACTUALIZACIÓN
                // ==========================================
                if (estavacia()) {
                    cout << "La pila está vacía." << endl;
                } else {
                    cout << "Ingrese el ID a actualizar: ";
                    cin >> idBuscar;
                    encontrado = false;
                    topeAux = -1;

                    while (tope != -1) {
                        Paquete actual = pila[tope];
                        // Usamos cima() para comparar el ID entero
                        if (cima() == idBuscar) { 
                            cout << "Paquete encontrado. Ingrese el nuevo destino: ";
                            cin.ignore();
                            cin.getline(actual.destino, 50);
                            encontrado = true;
                        }
                        topeAux++;
                        pilaAux[topeAux] = actual;
                        eliminar();
                    }
                    while (topeAux != -1) {
                        insertar(pilaAux[topeAux]);
                        topeAux--;
                    }

                    if (encontrado) {
                        cout << "¡Destino actualizado con éxito!" << endl;
                    } else {
                        cout << "Paquete con ID " << idBuscar << " no encontrado." << endl;
                    }
                }
                break;

            case 5:
                // ==========================================
                // ESTRUCTURA: ELIMINACIÓN SEGÚN CRITERIO
                // ==========================================
                if (estavacia()) {
                    cout << "La pila está vacía." << endl;
                } else {
                    cout << "Ingrese el peso máximo permitido: ";
                    cin >> pesoLimite;
                    topeAux = -1;

                    while (tope != -1) {
                        if (pila[tope].peso > pesoLimite) {
                            // Imprimimos usando cima() para mostrar el ID entero que se va a ir
                            cout << "Paquete ID " << cima() << " superó el límite (" << pila[tope].peso << " kg). ";
                            eliminar();
                        } else {
                            topeAux++;
                            pilaAux[topeAux] = pila[tope];
                            eliminar();
                        }
                    }
                    while (topeAux != -1) {
                        insertar(pilaAux[topeAux]);
                        topeAux--;
                    }
                }
                break;

            case 6:
                // ==========================================
                // ESTRUCTURA: MOSTRAR DATOS
                // ==========================================
                imprimir();
                break;

            case 7:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }
    } while (opcion != 7);

    return 0;
}