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
    while (getline(archivo, linea)) {
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void mostrarCrow() {
    ifstream archivo("crow.txt");
    string linea;
    while (getline(archivo, linea)) {
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void mostrarLogo() {
    ifstream archivo("Logo.txt");
    string linea;
    while (getline(archivo, linea)) {
        cout<<linea<<endl;
    }
    archivo.close();
    cout<<"Presiona Enter para continuar..."<<endl;
    cin.get();
}
void menuPrincipal(Partida &p, Usuario u[], int n, int sesion) {
    bool esAdmin = (u[sesion].rol == 'A');
    int opcion = 0;

    while (opcion != 7) {
        limpiar();
        cout << "========================================"<<endl;
        cout << "        EL SANTUARIO DE LA CENIZA       "<<endl;
        cout << "========================================"<<endl;
        cout << "|  Sesion: " << u[sesion].nombre<<"    |"
             << (esAdmin ? " (admin)        |" : " (jugador)        |") <<endl<<endl;
             cout << "=======================================|"<<endl;
        cout << "| 1) Nueva partida                     |"<<endl;
        cout << "| 2) Continuar                         |"<<endl;
        if (esAdmin) 
        cout << "|  3) Panel de administrador           |"<<endl;
        cout << "|  4) Reporte de resultados            |"<<endl;
        cout << "|  5) Ayuda                            |"<<endl;
        cout << "|  6) Integrantes                      |"<<endl;
        cout << "|  7) Salir                            |"<<endl;
        cout << "|                                      |"<<endl;
        cout << "========================================"<<endl;
        cout << "|> ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                nuevoJuego(p);
                break;
            case 2:
                if (p.nivel == 0) {
                    cout << "No hay partida guardada.\n";
                    pausa();
                } else if (p.terminada) {
                    cout << "Esa partida ya termino. Empieza una nueva.\n";
                    pausa();
                } else {
                    jugar(p);
                }
                break;
            case 3:
                if (esAdmin) menuAdmin(p, u, n);
                else {
                    cout << "No tienes permiso para esa opcion.\n";
                    pausa();
                }
                break;
            case 4:
                reporteResultados(u, n, p);
                break;
            case 5:
                mostrarAyuda();
                break;
            case 6:
                mostrarIntegrantes();
                break;
            case 7:
                cout << "La oscuridad se queda quieta..."<<endl;
                break;
            default:
                cout << "Opcion invalida."<<endl;
                pausa();
                break;
        }
    }
}

void reporteResultados(Usuario u[], int n, Partida p) {
    limpiar();
    cout << "==================================="<<endl;
    cout << "|===== REPORTE DE RESULTADOS =====|"<<endl;

    int admins = 0, jugadores = 0;
    for (int i = 0; i < n; i++) {
        if (u[i].rol == 'A') admins++;
        else jugadores++;
    }
    cout << "==================================="<<endl; 
    cout << "|------------ Usuarios -----------|"<<endl;
    cout << "|Total registrados : " << n <<"            |"<<endl;
    cout << "|Administradores   : " << admins <<"            |"<<endl;
    cout << "|Jugadores         : " << jugadores <<"            |"<<endl;
    cout << "|Espacios libres   : " << (MAX_USUARIOS - n) <<"            |"<<endl;
    cout << "|Ocupacion         : "
         << (n * 100 / MAX_USUARIOS) << "%"<<"          |"<<endl<<endl;
    
    cout << "==================================="<<endl;     
    cout << "|-------- Partida actual ---------|"<<endl;
    cout << "|Nivel alcanzado   : |" << p.nivel <<endl;
    cout << "|Jefe derrotado    : " << (p.jefeMuerto ? "            si|" : "           no|") <<endl;
    cout << "|Partida terminada : " << (p.terminada ? "             si|" : "           no|") <<endl;

    if (p.nivel == 0)
        cout << "|Estado: sin partida guardada.    |"<<endl;
    else if (p.terminada)
        cout << "|Estado: partida completada.      |"<<endl;
    else
        cout << "|Estado: en progreso.             |"<<endl;
        cout << "=================================="<<endl;
    pausa();
}

void mostrarAyuda() {
    int op = 0;

    while (op != 5) {
        limpiar();
        cout << "============================="<<endl;
        cout << "|========== AYUDA ==========|"<<endl<<endl;
        cout << "============================="<<endl;
        cout << "|1) Como se juega           |"<<endl;
        cout << "|2) Controles               |"<<endl;
        cout << "|3) Objeto                  |"<<endl;
        cout << "|4) Consejos                |"<<endl;
        cout << "|5) Volver                  |"<<endl;
        cout << "============================="<<endl;
        cout << "|> ";
        cin >> op;
        cin.ignore();

        switch (op) {
            case 1:
                limpiar();
                cout << "==================================================="<<endl;
                cout << "|=============== COMO SE JUEGA ===================|"<<endl<<endl;
                cout << "==================================================="<<endl;
                cout << "|Recorres una mazmorra en 2D vista desde arriba,  |"<<endl;
                cout << "|- Cada nivel tiene enemigos y un jefe al final.  |"<<endl;
                cout << "|- Si te quedas sin vida, la partida termina.     |"<<endl;
                cout << "|- Derrota al jefe para ganar.                    |"<<endl;
                cout << "|- El progreso se guarda solo al derrotar al jefe.|"<<endl;
                cout << "|El mapa usa simbolos en ASCII:                   |"<<endl;
                cout << "|  | y = -->  pared    |  . -->  suelo            |"<<endl;
                cout << "|  @  --> tu personaje |  E --> enemigo           |"<<endl;
                cout << "|  D  --> jefe         |  + --> objeto            |"<<endl;
                cout << "==================================================="<<endl;
                pausa();
                break;

            case 2:
                limpiar();
                cout << "==================================="<<endl;
                cout << "|=========== CONTROLES ===========|"<<endl<<endl;
                cout << "==================================="<<endl;
                cout << "|  W  o  arriba    mover arriba   |"<<endl;
                cout << "|  S  o  abajo     mover abajo    |"<<endl;
                cout << "|  A  o  izquierda mover izquierda|"<<endl;
                cout << "|  D  o  derecha   mover derecha  |"<<endl;
                cout << "|---------------------------------|"<<endl;
                cout << "|  P               usar el Pocion |"<<endl;
                cout << "|  ESC             pausa y guardar|"<<endl;
                cout << "|Escribe la letra y pulsa Enter.  |"<<endl;
                cout << "==================================="<<endl;
                pausa();
                break;

            case 3:
                limpiar();
                cout << "========================================="<<endl;
                cout << "|=========== POCIONES Y CHAKRA =========="<<endl;
                cout << "|  P  Pocion     recupera vida          |"<<endl;
                cout << "|  Chakra     aumenta el dano de ataque |"<<endl;
                cout << "========================================="<<endl;
                pausa();
                break;

            case 4:
                limpiar();
                cout << "=============================================================="<<endl;
                cout << "|===================== ENEMIGOS Y JEFE ======================|"<<endl<<endl;
                cout << "=============================================================="<<endl;
                cout << "|ENEMIGOS COMUNES                                            |"<<endl;
                cout << "|  Slime:   cuando te encuentra, te persigue hasta alcanzarte|"<<endl<<endl;
                cout << "|JEFE                                                        |"<<endl;
                cout << "|  Dragon:                                                   |"<<endl;
                cout << "|  Uno por nivel, al final de la mazmorra.                   |"<<endl;
                cout << "|  Tienen mas vida y atacan en patron: golpean,              |"<<endl;
                cout << "|  se alejan y vuelven. Espera a que se alejen               |"<<endl;
                cout << "|  para acercarte y atacar.                                  |"<<endl<<endl;
                cout << "|------------------------------------------------------------|"<<endl;
                cout << "|Regla general: no luches rodeado. Usa los pasillos          |"<<endl;
                cout << "|para enfrentarlos de uno en uno.                            |"<<endl;
                cout << "=============================================================="<<endl;
                pausa();
                break;

            case 5:
                break;

            default:
                cout << "Opcion invalida."<<endl;
                pausa();
                break;
        }
    }
}


void mostrarIntegrantes() {
    limpiar();
    cout << "================================================="<<endl;
    cout << "|================= INTEGRANTES =================|"<<endl<<endl;
    cout << "================================================="<<endl;
    cout << left << setw(28) <<  "|NOMBRE" << "CARNET              |"<<endl;
    cout << "-------------------------------------------------"<<endl;
    cout << setw(28) << "|Alisson Ramirez"       << "00058026            |"<<endl;
    cout << setw(28) << "|Enrique Valladares"    << "00078226            |"<<endl;
    cout << "================================================="<<endl;
    pausa();
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
void jugar(Partida &p) {
    limpiar();
    cout << "================================================="<<endl;
    cout << "|============ NIVEL " << p.nivel << " ===============|" << endl << endl;
    cout << "================================================="<<endl;
    cout << "|La Oscuridad se disipa frente a ti...          |" << endl;
    cout << "|Presiona Enter para entrar.                    |" << endl;
    cout << "================================================"<<endl;
    cin.get();
    
    explorar();

    
    if (enemigosVivos() > 0) {
       
        cout << "No lograste limpiar el nivel..." << endl;
        pausa();
        return;
    }

    
    p.nivel++;
    p.jefeMuerto = true;
    guardarPartida(p);

    cout << "Llegaste al nivel " << p.nivel << "." << endl;
    pausa();
}
bool esPared(char c) {
    return c == '|' || c == '=' || c=='"';
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
                enemigo e;
                e.nombre   = "Slime";
                e.fila     = y;
                e.col      = x;
                e.vida     = 10;
                e.vidamax  = 10;
                e.ataque   = 6;
                e.defensa  = 1;
                e.xp       = 10;
                e.x        = x;
                e.y        = y;
                e.esJefe   = false;
                e.cooldown = 0;
                enemigos[totalEnemigos] = e;
                totalEnemigos++;
                mapa[y][x] = '.';
            } else if (mapa[y][x] == 'J' && totalEnemigos < MAX_ENEMIGOS) {
                enemigo j;
                j.nombre   = "Dragon";
                j.fila     = y;
                j.col      = x;
                j.vida     = 15;
                j.vidamax  = 15;
                j.ataque   = 12;
                j.defensa  = 3;
                j.xp       = 100;
                j.x        = x;
                j.y        = y;
                j.esJefe   = true;
                j.cooldown = 0;
                enemigos[totalEnemigos] = j;
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
    bool yaGolpeado = false;
    for (int i = 0; i < totalEnemigos; i++) {
    if (enemigos[i].vida <= 0) continue;

    int dx = 0, dy = 0;
    if (jugadorX > enemigos[i].x) dx = 1;
    else if (jugadorX < enemigos[i].x) dx = -1;
    if (jugadorY > enemigos[i].y) dy = 1;
    else if (jugadorY < enemigos[i].y) dy = -1;
    if (enemigos[i].cooldown > 0) {
    enemigos[i].cooldown--;
    continue;
    }
    int nx = enemigos[i].x + dx;
    int ny = enemigos[i].y + dy;

    if (nx < 1 || nx >= COLS - 1 || ny < 1 || ny >= FILAS - 1) continue;

    // ¿me alcanza? -> golpe, y no se mueve
    if (nx == jugadorX && ny == jugadorY) {
        if (!yaGolpeado) {
        p.vida -= 1;
        yaGolpeado = true;
        mensaje = "Un enemigo te golpeo!";
        }
        enemigos[i].cooldown = 2;
        continue;
    }

    if (esPared(mapa[ny][nx])) continue;
    if (mapa[ny][nx] == 'C' || mapa[ny][nx] == 'K') continue;
    if (enemigoEn(nx, ny) != -1) continue;

    mapa[enemigos[i].y][enemigos[i].x] = '.';
    enemigos[i].x = nx;
    enemigos[i].y = ny;
    mapa[ny][nx] = 'E';
}
    if (p.vida <= 0) {
    cout << "Has muerto...\n";
    pausa();
    return;   // o reiniciar nivel
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
char moverpersonaje(char tecla, int &x, int &y) {
    int nx = x, ny = y;

    if (tecla == 'W') ny--;
    if (tecla == 'S') ny++;
    if (tecla == 'A') nx--;
    if (tecla == 'D') nx++;

    if (nx < 0 || nx >= COLS - 1 || ny < 0 || ny >= FILAS) return '.';
    if (esPared(mapa[ny][nx])) return '.';

    x = nx;
    y = ny;
    return mapa[ny][nx];
}

  void explorar() {
    personaje jugador = {"Crow", 100, 100, 20, 10, 1, 0, 50, 1};
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
        } else if (tecla == 'p' || tecla == 'P') {
        if (jugador.pociones <= 0) {
            mensaje = "No te quedan pociones.";
        } else if (jugador.vida >= jugador.vidamax) {
            mensaje = "Ya tienes la vida completa.";
        } else {
            jugador.pociones--;
            jugador.vida += 5;
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
                int antX = jugadorX, antY = jugadorY;          // antes de mover
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
    SetConsoleOutputCP(CP_UTF8);
    mostrarMural();
    mostrarCrow();
    mostrarLogo();
    jugar(p);
};

void cargarUsuarios(Usuario u[], int &n) {
    n = 0;
    ifstream archivo("usuarios.txt");

    if (!archivo.is_open()) {
        u[0] = {"admin", "1234", 'A', true};
        n = 1;
        ofstream nuevo("usuarios.txt");
        nuevo << "admin 1234 A"<<endl;
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
        cout << "No hay espacio para mas usuarios."<<endl;
        pausa();
        return;
    }

    limpiar();
    cout << "===== REGISTRO ====="<<endl;

    string nombre, clave;
    cout << "Nuevo usuario: ";
    cin >> nombre;

    for (int i = 0; i < n; i++) {
        if (u[i].nombre == nombre) {
            cout << "Ese nombre ya existe."<<endl;
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
    archivo << nombre << " " << clave << " J"<<endl;
    archivo.close();

    cout << "Usuario creado. Ya puedes iniciar sesion."<<endl;
    pausa();
}

int iniciarSesion(Usuario u[], int &n) {
    int intentos = 0;

    while (intentos < 3) {
        limpiar();
        cout << "============================"<<endl;
        cout << "|===== INICIAR SESION =====|"<<endl;
        cout << "============================"<<endl;
        cout << "|        1) Entrar         |"<<endl;
        cout << "|      2) Registrarse      |"<<endl;
        cout << "|        3) Salir>         |"<<endl;
        cout << "============================"<<endl;

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
                cout << "Bienvenido, " << u[i].nombre <<endl;
                pausa();
                return i;
            }
        }

        intentos++;
        cout << "Datos incorrectos. Intentos restantes: " << (3 - intentos) <<endl;
        pausa();
    }
    return -1;
}

void menuAdmin(Partida &p, Usuario u[], int n) {
    int op = 0;
    while (op != 4) {
        limpiar();
        cout << "===================================="<<endl;
        cout << "|===== PANEL DE ADMINISTRADOR =====|"<<endl;
        cout << "|1) Ver estado de la partida       |"<<endl;
        cout << "|2) Reiniciar partida guardada     |"<<endl;
        cout << "|3) Listado de usuarios registrados|"<<endl;
        cout << "|4) Volver                         |"<<endl;
        cout << "===================================="<<endl;
        cout << "> ";
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
    cout << "=================================="<<endl;
    cout << "|===== USUARIOS REGISTRADOS =====|"<<endl;
    cout << "=================================="<<endl;

    if (n == 0) {
        cout << "No hay usuarios cargados."<<endl;
        pausa();
        return;
    }

    cout << left
         << setw(4)  << "No."
         << setw(18) << "Usuario"
         << setw(8)  << "Rol"
         << "Estado"<<endl;
    cout << "----------------------------------------"<<endl;

    for (int i = 0; i < n; i++) {
        cout << setw(4)  << (i + 1)
             << setw(18) << u[i].nombre
             << setw(8)  << (u[i].rol == 'A' ? "Admin" : "Jugador")
             << (u[i].activo ? "Activo" : "Inactivo") <<endl;
    }

    cout << "----------------------------------------"<<endl;
    cout << "Total: " << n << " de " << MAX_USUARIOS << " espacios"<<endl;
    pausa();
}


