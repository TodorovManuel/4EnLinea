#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

bool cuatroEnLinea(vector<vector<int>>matriz, int &jugadorGanador){
    int cantenFila = 0;
    int cantenColumna = 0;
    int cantenDiagonalP = 0;
    int cantenDiagonalM = 0;
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz[i].size(); j++){
            if(matriz[i][j]==1){
                for(int enFila = j; enFila < matriz[i].size() && matriz[i][enFila]==1 ;enFila++){
                    cantenFila++;
                }
                for(int enFila = j - 1; enFila >= 0 && matriz[i][enFila]==1;enFila--){
                    cantenFila++;
                }
                for(int enColumna = i; enColumna < matriz.size() && matriz[enColumna][j]==1  ;enColumna++){
                    cantenColumna++;
                }
                for(int enColumna = i - 1; enColumna >= 0 && matriz[enColumna][j]==1;enColumna--){
                    cantenColumna++;
                }
                for(int enDiagonalP = 0;(i + enDiagonalP) < matriz.size() && (j + enDiagonalP) < matriz.size() && matriz[i + enDiagonalP][j+enDiagonalP]==1;enDiagonalP++){
                    cantenDiagonalP++;
                }
                for(int enDiagonalP = 1; (i - enDiagonalP) >= 0 && (j - enDiagonalP) >= 0 && matriz[i - enDiagonalP][j - enDiagonalP]==1;enDiagonalP++){
                    cantenDiagonalP++;
                }
                for(int enDiagonalM = 0; (i - enDiagonalM) >= 0 && (j + enDiagonalM) < matriz[i].size() && matriz[i - enDiagonalM][j + enDiagonalM]==1 ; enDiagonalM++){
                    cantenDiagonalM++;
                }
                for(int enDiagonalM = 1; (j - enDiagonalM) >= 0 && (i + enDiagonalM) < matriz[i].size() && matriz[i + enDiagonalM][j - enDiagonalM]==1; enDiagonalM++){
                    cantenDiagonalM++;
                }
                if(cantenFila == 4 || cantenColumna == 4 || cantenDiagonalP == 4 || cantenDiagonalP == 4){
                    jugadorGanador = 1;
                    return true;
                }
            }
            if(matriz[i][j]==2){
                for(int enFila = j; enFila < matriz[i].size() && matriz[i][enFila]==1 ;enFila++){
                    cantenFila++;
                }
                for(int enFila = j - 1; enFila >= 0 && matriz[i][enFila]==1;enFila--){
                    cantenFila++;
                }
                for(int enColumna = i; enColumna < matriz.size() && matriz[enColumna][j]==1  ;enColumna++){
                    cantenColumna++;
                }
                for(int enColumna = i - 1; enColumna >= 0 && matriz[enColumna][j]==1;enColumna--){
                    cantenColumna++;
                }
                for(int enDiagonalP = 0;(i + enDiagonalP) < matriz.size() && (j + enDiagonalP) < matriz.size() && matriz[i + enDiagonalP][j+enDiagonalP]==1;enDiagonalP++){
                    cantenDiagonalP++;
                }
                for(int enDiagonalP = 1; (i + enDiagonalP) >= 0 && (j + enDiagonalP) >= 0 && matriz[i - enDiagonalP][j - enDiagonalP]==1;enDiagonalP++){
                    cantenDiagonalP++;
                }
                for(int enDiagonalM = 0; (i - enDiagonalM) >= 0 && (j + enDiagonalM) < matriz[i].size() && matriz[i - enDiagonalM][j + enDiagonalM]==1 ; enDiagonalM++){
                    cantenDiagonalM++;
                }
                for(int enDiagonalM = 1; (j - enDiagonalM) >= 0 && (i + enDiagonalM) < matriz[i].size() && matriz[i + enDiagonalM][j - enDiagonalM]==1; enDiagonalM++){
                    cantenDiagonalM++;
                }
                if(cantenFila == 4 || cantenColumna == 4 || cantenDiagonalP == 4 || cantenDiagonalP == 4){
                    jugadorGanador = 2;
                    return true;
                }
            }
        }
    }
    return false;
}

void mostrarTablero(vector<vector<int>>matriz){
    cout<<"|  ||1||2||3||4||5||6||7||8||9||10||11||12||13||14||15|"<<endl;
    for(int i = 0; i<matriz.size() ; i++){
        if(i+1 < 10){
            cout<<"|"<<i+1<<" |";
        }
        else{
            cout<<"|"<<i+1<<"|";
        }
        for(int j = 0; j<matriz[i].size(); j++){
            if(matriz[i][j]==0){
                cout<<"| |";
            }
            else if(matriz[i][j] == 1){
                cout<<"|X|";
            }
            else if(matriz[i][j] == 2){
                cout<<"|O|";
            }
        }
        cout<<endl;
    }
}

void juego(vector<vector<int>>matriz, string nombreUsuario, string nombreUsuario2){
    int jugadorGanador = 0;
    while(!cuatroEnLinea(matriz, jugadorGanador)){
        mostrarTablero(matriz);
        int columna;
        cout<<"Es el turno de "<<nombreUsuario<<endl;
        cin>>columna;
        for(int i = 14; i>=0 ; i--){
            if(matriz[i][columna-1]==0){
                matriz[i][columna-1]=1;
                i = -1;
            }
        }
        if(!cuatroEnLinea(matriz, jugadorGanador)){
            mostrarTablero(matriz);
            cout<<"Es el turno de "<<nombreUsuario2<<endl;
            cin>>columna;
            for(int i = 14; i>=0 ; i--){
                if(matriz[i][columna-1]==0){
                    matriz[i][columna-1]=2;
                    i = -1;
                }
            }
        }
    }
}

bool chequearPartida(string nombre){
    ifstream archivo;
    string linea;
    bool esta = false;
    archivo.open("partidas.txt");
    while(getline(archivo, linea, ':')) {
        if(linea == nombre){
            esta = true; 
        }
    }
    return esta;
}

bool chequear(string nombre){
    ifstream archivo;
    string linea;
    archivo.open("usuarios.txt");
    while(getline(archivo, linea, ';')) {
        if(linea == nombre){
            return true;
        }
    }
    return false;
}

void crearUsuario(string nombre){
    ofstream archivo;
    archivo.open("usuarios.txt", ios::app);
    archivo <<";" << nombre << ";" << "0" <<endl;
}

void cargarPartida(string nombreUsuario, string nombreUsuario2){
    string nombrePartida;
    bool esta;
    ifstream archivo;
    int n;
    string linea;
    vector<int>v1;
    nombrePartida= nombreUsuario + " vs " + nombreUsuario2 + ":";
    vector<vector<int>>matriz;
    esta = chequearPartida(nombrePartida);
    if(esta){
        archivo.open("partidas.txt");
        while(getline(archivo, linea, ':')){
            if(nombrePartida == linea){
                for(int i = 0; i<15 ; i++){
                    v1= {};
                    for(int i = 0; i<15; i++){
                        archivo>>n;
                        v1.push_back(n);
                    }
                    matriz.push_back(v1);
                }
            }
        }
        juego(matriz, nombreUsuario, nombreUsuario2);
    }
}

void iniciarPartida(vector<vector<int>>matriz ){
    ofstream archivo;
    string nombreUsuario;
    string nombreUsuario2;
    string nombrePartida;
    bool esta = true;
    archivo.open("partidas.txt");
    cout<<"Ingrese nombre de usuario o pase a registrarse por favor si es usted muy amable."<<endl;
    cin>>nombreUsuario;
    esta = chequear(nombreUsuario);
    if(!esta){
        crearUsuario(nombreUsuario);
        cout<<"No se encontro, usuario creado"<<endl;
    }
    cout<<"Ingrese el nombre del segundo jugador"<<endl;
    cin>>nombreUsuario2;
    esta = chequear(nombreUsuario2);
    if(!esta){
        crearUsuario(nombreUsuario2);
        cout<<"No se encontro, usuario creado"<<endl;
    }
    nombrePartida= nombreUsuario + " vs " + nombreUsuario2 + ":";
    bool estaPartida = chequearPartida(nombrePartida);
    if(estaPartida){
        cargarPartida(nombreUsuario, nombreUsuario2);
    }
    else{
        juego(matriz, nombreUsuario, nombreUsuario2);
    }
}

void verPuntuacion(){
    ifstream archivo;
    string nombre;
    string linea;
    cout<<"Ingrese su nombre"<<endl;
    cin>>nombre;
    archivo.open("usuarios.txt");
    while(getline(archivo, linea, ';')) {
        if(nombre==linea) {
            getline(archivo, linea, ';');
            cout<< "Sus puntos: " << linea<<endl;
            cout<<" "<<endl;
        }
    }
}

void verPodio(){
    ifstream archivo;
    string linea;
    string lineaNombre;
    int lineaInt;
    int puntosPrimero = 0;
    int puntosSegundo = 0;
    int puntosTercero = 0;
    string nombrePrimero;
    string nombreSegundo;
    string nombreTercero;
    archivo.open("usuarios.txt");
    while(getline(archivo, linea, ';')) {
        getline(archivo, lineaNombre, ';');
        getline(archivo, linea, ';');
        lineaInt = stoi(linea);
        cout<<lineaInt<<endl;
        if(puntosPrimero<=lineaInt) {
            puntosPrimero=lineaInt;
            nombrePrimero=lineaNombre;
        } else if(puntosSegundo<=lineaInt) {
            puntosSegundo=lineaInt;
            nombreSegundo=lineaNombre;
        } else if(puntosTercero<=lineaInt) {
            puntosTercero=lineaInt;
            nombreTercero=lineaNombre;
        }
    }
    
    cout<<"1- " << nombrePrimero << " " << puntosPrimero << endl;
    cout<<"2- " << nombreSegundo << " "<< puntosSegundo << endl;
    cout<<"3- " << nombreTercero << " "<< puntosTercero << endl;
}


void menu(){
    cout<<"Ingrese una opcion"<<endl;
    cout<<"1. Iniciar nueva partida"<<endl;
    cout<<"2. Cargar partida guardada"<<endl;
    cout<<"3. Ver tu puntuacion"<<endl;
    cout<<"4. Ver podio"<<endl;
    cout<<"5. salir"<<endl;
}



int main(){
    vector<vector<int>>matriz={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    int n;
    bool salir = false;
    while(!salir){
        menu();
        cin>>n;
        switch (n) {
            case 1: 
            iniciarPartida(matriz);
            break;

            case 2:{
            bool esta = false;
            string nombreUsuario;
            string nombreUsuario2;
            while(!esta){
                cout<<"Ingrese su nombre para acceder a sus datos"<<endl;
                cin>>nombreUsuario;
                esta = chequear(nombreUsuario);
            }
            esta = false;
            while(!esta){
                cout<<"Ingrese su nombre para acceder a sus datos"<<endl;
                cin>>nombreUsuario2;
                esta = chequear(nombreUsuario2);
            }
            cargarPartida(nombreUsuario, nombreUsuario2);
            }
            break;

            case 3:
            verPuntuacion();
            break;

            case 4: 
            verPodio();
            break;
            
            case 5:
            salir = true;
            break;

            default:
            cout<<"Elija una opción válida por favor"<<endl;
            break;
        }
    }
}