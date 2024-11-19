#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Clase Libro para almacenar la información de cada libro
class Libro {
public:
    string titulo;
    string autor;
    string genero;
    bool disponible;

    Libro(string t, string a, string g, bool d) : titulo(t), autor(a), genero(g), disponible(d) {}
};

// Clase Biblioteca para gestionar los libros
class Biblioteca {
private:
    vector<Libro> libros;

public:
    void agregarLibro(const string& titulo, const string& autor, const string& genero, bool disponible) {
        libros.emplace_back(titulo, autor, genero, disponible);
    }

    void mostrarLibros() {
        cout << "\nLista de Libros en la Biblioteca:\n";
        for (const auto& libro : libros) {
            cout << "Título: " << libro.titulo << "\n"
                 << "Autor: " << libro.autor << "\n"
                 << "Género: " << libro.genero << "\n"
                 << "Disponibilidad: " << (libro.disponible ? "Disponible" : "No disponible") << "\n\n";
        }
    }

    void buscarPorGenero(const string& genero) {
        cout << "\nLibros en el género '" << genero << "':\n";
        bool encontrado = false;
        for (const auto& libro : libros) {
            if (libro.genero == genero) {
                cout << "Título: " << libro.titulo << " | Autor: " << libro.autor 
                     << " | Disponibilidad: " << (libro.disponible ? "Disponible" : "No disponible") << "\n";
                encontrado = true;
            }
        }
        if (!encontrado) cout << "No se encontraron libros en este género.\n";
    }

    void buscarPorAutor(const string& autor) {
        cout << "\nLibros del autor '" << autor << "':\n";
        bool encontrado = false;
        for (const auto& libro : libros) {
            if (libro.autor == autor) {
                cout << "Título: " << libro.titulo << " | Género: " << libro.genero 
                     << " | Disponibilidad: " << (libro.disponible ? "Disponible" : "No disponible") << "\n";
                encontrado = true;
            }
        }
        if (!encontrado) cout << "No se encontraron libros de este autor.\n";
    }

    void cambiarDisponibilidad(const string& titulo) {
        for (auto& libro : libros) {
            if (libro.titulo == titulo) {
                libro.disponible = !libro.disponible;
                cout << "La disponibilidad del libro '" << titulo << "' ha sido cambiada a: "
                     << (libro.disponible ? "Disponible" : "No disponible") << "\n";
                return;
            }
        }
        cout << "Libro no encontrado.\n";
    }

    void clasificarGenero(const string& titulo, const string& nuevoGenero) {
        for (auto& libro : libros) {
            if (libro.titulo == titulo) {
                libro.genero = nuevoGenero;
                cout << "El género del libro '" << titulo << "' ha sido actualizado a: " << nuevoGenero << "\n";
                return;
            }
        }
        cout << "Libro no encontrado.\n";
    }
};

void mostrarMenuAdministrador() {
    cout << "\n----- Menú de Administrador -----\n";
    cout << "1. Agregar un nuevo libro\n";
    cout << "2. Mostrar todos los libros\n";
    cout << "3. Cambiar disponibilidad de un libro\n";
    cout << "4. Clasificar género de un libro\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuUsuario() {
    cout << "\n----- Menú de Usuario -----\n";
    cout << "1. Mostrar todos los libros\n";
    cout << "2. Buscar libros por género\n";
    cout << "3. Buscar libros por autor\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    Biblioteca biblioteca;
    int opcion;
    string titulo, autor, genero, nuevoGenero;
    bool disponible;
    const string ADMIN_PASSWORD = "1234";
    bool salirSistema = false;

    // Agregar libros de muestra
    biblioteca.agregarLibro("Cien años de soledad", "Gabriel Garcia Marquez", "Realismo mágico", true);
    biblioteca.agregarLibro("La Odisea", "Homero", "Clásico", false);
    biblioteca.agregarLibro("Don Quijote", "Miguel de Cervantes", "Aventura", true);
    biblioteca.agregarLibro("El llamado de Cthulhu", "H.P. Lovecraft", "Terror cósmico", true);
    biblioteca.agregarLibro("It", "Stephen King", "Terror", false);
    biblioteca.agregarLibro("Dune", "Frank Herbert", "Ciencia ficción", true);
    biblioteca.agregarLibro("El sindicato de policía yiddish", "Michael Chabon", "Historia alternativa", true);

    while (!salirSistema) {
        cout << "\n¿Eres un Administrador o Usuario? (1 = Administrador, 2 = Usuario, 3 = Salir): ";
        int tipoUsuario;
        cin >> tipoUsuario;
        cin.ignore();

        if (tipoUsuario == 1) {
            cout << "Ingrese la contraseña de administrador: ";
            string password;
            getline(cin, password);

            if (password == ADMIN_PASSWORD) {
                do {
                    mostrarMenuAdministrador();
                    cin >> opcion;
                    cin.ignore();

                    switch (opcion) {
                        case 1:
                            cout << "Ingrese el título del libro: ";
                            getline(cin, titulo);
                            cout << "Ingrese el autor del libro: ";
                            getline(cin, autor);
                            cout << "Ingrese el género del libro: ";
                            getline(cin, genero);
                            cout << "¿Está disponible? (1 = Sí, 0 = No): ";
                            cin >> disponible;
                            biblioteca.agregarLibro(titulo, autor, genero, disponible);
                            cout << "Libro agregado exitosamente.\n";
                            break;

                        case 2:
                            biblioteca.mostrarLibros();
                            break;

                        case 3:
                            cout << "Ingrese el título del libro para cambiar disponibilidad: ";
                            getline(cin, titulo);
                            biblioteca.cambiarDisponibilidad(titulo);
                            break;

                        case 4:
                            cout << "Ingrese el título del libro para clasificar género: ";
                            getline(cin, titulo);
                            cout << "Ingrese el nuevo género: ";
                            getline(cin, nuevoGenero);
                            biblioteca.clasificarGenero(titulo, nuevoGenero);
                            break;

                        case 5:
                            cout << "Saliendo del menú de administrador...\n";
                            break;

                        default:
                            cout << "Opción inválida. Intente de nuevo.\n";
                    }
                } while (opcion != 5);
            } else {
                cout << "Contraseña incorrecta. Intente nuevamente.\n";
            }

        } else if (tipoUsuario == 2) {
            do {
                mostrarMenuUsuario();
                cin >> opcion;
                cin.ignore();

                switch (opcion) {
                    case 1:
                        biblioteca.mostrarLibros();
                        break;

                    case 2:
                        cout << "Ingrese el género a buscar: ";
                        getline(cin, genero);
                        biblioteca.buscarPorGenero(genero);
                        break;

                    case 3:
                        cout << "Ingrese el autor a buscar: ";
                        getline(cin, autor);
                        biblioteca.buscarPorAutor(autor);
                        break;

                    case 4:
                        cout << "Saliendo del menú de usuario...\n";
                        break;

                    default:
                        cout << "Opción inválida. Intente de nuevo.\n";
                }
            } while (opcion != 4);

        } else if (tipoUsuario == 3) {
            cout << "Saliendo del sistema...\n";
            salirSistema = true;
        } else {
            cout << "Rol inválido. Intente nuevamente.\n";
        }
    }

    return 0;
}
