#include <iostream>
using namespace std;

#define MAX 100

// ============================================================
//  FUNCIONES MANUALES (sin cstring / cstdlib)
// ============================================================

// Compara dos cadenas; retorna 0 si son iguales
int mi_strcmp(const char* a, const char* b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

// Copia la cadena src en dst
void mi_strcpy(char* dst, const char* src) {
    while ((*dst++ = *src++) != '\0');
}

// Limpia la pantalla con secuencia ANSI (reemplaza system("cls"))
void limpiar() { cout << "\033[2J\033[H"; }

// Pausa hasta que el usuario presione ENTER
void pausa() { cout << "\n  ENTER para continuar..."; cin.ignore(); cin.get(); }

// ============================================================
//  VARIABLES GLOBALES
// ============================================================

// Lista enlazada - Gestor de Procesos
int  lista_id[MAX], lista_prio[MAX], totalLista = 0;
char lista_nom[MAX][50], lista_est[MAX][20];

// Cola de prioridad - Planificador CPU
int  cola_id[MAX], cola_prio[MAX], totalCola = 0;
char cola_nom[MAX][50], cola_est[MAX][20];

// Pila - Gestor de Memoria
int  pila_id[MAX], topePila = 0;
char pila_nom[MAX][50], pila_est[MAX][20];

// ============================================================
//  CABECERA
// ============================================================
void cabecera(const char* titulo) {
    limpiar();
    cout << "\n  ================================================\n";
    cout << "   SISTEMA DE GESTION DE PROCESOS | NRC 28648\n";
    cout << "  ================================================\n";
    cout << "   " << titulo << "\n";
    cout << "  ================================================\n\n";
}

// ============================================================
//  ESTRUCTURA 1: LISTA ENLAZADA - Gestor de Procesos
// ============================================================

// WHILE: recorre la lista buscando el ID
int existeEnLista(int id) {
    int i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) return 1;
        i++;
    }
    return 0;
}

// IF: valida duplicados y desbordamiento antes de insertar
void insertarEnLista(int id, char nom[], int prio) {
    if (totalLista >= MAX) { cout << "  [ERROR] Lista llena.\n"; return; }
    if (existeEnLista(id)) { cout << "  [ERROR] ID " << id << " ya existe.\n"; return; }
    lista_id[totalLista] = id;
    mi_strcpy(lista_nom[totalLista], nom);
    lista_prio[totalLista] = prio;
    mi_strcpy(lista_est[totalLista], "Listo");
    totalLista++;
    cout << "  [OK] Proceso registrado en el Gestor Central.\n";
}

// WHILE: busca posicion; FOR: reorganiza el arreglo tras eliminar
void eliminarDeLista(int id) {
    int pos = -1, i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) { pos = i; break; }
        i++;
    }
    if (pos < 0) { cout << "  [ERROR] ID no encontrado.\n"; return; }
    for (int j = pos; j < totalLista - 1; j++) {
        lista_id[j] = lista_id[j+1];
        mi_strcpy(lista_nom[j], lista_nom[j+1]);
        lista_prio[j] = lista_prio[j+1];
        mi_strcpy(lista_est[j], lista_est[j+1]);
    }
    totalLista--;
    cout << "  [OK] Proceso " << id << " eliminado.\n";
}

// WHILE: busqueda secuencial por ID
void buscarPorID(int id) {
    int i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) {
            cout << "  [ENCONTRADO] ID: " << lista_id[i]
                 << " | Nombre: " << lista_nom[i]
                 << " | Prioridad: " << lista_prio[i]
                 << " | Estado: " << lista_est[i] << "\n";
            return;
        }
        i++;
    }
    cout << "  [NO ENCONTRADO] ID " << id << " no existe.\n";
}

// WHILE: busqueda secuencial por nombre usando mi_strcmp
void buscarPorNombre(char nom[]) {
    int i = 0;
    while (i < totalLista) {
        if (mi_strcmp(lista_nom[i], nom) == 0) {
            cout << "  [ENCONTRADO] ID: " << lista_id[i]
                 << " | Prioridad: " << lista_prio[i]
                 << " | Estado: " << lista_est[i] << "\n";
            return;
        }
        i++;
    }
    cout << "  [NO ENCONTRADO]\n";
}

// WHILE: localiza el proceso y actualiza su prioridad
void modificarPrioridad(int id, int nueva) {
    int i = 0;
    while (i < totalLista) {
        if (lista_id[i] == id) {
            lista_prio[i] = nueva;
            cout << "  [OK] Prioridad actualizada a " << nueva << "\n";
            return;
        }
        i++;
    }
    cout << "  [ERROR] ID no encontrado.\n";
}

// FOR: recorre e imprime todos los elementos de la lista
void mostrarLista() {
    if (totalLista == 0) { cout << "  Lista vacia.\n"; return; }
    cout << "  ID  | Nombre          | Prio | Estado\n";
    cout << "  ----|-----------------|------|----------\n";
    for (int i = 0; i < totalLista; i++)
        cout << "  " << lista_id[i] << "\t| " << lista_nom[i]
             << "\t| " << lista_prio[i] << "\t| " << lista_est[i] << "\n";
    cout << "  Total: " << totalLista << " proceso(s).\n";
}

// ============================================================
//  ESTRUCTURA 2: COLA DE PRIORIDAD - Planificador CPU
// ============================================================

// WHILE: encuentra posicion correcta; FOR: desplaza elementos
void encolarPlanificador(int id, char nom[], int prio) {
    if (totalCola >= MAX) { cout << "  [ERROR] Cola llena.\n"; return; }
    int pos = 0;
    while (pos < totalCola && cola_prio[pos] >= prio) pos++;
    for (int j = totalCola; j > pos; j--) {
        cola_id[j] = cola_id[j-1];
        mi_strcpy(cola_nom[j], cola_nom[j-1]);
        cola_prio[j] = cola_prio[j-1];
        mi_strcpy(cola_est[j], cola_est[j-1]);
    }
    cola_id[pos] = id;
    mi_strcpy(cola_nom[pos], nom);
    cola_prio[pos] = prio;
    mi_strcpy(cola_est[pos], "Listo");
    totalCola++;
    cout << "  [OK] Proceso encolado en posicion " << pos+1 << "\n";
}

// IF: valida cola no vacia; FOR: reorganiza tras desencolar
// PUSH automatico: al despachar se asigna memoria en la pila
void despacharCPU() {
    if (totalCola == 0) { cout << "  [INFO] No hay procesos en cola.\n"; return; }
    cout << "  [CPU] Despachando -> ID: " << cola_id[0]
         << " | " << cola_nom[0] << " | EN EJECUCION\n";
    if (topePila < MAX) {
        pila_id[topePila] = cola_id[0];
        mi_strcpy(pila_nom[topePila], cola_nom[0]);
        mi_strcpy(pila_est[topePila], "En Ejecucion");
        topePila++;
        cout << "  [RAM] Bloque de memoria asignado.\n";
    }
    for (int i = 0; i < totalCola - 1; i++) {
        cola_id[i] = cola_id[i+1];
        mi_strcpy(cola_nom[i], cola_nom[i+1]);
        cola_prio[i] = cola_prio[i+1];
        mi_strcpy(cola_est[i], cola_est[i+1]);
    }
    totalCola--;
}

// FOR: muestra la cola de mayor a menor prioridad
void mostrarCola() {
    if (totalCola == 0) { cout << "  Cola vacia.\n"; return; }
    cout << "  Pos | ID  | Nombre          | Prioridad\n";
    cout << "  ----|-----|-----------------|----------\n";
    for (int i = 0; i < totalCola; i++)
        cout << "  " << i+1 << "\t| " << cola_id[i]
             << "\t| " << cola_nom[i] << "\t| " << cola_prio[i] << "\n";
    cout << "  En espera: " << totalCola << " proceso(s).\n";
}

// ============================================================
//  ESTRUCTURA 3: PILA LIFO - Gestor de Memoria
// ============================================================

// IF: valida pila no llena antes de asignar (PUSH)
void pushMemoria(int id, char nom[]) {
    if (topePila >= MAX) { cout << "  [ERROR] Memoria llena.\n"; return; }
    pila_id[topePila] = id;
    mi_strcpy(pila_nom[topePila], nom);
    mi_strcpy(pila_est[topePila], "En Ejecucion");
    topePila++;
    cout << "  [RAM] Bloque asignado al Proceso " << id << "\n";
}

// IF: valida pila no vacia antes de liberar (POP)
void popMemoria() {
    if (topePila == 0) { cout << "  [ERROR] Pila vacia.\n"; return; }
    topePila--;
    cout << "  [RAM] Bloque liberado del Proceso " << pila_id[topePila] << "\n";
}

// FOR: recorre desde el tope hacia la base
void mostrarPila() {
    if (topePila == 0) { cout << "  Pila vacia. Memoria libre.\n"; return; }
    cout << "  Niv | ID  | Nombre          | Estado\n";
    cout << "  ----|-----|-----------------|----------\n";
    for (int i = topePila - 1; i >= 0; i--)
        cout << "  " << topePila-i << "\t| " << pila_id[i]
             << "\t| " << pila_nom[i] << "\t| " << pila_est[i] << "\n";
    cout << "  Bloques en uso: " << topePila << "\n";
}

// ============================================================
//  PERSISTENCIA (sin fstream, usando freopen)
// ============================================================

void guardarEstado() {
    if (!freopen("procesos.txt", "w", stdout)) {
        freopen("/dev/tty", "w", stdout);
        cout << "  [ERROR] No se pudo guardar.\n"; return;
    }
    for (int i = 0; i < totalLista; i++) {
        // Convierte enteros a cadena manualmente para escribir en archivo
        char bid[12], bprio[12];
        int n = lista_id[i], k = 11; bid[k] = '\0';
        if (!n) { bid[--k] = '0'; } else { while (n > 0) { bid[--k] = '0' + (n % 10); n /= 10; } }
        n = lista_prio[i]; k = 11; bprio[k] = '\0';
        if (!n) { bprio[--k] = '0'; } else { while (n > 0) { bprio[--k] = '0' + (n % 10); n /= 10; } }
        cout << (bid+k) << "|" << lista_nom[i] << "|" << (bprio+k) << "|" << lista_est[i] << "\n";
    }
    cout.flush();
    freopen("/dev/tty", "w", stdout);
    cout << "  [OK] Guardado en 'procesos.txt' (" << totalLista << " procesos).\n";
}

void cargarEstado() {
    if (!freopen("procesos.txt", "r", stdin)) {
        freopen("/dev/tty", "r", stdin);
        cout << "  [INFO] Sin archivo previo. Sistema limpio.\n"; return;
    }
    char linea[120]; int cargados = 0;
    while (cin.getline(linea, 120)) {
        char ids[12], nom[50], ps[12], est[20];
        int k = 0, pos = 0;
        // Parsea cada campo separado por '|'
        while (linea[pos] != '|' && linea[pos]) ids[k++] = linea[pos++]; ids[k] = '\0'; pos++;
        k = 0; while (linea[pos] != '|' && linea[pos]) nom[k++] = linea[pos++]; nom[k] = '\0'; pos++;
        k = 0; while (linea[pos] != '|' && linea[pos]) ps[k++]  = linea[pos++]; ps[k]  = '\0'; pos++;
        k = 0; while (linea[pos]) est[k++] = linea[pos++]; est[k] = '\0';
        // Convierte cadenas a enteros
        int id = 0, i = 0; while (ids[i] >= '0' && ids[i] <= '9') id = id*10 + (ids[i++]-'0');
        int p  = 0; i = 0; while (ps[i]  >= '0' && ps[i]  <= '9') p  = p*10  + (ps[i++] -'0');
        if (!existeEnLista(id)) { insertarEnLista(id, nom, p); mi_strcpy(lista_est[totalLista-1], est); cargados++; }
    }
    freopen("/dev/tty", "r", stdin);
    cout << "  [OK] " << cargados << " proceso(s) cargados.\n";
}

// ============================================================
//  MENUS
// ============================================================
void menuLista() {
    int op, id, prio; char nom[50];
    do {
        cabecera("1. GESTOR DE PROCESOS  [Lista Enlazada]");
        cout << "  1. Registrar proceso\n  2. Eliminar proceso\n  3. Buscar por ID\n";
        cout << "  4. Buscar por nombre\n  5. Modificar prioridad\n  6. Mostrar todos\n  0. Volver\n\n  >> ";
        cin >> op;
        if      (op == 1) { cout << "  ID: "; cin >> id; cout << "  Nombre: "; cin >> nom; cout << "  Prioridad: "; cin >> prio; insertarEnLista(id, nom, prio); }
        else if (op == 2) { cout << "  ID: "; cin >> id; eliminarDeLista(id); }
        else if (op == 3) { cout << "  ID: "; cin >> id; buscarPorID(id); }
        else if (op == 4) { cout << "  Nombre: "; cin >> nom; buscarPorNombre(nom); }
        else if (op == 5) { cout << "  ID: "; cin >> id; cout << "  Nueva prioridad: "; cin >> prio; modificarPrioridad(id, prio); }
        else if (op == 6) mostrarLista();
        if (op) pausa();
    } while (op);
}

void menuCola() {
    int op, id, prio; char nom[50];
    do {
        cabecera("2. PLANIFICADOR CPU  [Cola de Prioridad]");
        cout << "  1. Encolar proceso\n  2. Despachar a CPU\n  3. Ver cola\n  0. Volver\n\n  >> ";
        cin >> op;
        if      (op == 1) { cout << "  ID: "; cin >> id; cout << "  Nombre: "; cin >> nom; cout << "  Prioridad: "; cin >> prio; encolarPlanificador(id, nom, prio); }
        else if (op == 2) despacharCPU();
        else if (op == 3) mostrarCola();
        if (op) pausa();
    } while (op);
}

void menuPila() {
    int op, id; char nom[50];
    do {
        cabecera("3. GESTOR DE MEMORIA  [Pila LIFO]");
        cout << "  1. Ver estado de memoria\n  2. Asignar memoria - PUSH\n  3. Liberar memoria - POP\n  0. Volver\n\n  >> ";
        cin >> op;
        if      (op == 1) mostrarPila();
        else if (op == 2) { cout << "  ID: "; cin >> id; cout << "  Nombre: "; cin >> nom; pushMemoria(id, nom); }
        else if (op == 3) popMemoria();
        if (op) pausa();
    } while (op);
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
        cout << "  4. Guardar estado\n  5. Ver resumen\n  0. Salir\n\n  >> ";
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
    } while (op);
    cout << "\n  Guardando y saliendo...\n";
    guardarEstado();
    return 0;
}
