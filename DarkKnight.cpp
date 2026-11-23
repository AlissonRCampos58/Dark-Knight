#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <cctype>
#include <iomanip>

#include "DarkKnight.h"

using namespace std;

char mapa[FILAS][COLS] = {
    "===========================================================",
    "|................E..................|....|................|",
    "|........==..........==..............====.......==........|",
    "|.......|..|........|..|.......................|..|.......|",
    "|........==K.........==.C.......................==........|",
    "|...E...................................E.................|",
    "|........==..........==.........................==........|",
    "|.......|..|........|..|.......................|..|.......|",
    "|........==..........==.........................==........|",
    "|.......................................E.................|",
    "|........==..........==.........................==........|",
    "|.......|..|........|..|.......................|..|.......|",
    "|........==....J.....==..............====.......==........|",
    "|......E............................|....|................|",
    "==========================================================="
};

void limpiar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausa() {
    cout << "\nPresiona ENTER para continuar...";
    cin.get();
}
void mostrarMural() {
    ifstream archivo("mural.txt");
    string linea;
    while (getline(archivo, linea)) {   // while + archivo
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void mostrarLogo() {
    ifstream archivo("Logo.txt");
    string linea;
    while (getline(archivo, linea)) {   // while + archivo
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void menuPrincipal(Partida &p, Usuario u[], int n, int sesion) {
    bool esAdmin = (u[sesion].rol == 'A');
    int opcion = 0;

    while (opcion != 4) {
        limpiar();
        cout << "========================================\n";
        cout << "        EL SANTUARIO DE LA CENIZA\n";
        cout << "========================================\n";
        cout << "  Sesion: " << u[sesion].nombre
             << (esAdmin ? " (admin)" : " (jugador)") << "\n\n";
        cout << "  1) Nueva partida\n";
        cout << "  2) Continuar\n";
        if (esAdmin) cout << "  3) Panel de administrador\n";
        cout << "  4) Salir\n";
        cout << "> ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                nuevoJuego(p);
                break;
            case 2:
                if (p.nivel == 0) {
                    cout << "No hay partida guardada."<<endl;
                    pausa();
                } else if (p.terminada) {
                    cout << "Esa partida ya termino. Empieza una nueva."<<endl;
                    pausa();
                } else {
                    jugar(p);
                }
                break;
            case 3:
                if (esAdmin) {
                    menuAdmin(p, u, n);
;
                } else {
                    cout << "No tienes permiso para esa opcion."<<endl;
                    pausa();
                }
                break;
            case 4:
                cout << "La oscuridad se queda quieta."<<endl;
                break;
            default:
                cout << "Opcion invalida."<<endl;
                pausa();
                break;
        }
    }
}

void cargarPartida(Partida &p) {
    ifstream archivo("partida.txt");
    if (archivo.is_open()) {
        archivo >> p.nivel >> p.jefeMuerto >> p.terminada;
        archivo.close();
    } else {
        p.nivel = 0;
        p.jefeMuerto = false;
        p.terminada = false;
    }
}

void guardarPartida(Partida p) {
    ofstream archivo("partida.txt");
    archivo << p.nivel << " " << p.jefeMuerto << " " << p.terminada << '\n';
    archivo.close();
}
int jugadorX = 1;
int jugadorY = 1;

bool esPared(char c) {
    return c == '|' || c == '=';
}
//para la funcion dibujar mapa la realize yo pero me ayude de IA
char leerTecla()
 { return toupper(_getch());}
// la funcion explorar me apoye de IA para poder hacerla
enemigo enemigos[MAX_ENEMIGOS];
int totalEnemigos = 0;
string mensaje = "";
void cargarEnemigos() {
    totalEnemigos = 0;
    for (int y = 0; y < FILAS; y++) {
        for (int x = 0; x < COLS - 1; x++) {
            if (mapa[y][x] == 'E' && totalEnemigos < MAX_ENEMIGOS) {
                enemigos[totalEnemigos] = {"Slime", 30, 30, 6, 1, 10, x, y};
                totalEnemigos++;
                mapa[y][x] = '.';
            } else if (mapa[y][x] == 'J' && totalEnemigos < MAX_ENEMIGOS) {
                enemigos[totalEnemigos] = {"Dragon", 80, 80, 12, 3, 100, x, y};
                totalEnemigos++;
                mapa[y][x] = '.';
            }
        }
    }
}
int enemigoEn(int x, int y) {
    for (int i = 0; i < totalEnemigos; i++) {
        if (enemigos[i].vida > 0 && enemigos[i].x == x && enemigos[i].y == y)
            return i;
    }
    return -1;
}
int enemigosVivos() {
    int n = 0;
    for (int i = 0; i < totalEnemigos; i++)
        if (enemigos[i].vida > 0) n++;
    return n;
}
void atacar(personaje &p, int dx, int dy) {
    int i = enemigoEn(jugadorX + dx, jugadorY + dy);
    if (i == -1) {
        mensaje = "Tu espada corta el aire...";
        return;
    }
    int d = p.ataque - enemigos[i].defensa;
    if (d < 1) d = 1;
    enemigos[i].vida -= d;
    mensaje = "Golpeas al " + enemigos[i].nombre + " por " + to_string(d);
    if (enemigos[i].vida <= 0) {
        p.experiencia += enemigos[i].xp;
        mensaje = "Derrotaste al " + enemigos[i].nombre + "!";
    }
}
void moverEnemigos(personaje &p, int tick) {
    for (int i = 0; i < totalEnemigos; i++) {
        if (enemigos[i].vida <= 0) continue;

        int dx = jugadorX - enemigos[i].x;
        int dy = jugadorY - enemigos[i].y;
        int dist = abs(dx) + abs(dy);

        if (dist == 1) {                       
            int d = enemigos[i].ataque - p.defensa;
            if (d < 1) d = 1;
            p.vida -= d;
            mensaje = enemigos[i].nombre + " te golpea por " + to_string(d);
        } else if (dist <= 8 && tick % 2 == 0) {
            int nx = enemigos[i].x, ny = enemigos[i].y;
            if (abs(dx) > abs(dy)) nx += (dx > 0) ? 1 : -1;
            else                   ny += (dy > 0) ? 1 : -1;

            if (!esPared(mapa[ny][nx]) && enemigoEn(nx, ny) == -1 &&
                !(nx == jugadorX && ny == jugadorY)) {
                enemigos[i].x = nx;
                enemigos[i].y = ny;
            }
        }
    }
}
      void dibujarMapa(personaje &p) {
    cout << "\033[H";
    for (int y = 0; y < FILAS; y++) {
        for (int x = 0; x < COLS - 1; x++) {
            char c = mapa[y][x];
            int i = enemigoEn(x, y);
            if (x == jugadorX && y == jugadorY) cout << "\033[96m@\033[0m";
            else if (i != -1) {
                if (enemigos[i].nombre == "Dragon") cout << "\033[91mD\033[0m";
                else                                cout << "\033[92mE\033[0m";
            }
            else if (esPared(c)) cout << "\033[90m" << c << "\033[0m";
            else if (c == 'K')   cout << "\033[93mK\033[0m";
            else if (c == 'C')   cout << "\033[96mC\033[0m";
            else                 cout << c;
        }
        cout << endl;
    }
    cout << "Vida " << p.vida << "/" << p.vidamax
         << "  Pociones " << p.pociones
         << "  Enemigos " << enemigosVivos() << "     " << endl;
    cout << mensaje << "                              " << endl;
    cout << "Mover: WASD | Espada: ESPACIO | Pocion: P | Salir: Q" << endl;
}
  void explorar() {
    personaje jugador = {"Crow", 100, 100, 15, 3, 1, 0, 50, 1};
    int dirX = 1, dirY = 0;   
    int tick = 0;             

    cargarEnemigos();
    limpiar();

    while (jugador.vida > 0 && enemigosVivos() > 0) {
        dibujarMapa(jugador);
        char tecla = leerTecla();
        if (tecla == 'Q') break;
        mensaje = "";

        if (tecla == ' ') {
            atacar(jugador, dirX, dirY);
        } else if (tecla == 'P') {
            if (jugador.pociones > 0 && jugador.vida < jugador.vidamax) {
                jugador.pociones--;
                jugador.vida += 40;
                if (jugador.vida > jugador.vidamax) jugador.vida = jugador.vidamax;
                mensaje = "Bebes una pocion";
            }
        } else if (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D') {
            dirX = 0;
            dirY = 0;
            if (tecla == 'W') dirY = -1;
            if (tecla == 'S') dirY = 1;
            if (tecla == 'A') dirX = -1;
            if (tecla == 'D') dirX = 1;

            // no atraviesa enemigos
            if (enemigoEn(jugadorX + dirX, jugadorY + dirY) == -1) {
                char c = moverpersonaje(tecla, jugadorX, jugadorY);
                if (c == 'C') {
                    jugador.chakra += 25;
                    mapa[jugadorY][jugadorX] = '.';
                } else if (c == 'K') {
                    jugador.pociones++;
                    mensaje = "Encontraste una pocion!";
                    mapa[jugadorY][jugadorX] = '.';
                }
            }
        }

        moverEnemigos(jugador, tick);
        tick++;
    }

    limpiar();
    if (jugador.vida <= 0){ cout << "Has caido..." << endl;
    }else if (enemigosVivos() == 0){ cout << "Derrotaste a todos! GANASTE!" << endl;
    }
    pausa();
  }
    void nuevoJuego(Partida &p) {
    p.nivel = 1;
    p.jefeMuerto = false;
    p.terminada = false;
    guardarPartida(p);
    mostrarMural();
    jugar(p);
};

void cargarUsuarios(Usuario u[], int &n) {
    n = 0;
    ifstream archivo("usuarios.txt");

    if (!archivo.is_open()) {
        u[0] = {"admin", "1234", 'A', true};
        n = 1;
        ofstream nuevo("usuarios.txt");
        nuevo << "admin 1234 A\n";
        nuevo.close();
        return;
    }

    while (n < MAX_USUARIOS && archivo >> u[n].nombre >> u[n].clave >> u[n].rol) {
        u[n].activo = true;
        n++;
    }
    archivo.close();
}

void registrarUsuario(Usuario u[], int &n) {
    if (n >= MAX_USUARIOS) {
        cout << "No hay espacio para mas usuarios.\n";
        pausa();
        return;
    }

    limpiar();
    cout << "===== REGISTRO =====\n";

    string nombre, clave;
    cout << "Nuevo usuario: ";
    cin >> nombre;

    for (int i = 0; i < n; i++) {
        if (u[i].nombre == nombre) {
            cout << "\nEse nombre ya existe.\n";
            pausa();
            return;
        }
    }

    cout << "Clave: ";
    cin >> clave;
    cin.ignore();

    u[n].nombre = nombre;
    u[n].clave = clave;
    u[n].rol = 'J';
    u[n].activo = true;
    n++;

    ofstream archivo("usuarios.txt", ios::app);
    archivo << nombre << " " << clave << " J\n";
    archivo.close();

    cout << "\nUsuario creado. Ya puedes iniciar sesion.\n";
    pausa();
}

int iniciarSesion(Usuario u[], int &n) {
    int intentos = 0;

    while (intentos < 3) {
        limpiar();
        cout << "===== INICIAR SESION =====\n";
        cout << "1) Entrar\n";
        cout << "2) Registrarse\n";
        cout << "3) Salir\n> ";

        int op = 0;
        cin >> op;
        cin.ignore();

        if (op == 2) {
            registrarUsuario(u, n);
            continue;
        }
        if (op == 3) {
            return -1;
        }
        if (op != 1) {
            cout << "Opcion invalida.\n";
            pausa();
            continue;
        }

        string nombre, clave;
        cout << "Usuario: ";
        cin >> nombre;
        cout << "Clave: ";
        cin >> clave;
        cin.ignore();

        for (int i = 0; i < n; i++) {
            if (u[i].activo && u[i].nombre == nombre && u[i].clave == clave) {
                cout << "\nBienvenido, " << u[i].nombre << '\n';
                pausa();
                return i;
            }
        }

        intentos++;
        cout << "\nDatos incorrectos. Intentos restantes: " << (3 - intentos) << '\n';
        pausa();
    }
    return -1;
}

void menuAdmin(Partida &p, Usuario u[], int n) {
    int op = 0;
    while (op != 3) {
        limpiar();
        cout << "===== PANEL DE ADMINISTRADOR ====="<<endl;
        cout << "1) Ver estado de la partida"<<endl;
        cout << "2) Reiniciar partida guardada"<<endl;
        cout << "3) Listado de usuarios registrados"<<endl;
        cout << "4) Volver> "<<endl;
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                cout << "Nivel: "<<endl << p.nivel
                     << "  Jefe muerto: " << (p.jefeMuerto ? "si" : "no")
                     << "  Terminada: " << (p.terminada ? "si" : "no") << '\n';
                pausa();
                break;
            case 2:
                p.nivel = 0;
                p.jefeMuerto = false;
                p.terminada = false;
                guardarPartida(p);
                cout << "Partida reiniciada."<<endl;
                pausa();
                break;
            case 3:
                listarUsuarios(u, n);
                break;
            case 4:
                break;    
            default:
                cout << "Opcion invalida."<<endl;
                pausa();
                break;
        }
    }
}
void listarUsuarios(Usuario u[], int n) {
    limpiar();
    cout << "===== USUARIOS REGISTRADOS =====\n\n";

    if (n == 0) {
        cout << "No hay usuarios cargados.\n";
        pausa();
        return;
    }

    cout << left
         << setw(4)  << "No."
         << setw(18) << "Usuario"
         << setw(8)  << "Rol"
         << "Estado\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << setw(4)  << (i + 1)
             << setw(18) << u[i].nombre
             << setw(8)  << (u[i].rol == 'A' ? "Admin" : "Jugador")
             << (u[i].activo ? "Activo" : "Inactivo") << '\n';
    }

    cout << "----------------------------------------\n";
    cout << "Total: " << n << " de " << MAX_USUARIOS << " espacios\n";
    pausa();
}


