// Multi_Listas (parcial).cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
using namespace std;

class Estudiante {
public:
    string nombre;
    string sexo;
    string ciudad;
    Estudiante* siguiente;

    Estudiante(string nombre, string sexo, string ciudad) {
        this->nombre = nombre;
        this->sexo = sexo;
        siguiente = nullptr;
    }
};

class Asignatura {
public:
    string nombre;
    string docente; // Nuevo atributo para almacenar el nombre del docente
    Estudiante* estudiantes;

    Asignatura(string nombre, string docente) {
        this->nombre = nombre;
        this->docente = docente;
        estudiantes = nullptr;
    }
};

class Docente {
public:
    string nombre;
    vector<Asignatura*> asignaturas;

    Docente(string nombre) {
        this->nombre = nombre;
    }
};

class MultilistaAsignaturas {
private:
    vector<Docente*> docentes;

public:
    MultilistaAsignaturas() {}

    void agregar_asignatura(string nombre, string docente) {
        Asignatura* nueva_asignatura = new Asignatura(nombre, docente);

        Docente* docente_actual = nullptr;
        for (Docente* d : docentes) {
            if (d->nombre == docente) {
                docente_actual = d;
                break;
            }
        }

        if (docente_actual == nullptr) {
            docente_actual = new Docente(docente);
            docentes.push_back(docente_actual);
        }

        docente_actual->asignaturas.push_back(nueva_asignatura);
    }

    void agregar_estudiante(string asignatura_nombre, string nombre, string sexo, string ciudad) {
        Estudiante* nuevo_estudiante = new Estudiante(nombre, sexo, ciudad);

        for (Docente* d : docentes) {
            for (Asignatura* a : d->asignaturas) {
                if (a->nombre == asignatura_nombre) {
                    if (a->estudiantes == nullptr) {
                        a->estudiantes = nuevo_estudiante;
                    }
                    else if (ciudad < a->estudiantes->ciudad) { // Insertar al principio de la lista
                        nuevo_estudiante->siguiente = a->estudiantes;
                        a->estudiantes = nuevo_estudiante;
                    }
                    else {
                        Estudiante* estudiante_actual = a->estudiantes;
                        while (estudiante_actual->siguiente != nullptr && ciudad > estudiante_actual->siguiente->ciudad) {
                            estudiante_actual = estudiante_actual->siguiente;
                        }
                        nuevo_estudiante->siguiente = estudiante_actual->siguiente;
                        estudiante_actual->siguiente = nuevo_estudiante;
                    }
                    return;
                }
            }
        }

        cout << "No se encontró la asignatura especificada." << endl;
    }


    int cantidad_estudiantes_en_asignatura(string asignatura_nombre) {
        for (Docente* d : docentes) {
            for (Asignatura* a : d->asignaturas) {
                if (a->nombre == asignatura_nombre) {
                    int contador = 0;
                    Estudiante* estudiante_actual = a->estudiantes;
                    while (estudiante_actual != nullptr) {
                        contador++;
                        estudiante_actual = estudiante_actual->siguiente;
                    }
                    return contador;
                }
            }
        }
        return 0;
    }

    int cantidad_asignaturas() {
        int contador = 0;
        for (Docente* d : docentes) {
            contador += d->asignaturas.size();
        }
        return contador;
    }

    void mostrar_estudiantes_masculinos() {
        for (Docente* d : docentes) {
            for (Asignatura* a : d->asignaturas) {
                Estudiante* estudiante_actual = a->estudiantes;
                while (estudiante_actual != nullptr) {
                    if (estudiante_actual->sexo == "Masculino") {
                        cout << "Nombre: " << estudiante_actual->nombre << ", Sexo: " << estudiante_actual->sexo << endl;
                    }
                    estudiante_actual = estudiante_actual->siguiente;
                }
            }
        }
    }
    void mostrar_estudiantes_femeninos() {
        for (Docente* d : docentes) {
            for (Asignatura* a : d->asignaturas) {
                Estudiante* estudiante_actual = a->estudiantes;
                while (estudiante_actual != nullptr) {
                    if (estudiante_actual->sexo == "Femenino") {
                        cout << "Nombre: " << estudiante_actual->nombre << ", Sexo: " << estudiante_actual->sexo << endl;
                    }
                    estudiante_actual = estudiante_actual->siguiente;
                }
            }
        }
    }

    void mostrar_asignaturas_y_estudiantes_docente(string nombre_docente) {
        bool docente_encontrado = false;

        for (Docente* d : docentes) {
            if (d->nombre == nombre_docente) {
                docente_encontrado = true;

                cout << "Docente: " << d->nombre << endl;
                cout << "Asignaturas:" << endl;

                for (Asignatura* a : d->asignaturas) {
                    cout << "Nombre: " << a->nombre << endl;
                    cout << "Estudiantes:" << endl;

                    Estudiante* estudiante_actual = a->estudiantes;
                    while (estudiante_actual != nullptr) {
                        cout << "- Nombre: " << estudiante_actual->nombre << ", Sexo: " << estudiante_actual->sexo << endl;
                        estudiante_actual = estudiante_actual->siguiente;
                    }

                    cout << endl;
                }

                break;
            }
        }

        if (!docente_encontrado) {
            cout << "No se encontró al docente especificado." << endl;
        }
    }

    void mostrar_estudiantes_por_ciudad(string ciudad) {
        bool estudiantes_encontrados = false;

        for (Docente* d : docentes) {
            for (Asignatura* a : d->asignaturas) {
                Estudiante* estudiante_actual = a->estudiantes;

                while (estudiante_actual != nullptr) {
                    if (estudiante_actual->ciudad == ciudad) {
                        if (!estudiantes_encontrados) {
                            cout << "Estudiantes de la ciudad " << ciudad << ":" << endl;
                            estudiantes_encontrados = true;
                        }
                        cout << "- Nombre: " << estudiante_actual->nombre << ", Sexo: " << estudiante_actual->sexo << endl;
                    }

                    estudiante_actual = estudiante_actual->siguiente;
                }
            }
        }

        if (!estudiantes_encontrados) {
            cout << "No se encontraron estudiantes de la ciudad " << ciudad << "." << endl;
        }
    }



};

int main() {
    MultilistaAsignaturas multilista;
    int opcion = 0;
    string nombre_asignatura, nombre_estudiante, sexo_estudiante, nombre_docente, nombre_ciudad;

    while (opcion != 6) {
        cout << "----- Menu de Opciones -----" << endl;
        cout << "1. Agregar asignatura" << endl;
        cout << "2. Agregar estudiante" << endl;
        cout << "3. Cantidad de estudiantes en una asignatura" << endl;
        cout << "4. Cantidad de asignaturas" << endl;
        cout << "5. Mostrar estudiantes por sexo" << endl;
        cout << "6. Mostrar la lista de estudiantes y asignaturas de un docente \n";
        cout << "7. Mostrar lista de estudiantes por ciudad \n";
        cout << "8. Salir" << endl;
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese el nombre de la asignatura: ";
            cin >> nombre_asignatura;
            cout << "Ingrese el nombre del docente asignado: ";
            cin >> nombre_docente;
            multilista.agregar_asignatura(nombre_asignatura, nombre_docente);
            cout << "Asignatura agregada exitosamente." << endl;
            break;
        case 2:
            cout << "Ingrese el nombre de la asignatura: ";
            cin >> nombre_asignatura;
            cout << "Ingrese el nombre del estudiante: ";
            cin >> nombre_estudiante;
            cout << "Ingrese el sexo del estudiante (Masculino/Femenino): ";
            cin >> sexo_estudiante;
            cout << "Ingrese la ciudad de origen del estudiante: ";
            cin >> nombre_ciudad;
            multilista.agregar_estudiante(nombre_asignatura, nombre_estudiante, sexo_estudiante, nombre_ciudad);
            cout << "Estudiante agregado exitosamente." << endl;
            break;
        case 3:
            cout << "Ingrese el nombre de la asignatura: ";
            cin >> nombre_asignatura;
            cout << "Cantidad de estudiantes en " << nombre_asignatura << ": " << multilista.cantidad_estudiantes_en_asignatura(nombre_asignatura) << endl;
            break;
        case 4:
            cout << "Cantidad de asignaturas: " << multilista.cantidad_asignaturas() << endl;
            break;
        case 5:
            cout << "----- Mostrar Estudiantes -----" << endl;
            cout << "1. Mostrar estudiantes masculinos" << endl;
            cout << "2. Mostrar estudiantes femeninos" << endl;
            cout << "Ingrese la opción deseada: ";
            int opcion_mostrar;
            cin >> opcion_mostrar;
            cout << "----- Resultado -----" << endl;
            if (opcion_mostrar == 1) {
                cout << "Estudiantes masculinos:" << endl;
                multilista.mostrar_estudiantes_masculinos();
            }
            system("pause");
            break;
        case 6:
            cout << "Ingrese el nombre del docente: ";
            cin >> nombre_docente;
            multilista.mostrar_asignaturas_y_estudiantes_docente(nombre_docente);
            break;
        case 7:
            cout << "Ingrese el nombre de la ciudad: ";
            cin >> nombre_ciudad;
            multilista.mostrar_estudiantes_por_ciudad(nombre_ciudad);
            break;

        case 8:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}

