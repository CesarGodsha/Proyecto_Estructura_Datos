#include <iostream>
#include <string>

using namespace std;

//=================== ESTRUCTURAS ===================

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    string estado;
};

struct NodoProceso {
    Proceso dato;
    NodoProceso* sig;
};

struct NodoMemoria {
    int idProceso;
    NodoMemoria* sig;
};

//=================== LISTA GENERAL ===================

class ListaGeneral {
private:
    NodoProceso* cabeza;

public:

    ListaGeneral() {
        cabeza = NULL;
    }

    bool existeID(int id) {

        NodoProceso* aux = cabeza;

        while(aux != NULL) {

            if(aux->dato.id == id)
                return true;

            aux = aux->sig;
        }

        return false;
    }

    void insertar(Proceso p) {

        if(existeID(p.id)) {
            cout << "\nID duplicado.\n";
            return;
        }

        NodoProceso* nuevo = new NodoProceso;

        nuevo->dato = p;
        nuevo->sig = cabeza;

        cabeza = nuevo;

        cout << "\nProceso registrado.\n";
    }

    NodoProceso* buscar(int id) {

        NodoProceso* aux = cabeza;

        while(aux != NULL) {

            if(aux->dato.id == id)
                return aux;

            aux = aux->sig;
        }

        return NULL;
    }

    void modificar(int id) {

        NodoProceso* p = buscar(id);

        if(p == NULL) {
            cout << "\nProceso no encontrado.\n";
            return;
        }

        cout << "Nueva prioridad: ";
        cin >> p->dato.prioridad;

        cout << "\nActualizado.\n";
    }

    void eliminar(int id) {

        NodoProceso* actual = cabeza;
        NodoProceso* anterior = NULL;

        while(actual != NULL &&
              actual->dato.id != id) {

            anterior = actual;
            actual = actual->sig;
        }

        if(actual == NULL) {
            cout << "\nNo encontrado.\n";
            return;
        }

        if(anterior == NULL)
            cabeza = actual->sig;
        else
            anterior->sig = actual->sig;

        delete actual;

        cout << "\nEliminado.\n";
    }

    void mostrar() {

        NodoProceso* aux = cabeza;

        cout << "\n=== PROCESOS ===\n";

        while(aux != NULL) {

            cout << "ID: "
                 << aux->dato.id
                 << " | Nombre: "
                 << aux->dato.nombre
                 << " | Prioridad: "
                 << aux->dato.prioridad
                 << " | Estado: "
                 << aux->dato.estado
                 << endl;

            aux = aux->sig;
        }
    }
};

//=================== COLA PRIORIDAD ===================

class ColaPrioridad {

private:
    NodoProceso* frente;

public:

    ColaPrioridad() {
        frente = NULL;
    }

    bool vacia() {
        return frente == NULL;
    }

    void insertar(Proceso p) {

        NodoProceso* nuevo = new NodoProceso;

        nuevo->dato = p;
        nuevo->sig = NULL;

        if(frente == NULL ||
           p.prioridad < frente->dato.prioridad) {

            nuevo->sig = frente;
            frente = nuevo;
            return;
        }

        NodoProceso* aux = frente;

        while(aux->sig != NULL &&
              aux->sig->dato.prioridad <= p.prioridad) {

            aux = aux->sig;
        }

        nuevo->sig = aux->sig;
        aux->sig = nuevo;
    }

    Proceso extraer() {

        Proceso vacio;

        vacio.id = -1;

        if(vacia())
            return vacio;

        NodoProceso* aux = frente;

        Proceso p = aux->dato;

        frente = frente->sig;

        delete aux;

        return p;
    }

    void mostrar() {

        NodoProceso* aux = frente;

        cout << "\n=== COLA CPU ===\n";

        while(aux != NULL) {

            cout << aux->dato.nombre
                 << " (P:"
                 << aux->dato.prioridad
                 << ")" << endl;

            aux = aux->sig;
        }
    }
};

//=================== PILA MEMORIA ===================

class PilaMemoria {

private:
    NodoMemoria* tope;

public:

    PilaMemoria() {
        tope = NULL;
    }

    bool vacia() {
        return tope == NULL;
    }

    void push(int id) {

        NodoMemoria* nuevo = new NodoMemoria;

        nuevo->idProceso = id;
        nuevo->sig = tope;

        tope = nuevo;
    }

    void pop() {

        if(vacia()) {

            cout << "\nMemoria vacia.\n";
            return;
        }

        NodoMemoria* aux = tope;

        tope = tope->sig;

        delete aux;
    }

    void mostrar() {

        NodoMemoria* aux = tope;

        cout << "\n=== MEMORIA ===\n";

        while(aux != NULL) {

            cout << "Proceso "
                 << aux->idProceso
                 << endl;

            aux = aux->sig;
        }
    }
};

//=================== MAIN ===================

int main() {

    ListaGeneral lista;
    ColaPrioridad cpu;
    PilaMemoria memoria;

    int opcion;

    do {

        cout << "\n=========================\n";
        cout << " GESTOR DE PROCESOS\n";
        cout << "=========================\n";
        cout << "1. Registrar proceso\n";
        cout << "2. Buscar proceso\n";
        cout << "3. Modificar prioridad\n";
        cout << "4. Eliminar proceso\n";
        cout << "5. Mostrar procesos\n";
        cout << "6. Planificar CPU\n";
        cout << "7. Mostrar cola CPU\n";
        cout << "8. Mostrar memoria\n";
        cout << "9. Salir\n";
        cout << "\nOpcion: ";

        cin >> opcion;

        switch(opcion) {

        case 1: {

            Proceso p;

            cout << "ID: ";
            cin >> p.id;

            cout << "Nombre: ";
            cin >> p.nombre;

            cout << "Prioridad (1 alta, 2 media, 3 baja): ";
            cin >> p.prioridad;

            p.estado = "Listo";

            lista.insertar(p);
            cpu.insertar(p);

            break;
        }

        case 2: {

            int id;

            cout << "ID a buscar: ";
            cin >> id;

            NodoProceso* encontrado =
                lista.buscar(id);

            if(encontrado) {

                cout << "\nEncontrado:\n";

                cout << encontrado->dato.nombre
                     << endl;
            }
            else {

                cout << "\nNo existe.\n";
            }

            break;
        }

        case 3: {

            int id;

            cout << "ID: ";
            cin >> id;

            lista.modificar(id);

            break;
        }

        case 4: {

            int id;

            cout << "ID: ";
            cin >> id;

            lista.eliminar(id);

            break;
        }

        case 5:

            lista.mostrar();
            break;

        case 6: {

            if(cpu.vacia()) {

                cout << "\nNo hay procesos.\n";
                break;
            }

            Proceso ejecutando =
                cpu.extraer();

            cout << "\nEjecutando: "
                 << ejecutando.nombre
                 << endl;

            memoria.push(ejecutando.id);

            char interrupcion;

            cout << "Interrupcion? (s/n): ";
            cin >> interrupcion;

            if(interrupcion == 's' ||
               interrupcion == 'S') {

                cout << "\nContexto guardado.\n";
            }
            else {

                cout << "\nProceso finalizado.\n";
                memoria.pop();
            }

            break;
        }

        case 7:

            cpu.mostrar();
            break;

        case 8:

            memoria.mostrar();
            break;

        }

    } while(opcion != 9);

    cout << "\nFin del programa.\n";

    system("pause");

    return 0;
}
