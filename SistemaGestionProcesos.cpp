// ============================================================
//  SISTEMA DE GESTION DE PROCESOS
//  Universidad Continental - Estructura de Datos
//  NRC: 28648 | Huancayo - Peru | 2026
//  Integrantes:
//    - Torres Rojas Cesar Kevin
//    - Romero Samaniego Jhonatan
//    - Ccencho Gamarra Fernando
//    - Martinez Huancaya Jeimy
// ============================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX 100

// ============================================================
//  VARIABLES GLOBALES - LISTA ENLAZADA (Gestor Central)
// ============================================================
int  lista_id[MAX];
char lista_nombre[MAX][50];
int  lista_prioridad[MAX];
char lista_estado[MAX][20];
int  totalLista = 0;

// ============================================================
//  VARIABLES GLOBALES - COLA DE PRIORIDAD (Planificador CPU)
// ============================================================
int  cola_id[MAX];
char cola_nombre[MAX][50];
int  cola_prioridad[MAX];
char cola_estado[MAX][20];
int  totalCola = 0;

// ============================================================
//  VARIABLES GLOBALES - PILA (Gestor de Memoria)
// ============================================================
int  pila_id[MAX];
char pila_nombre[MAX][50];
char pila_estado[MAX][20];
int  topePila = 0;

// ============================================================
//  ESTRUCTURA 1: LISTA ENLAZADA - Gestor Central
// ============================================================

// Verifica si un ID ya existe en la lista
// WHILE: recorre todos los elementos registrados uno por uno
int existeEnLista(int id) {
    int i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) return 1;
        i = i + 1;
    }
    return 0;
}

// Inserta un nuevo proceso en la lista
// IF: valida que no haya duplicados ni desbordamiento
void insertarEnLista(int id, char nombre[], int prioridad) {
    if (totalLista >= MAX) {
        cout << "  [ERROR] Lista llena.\n"; return;
    }
    if (existeEnLista(id)) {
        cout << "  [ERROR] El ID " << id << " ya esta registrado.\n"; return;
    }
    lista_id[totalLista]        = id;
    strcpy(lista_nombre[totalLista], nombre);
    lista_prioridad[totalLista] = prioridad;
    strcpy(lista_estado[totalLista], "Listo");
    totalLista = totalLista + 1;
    cout << "  [OK] Proceso incorporado al Gestor Central.\n";
}

// Elimina un proceso buscando su ID
// WHILE: busca la posicion, FOR: reorganiza el arreglo
void eliminarDeLista(int id) {
    int pos = -1, i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) { pos = i; break; }
        i = i + 1;
    }
    if (pos == -1) { cout << "  [ERROR] ID no encontrado.\n"; return; }
    for (int j = pos; j < totalLista - 1; j = j + 1) {
        lista_id[j]        = lista_id[j+1];
        strcpy(lista_nombre[j], lista_nombre[j+1]);
        lista_prioridad[j] = lista_prioridad[j+1];
        strcpy(lista_estado[j], lista_estado[j+1]);
    }
    totalLista = totalLista - 1;
    cout << "  [OK] Proceso ID " << id << " eliminado.\n";
}

// Busca un proceso por ID - WHILE: recorrido secuencial
void buscarPorID(int id) {
    int i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) {
            cout << "  [ENCONTRADO] ID: " << lista_id[i]
                 << " | Nombre: "    << lista_nombre[i]
                 << " | Prioridad: " << lista_prioridad[i]
                 << " | Estado: "    << lista_estado[i] << "\n";
            return;
        }
        i = i + 1;
    }
    cout << "  [NO ENCONTRADO] El ID " << id << " no existe.\n";
}

// Busca un proceso por nombre
// WHILE: recorrido, strcmp: compara cadenas caracter a caracter
void buscarPorNombre(char nombre[]) {
    int i = 0;
    while (i < totalLista) {
        if (strcmp(lista_nombre[i], nombre) == 0) {
            cout << "  [ENCONTRADO] ID: " << lista_id[i]
                 << " | Prioridad: " << lista_prioridad[i]
                 << " | Estado: "    << lista_estado[i] << "\n";
            return;
        }
        i = i + 1;
    }
    cout << "  [NO ENCONTRADO]\n";
}

// Modifica la prioridad - WHILE: busca el proceso por ID
void modificarPrioridad(int id, int nueva) {
    int i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) {
            lista_prioridad[i] = nueva;
            cout << "  [OK] Prioridad actualizada a " << nueva << ".\n";
            return;
        }
        i = i + 1;
    }
    cout << "  [ERROR] ID no encontrado.\n";
}

// Muestra todos los procesos - FOR: recorre todos los elementos
void mostrarLista() {
    if (totalLista == 0) { cout << "  Lista vacia.\n"; return; }
    cout << "  ID  | Nombre          | Prior | Estado\n";
    cout << "  ----|-----------------|-------|----------\n";
    for (int i = 0; i < totalLista; i = i + 1)
        cout << "  " << lista_id[i]       << "\t| "
             << lista_nombre[i]    << "\t| "
             << lista_prioridad[i] << "\t| "
             << lista_estado[i]    << "\n";
    cout << "  Total: " << totalLista << " proceso(s).\n";
}

// ============================================================
//  ESTRUCTURA 2: COLA DE PRIORIDAD - Planificador CPU
// ============================================================

// Encola segun prioridad (mayor = primero)
// WHILE: encuentra posicion correcta, FOR: desplaza elementos
void encolarPlanificador(int id, char nombre[], int prioridad) {
    if (totalCola >= MAX) { cout << "  [ERROR] Cola llena.\n"; return; }
    int posicion = 0;
    while (posicion < totalCola && cola_prioridad[posicion] >= prioridad)
        posicion = posicion + 1;
    for (int j = totalCola; j > posicion; j = j - 1) {
        cola_id[j]        = cola_id[j-1];
        strcpy(cola_nombre[j], cola_nombre[j-1]);
        cola_prioridad[j] = cola_prioridad[j-1];
        strcpy(cola_estado[j], cola_estado[j-1]);
    }
    cola_id[posicion]        = id;
    strcpy(cola_nombre[posicion], nombre);
    cola_prioridad[posicion] = prioridad;
    strcpy(cola_estado[posicion], "Listo");
    totalCola = totalCola + 1;
    cout << "  [OK] Proceso encolado en posicion " << posicion+1 << ".\n";
}

// Despacha el proceso de mayor prioridad (frente)
// IF: validacion de robustez anti-caidas, FOR: reorganiza cola
void despacharCPU() {
    if (totalCola == 0) {
        cout << "  [VALIDACION] No hay tareas pendientes.\n"; return;
    }
    cout << "  [CPU] Despachando -> ID: " << cola_id[0]
         << " | " << cola_nombre[0] << " | EN EJECUCION\n";
    // PUSH automatico: asigna memoria al proceso despachado
    if (topePila < MAX) {
        pila_id[topePila] = cola_id[0];
        strcpy(pila_nombre[topePila], cola_nombre[0]);
        strcpy(pila_estado[topePila], "En Ejecucion");
        topePila = topePila + 1;
        cout << "  [RAM] Bloque de memoria asignado.\n";
    }
    for (int i = 0; i < totalCola - 1; i = i + 1) {
        cola_id[i]        = cola_id[i+1];
        strcpy(cola_nombre[i], cola_nombre[i+1]);
        cola_prioridad[i] = cola_prioridad[i+1];
        strcpy(cola_estado[i], cola_estado[i+1]);
    }
    totalCola = totalCola - 1;
}

// Muestra la cola - FOR: recorre de mayor a menor prioridad
void mostrarCola() {
    if (totalCola == 0) { cout << "  Cola vacia.\n"; return; }
    cout << "  Pos | ID  | Nombre          | Prioridad\n";
    cout << "  ----|-----|-----------------|----------\n";
    for (int i = 0; i < totalCola; i = i + 1)
        cout << "  " << i+1         << "\t| "
             << cola_id[i]       << "\t| "
             << cola_nombre[i]   << "\t| "
             << cola_prioridad[i] << "\n";
    cout << "  En espera: " << totalCola << " proceso(s).\n";
}

// ============================================================
//  ESTRUCTURA 3: PILA - Gestor de Memoria RAM
// ============================================================

// PUSH: apila un bloque de memoria - IF: valida pila no llena
void pushMemoria(int id, char nombre[]) {
    if (topePila >= MAX) { cout << "  [ERROR] Memoria llena.\n"; return; }
    pila_id[topePila] = id;
    strcpy(pila_nombre[topePila], nombre);
    strcpy(pila_estado[topePila], "En Ejecucion");
    topePila = topePila + 1;
    cout << "  [RAM] Bloque asignado al Proceso ID: " << id << "\n";
}

// POP: libera el tope - IF: validacion anti-caidas (pila vacia)
void popMemoria() {
    if (topePila == 0) {
        cout << "  [ERROR DE PROTECCION] Pila vacia.\n"; return;
    }
    topePila = topePila - 1;
    cout << "  [RAM] Bloque liberado del Proceso ID: "
         << pila_id[topePila] << "\n";
}

// Muestra la pila - FOR: recorre desde el tope hacia la base
void mostrarPila() {
    if (topePila == 0) { cout << "  Pila vacia. Memoria libre.\n"; return; }
    cout << "  Nivel | ID  | Nombre          | Estado\n";
    cout << "  ------|-----|-----------------|----------\n";
    for (int i = topePila - 1; i >= 0; i = i - 1)
        cout << "  " << topePila-i << "\t| "
             << pila_id[i]     << "\t| "
             << pila_nombre[i] << "\t| "
             << pila_estado[i] << "\n";
    cout << "  Bloques en uso: " << topePila << "\n";
}

// ============================================================
//  PERSISTENCIA
// ============================================================
void guardarEstado() {
    ofstream f("procesos.txt");
    for (int i = 0; i < totalLista; i = i + 1)
        f << lista_id[i]       << "|"
          << lista_nombre[i]   << "|"
          << lista_prioridad[i] << "|"
          << lista_estado[i]   << "\n";
    f.close();
    cout << "  [OK] Guardado en 'procesos.txt' (" << totalLista << " procesos).\n";
}

void cargarEstado() {
    ifstream f("procesos.txt");
    if (!f) { cout << "  [INFO] Sin archivo previo. Sistema limpio.\n"; return; }
    int  id, prio, cargados = 0;
    char nom[50], est[20], sep;
    while (f >> id >> sep) {
        f.getline(nom, 50, '|');
        f >> prio >> sep;
        f.getline(est, 20);
        if (!existeEnLista(id)) {
            insertarEnLista(id, nom, prio);
            strcpy(lista_estado[totalLista-1], est);
            cargados = cargados + 1;
        }
    }
    f.close();
    cout << "  [OK] " << cargados << " proceso(s) cargados.\n";
}

// ============================================================
//  UTILIDADES
// ============================================================
void pausa() {
    cout << "\n  Presione ENTER para continuar...";
    cin.ignore(); cin.get();
}

void cabecera(const char titulo[]) {
    system("cls");
    cout << "\n  ================================================\n";
    cout << "   SISTEMA DE GESTION DE PROCESOS | NRC 28648\n";
    cout << "  ================================================\n";
    cout << "   " << titulo << "\n";
    cout << "  ================================================\n\n";
}

// ============================================================
//  MENUS
// ============================================================
void menuLista() {
    int op, id, prio; char nom[50];
    do {
        cabecera("1. GESTOR DE PROCESOS  [Lista Enlazada]");
        cout << "  1. Registrar proceso\n  2. Eliminar proceso\n";
        cout << "  3. Buscar por ID\n  4. Buscar por nombre\n";
        cout << "  5. Modificar prioridad\n  6. Mostrar todos\n  0. Volver\n\n  >> ";
        cin >> op;
        if      (op == 1) { cout << "  ID: "; cin >> id; cout << "  Nombre: "; cin >> nom; cout << "  Prioridad: "; cin >> prio; insertarEnLista(id, nom, prio); }
        else if (op == 2) { cout << "  ID: "; cin >> id; eliminarDeLista(id); }
        else if (op == 3) { cout << "  ID: "; cin >> id; buscarPorID(id); }
        else if (op == 4) { cout << "  Nombre: "; cin >> nom; buscarPorNombre(nom); }
        else if (op == 5) { cout << "  ID: "; cin >> id; cout << "  Nueva prioridad: "; cin >> prio; modificarPrioridad(id, prio); }
        else if (op == 6) { mostrarLista(); }
        if (op != 0) pausa();
    } while (op != 0);
}

void menuCola() {
    int op, id, prio; char nom[50];
    do {
        cabecera("2. PLANIFICADOR CPU  [Cola de Prioridad]");
        cout << "  1. Encolar proceso\n  2. Despachar a CPU\n  3. Ver cola\n  0. Volver\n\n  >> ";
        cin >> op;
        if      (op == 1) { cout << "  ID: "; cin >> id; cout << "  Nombre: "; cin >> nom; cout << "  Prioridad: "; cin >> prio; encolarPlanificador(id, nom, prio); }
        else if (op == 2) { despacharCPU(); }
        else if (op == 3) { mostrarCola(); }
        if (op != 0) pausa();
    } while (op != 0);
}

void menuPila() {
    int op, id; char nom[50];
    do {
        cabecera("3. GESTOR DE MEMORIA  [Pila LIFO]");
        cout << "  1. Ver estado de memoria\n  2. Asignar memoria - PUSH\n  3. Liberar memoria - POP\n  0. Volver\n\n  >> ";
        cin >> op;
        if      (op == 1) { mostrarPila(); }
        else if (op == 2) { cout << "  ID: "; cin >> id; cout << "  Nombre: "; cin >> nom; pushMemoria(id, nom); }
        else if (op == 3) { popMemoria(); }
        if (op != 0) pausa();
    } while (op != 0);
}

// ============================================================
//  PROGRAMA PRINCIPAL
// ============================================================
int main() {
    cargarEstado(); pausa();
    int op;
    do {
        cabecera("MENU PRINCIPAL");
        cout << "  1. Gestor de Procesos    [Lista Enlazada]\n";
        cout << "  2. Planificador CPU      [Cola de Prioridad]\n";
        cout << "  3. Gestor de Memoria     [Pila LIFO]\n";
        cout << "  4. Guardar estado\n";
        cout << "  5. Ver resumen\n";
        cout << "  0. Salir\n\n  >> ";
        cin >> op;
        if      (op == 1) menuLista();
        else if (op == 2) menuCola();
        else if (op == 3) menuPila();
        else if (op == 4) { guardarEstado(); pausa(); }
        else if (op == 5) {
            cabecera("RESUMEN DEL SISTEMA");
            cout << "  Procesos registrados : " << totalLista << "\n";
            cout << "  En cola CPU          : " << totalCola  << "\n";
            cout << "  Bloques RAM en uso   : " << topePila   << "\n\n";
            mostrarLista(); pausa();
        }
    } while (op != 0);
    cout << "\n  Guardando y saliendo...\n";
    guardarEstado();
    return 0;
}
