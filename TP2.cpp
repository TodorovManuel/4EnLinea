#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int aleatorio(int limit_inf, int limit_sup, int numero){
    string n;
    ifstream registroLectura;
    string linea;
    registroLectura.open("registro.txt");
    bool randomEsta = true;
    while (randomEsta == true)
    {
        srand(time(NULL));
        numero =limit_inf + rand() % ((limit_sup+1)-limit_inf);
        randomEsta = false;    
        stringstream ss;
        ss << numero;
        ss >> n;
        while (getline(registroLectura, linea, ','))
        {
            if (linea == n)
            {
                randomEsta = true;
            }
        }
        numero = stoi(n);
    }
    return numero;
}

int verificacion(string numeroCuenta){
    ifstream registroLectura;
    string linea;
    string cod_seguridad;
    bool salirr = false;
    bool cod_correcto = false;
    int plata;
    registroLectura.open("registro.txt");
        while(getline(registroLectura, linea, ',') && salirr == false){
        if(linea == numeroCuenta){
            getline(registroLectura, linea, ',');
            while(cod_correcto == false){
                cout<<"Escriba el código de seguridad"<<endl;
                cin>>cod_seguridad;
                if(linea == cod_seguridad){
                    cout<<"Perfecto"<<endl;
                    cod_correcto = true;
                    getline(registroLectura, linea, ',');
                    plata = stoi(linea);
                }
                else{
                    cout<<"Codigo de seguridad incorrecto"<<endl;
                }
            }
            salirr=true;
        }
    }
    registroLectura.close();
    if(salirr == false){
        cout<<"Tu numero de cuenta no existe o es incorrecto"<<endl;
    }
    return plata;
}

int reescribir(string numeroCuenta, int monto, int plataUsuario,bool extraer,string cuentaTransferir){
    ifstream registroLectura;
    ofstream registroEscritura;
    string linea;
    string ruta_archivo = "registro.txt";
    string nuevo_nombre = "registro2.txt";
    rename(ruta_archivo.c_str(), nuevo_nombre.c_str());
    registroEscritura.open(ruta_archivo, ios::app);
    registroLectura.open(nuevo_nombre);
    while (getline(registroLectura, linea, ','))
    {
        if (linea != numeroCuenta && linea != cuentaTransferir)
        {
            registroEscritura << linea << ",";
        }
        else if (linea == numeroCuenta)
        {
            registroEscritura << linea << ",";
            getline(registroLectura, linea, ',');
            registroEscritura << linea << ",";
            getline(registroLectura, linea, ',');
            plataUsuario = stoi(linea);
            if(extraer == false){
                plataUsuario += monto;
            }
            else{
                plataUsuario -= monto;
            }
            registroEscritura << plataUsuario << ',';
        }
        if (linea == cuentaTransferir)
        {
            registroEscritura << linea << ",";
            getline(registroLectura, linea, ',');
            registroEscritura << linea << ",";
            getline(registroLectura, linea, ',');
            plataUsuario = stoi(linea);
            plataUsuario += monto;
            registroEscritura << plataUsuario << ",";
        }

    }
    registroLectura.close();
    remove(nuevo_nombre.c_str());
    return plataUsuario;
}

string crearCuenta()
{
    string nombre;
    string apellido;
    string dni;
    int numeroIdentificacion;
    int codigo_seguridad;
    int i = 0;
    int lineaint;
    ofstream registroEscritura;
    ifstream registroLectura;
    string linea;
    bool esta = false;
    bool randomEsta = true;
    int plata = -1;
    registroLectura.open("registro.txt");
    registroEscritura.open("registro.txt", ios::app);
    cout << "Ingrese su nombre" << endl;
    cin >> nombre;
    cout << "Ingrese su apellido" << endl;
    cin >> apellido;
    while(dni.size() < 7 || dni.size() > 8){
        cout << "Ingrese dni" << endl;
        cin >> dni;
        if(dni.size() < 7 || dni.size() > 8){
            cout<<"Su dni no es valido"<<endl;
        }
    }
    if (registroLectura.is_open())
    {
        while (getline(registroLectura, linea, ','))
        {
            if (linea == dni)
            {
                cout << "Usted ya tiene una cuenta activa" << endl;
                esta = true;
            }
        }
        if (esta == false)
        {
            numeroIdentificacion = aleatorio(10000000, 100000000, numeroIdentificacion);
            codigo_seguridad= aleatorio(100, 1000, codigo_seguridad);
            cout << "Su numero de Identificacion es " << numeroIdentificacion << endl;
            cout << "Tu código de seguridad es " << codigo_seguridad << endl;
            while (plata < 0)
            {
                cout << "Dinero a ingresar por primera vez" << endl;
                cin >> plata;
                if (plata < 0)
                {
                    cout << "Ingrese una opcion valida" << endl;
                }
            }
            registroEscritura << endl<< nombre << "," << apellido << "," << dni << ",";
            registroEscritura << numeroIdentificacion << "," << codigo_seguridad;
            registroEscritura << "," << plata << ",";
        }
    }
    registroLectura.close();

    return nombre;
}

void ingresarDinero()
{
    ifstream registroLectura;
    ofstream registroEscritura;
    ofstream operacion;
    string linea;
    string ruta_archivo = "registro.txt";
    string nuevo_nombre = "registro2.txt";
    string numeroCuenta;
    string cuentaTransferir="*";
    int monto;
    int plataUsuario;
    bool extraer = false;
    cout << "ingrese numero de identificacion" << endl;
    cin >> numeroCuenta;
    plataUsuario=verificacion(numeroCuenta);
    cout << "Monto a ingresar: " << endl;
    cin >> monto;
    while (monto < 0)
    {
        cout << "No se puede operar con un monto negativo" << endl;
        cout << "Ingreselo nuevamente por favor" << endl;
        cin >> monto;
    }
    plataUsuario = reescribir(numeroCuenta, monto, plataUsuario, extraer, cuentaTransferir);
    operacion.open("operacion.txt", ios::app);
    operacion << numeroCuenta << "," << monto << "," << plataUsuario << ","
              << "IE"
              << "," << endl;
}
void extraerDinero()
{
    ifstream registroLectura;
    ofstream registroEscritura;
    ofstream operacion;
    string linea;
    string ruta_archivo = "registro.txt";
    string nuevo_nombre = "registro2.txt";
    string numeroCuenta;
    string cuentaTransferir="*";
    int monto;
    int plata;
    bool extraer = true;
    cout << "ingrese numero de identificacion" << endl;
    cin >> numeroCuenta;
    plata=verificacion(numeroCuenta);
    cout << "Monto a extraer: " << endl;
    cin >> monto;
    while (monto>plata && monto<0)
    {
        if (monto<0)
        {
            cout << "No se puede operar con un monto negativo" << endl;
            cout << "Ingreselo nuevamente por favor" << endl;
            cin >> monto;
        }
        if (monto > plata)
        {
        cout << "No tiene suficiente dinero"<<endl;
        cout << "Ingreselo nuevamente por favor" << endl;
        cin >> monto;
        }
    }
    plata = reescribir(numeroCuenta, monto, plata, extraer, cuentaTransferir);
    operacion.open("operacion.txt", ios::app);
    operacion << numeroCuenta << "," << monto << "," << plata << ","
              << "IE"
              << "," << endl;
}

void realizarTransferencia(string identificacionString)
{
    int plata;
    int dineroEnviar;
    int lineaint;
    string codigoSeguridad;
    string codigoSeguridadVerif;
    string cuentaTransferir;
    string linea;
    bool transferir;
    bool salir = false;
    bool plataVer;
    bool extraer = true;
    ofstream registroEscritura;
    ifstream registroLectura;
    ofstream operacion;
    string ruta_archivo = "registro.txt";
    string nuevo_nombre = "registro2.txt";
    registroLectura.open("registro.txt");
    registroEscritura.open("registro.txt", ios::app);
    plata=verificacion(identificacionString);
    cout << "Perfecto! Elije el dinero que quiere enviar" << endl;
    cin >> dineroEnviar;
    while (dineroEnviar < 0 || dineroEnviar > plata)
    {
        if (dineroEnviar > plata){
            cout<<"No hay suficiente plata para transferir"<<endl;
            cout << "Ingreselo nuevamente por favor" << endl;
            cin >> dineroEnviar;
        }
        else if(dineroEnviar < 0){
            cout << "No se puede operar con un monto negativo" << endl;
            cout << "Ingreselo nuevamente por favor" << endl;
            cin >> dineroEnviar;
        }
    }
    if (dineroEnviar <= plata)
    {
        cout << "Excelente, A quien quiere enviarle el dinero? Ingrese su numero de identificacion" << endl;
        cin >> cuentaTransferir;
        registroLectura.close();
        registroEscritura.close();
        registroLectura.open("registro.txt");
        while (getline(registroLectura, linea, ','))
        {
            if (linea == cuentaTransferir)
            {
                transferir = true; // verifica si existe esa cuenta en el banco
            }
        }
        if (transferir == true)
        {
            cout << "Transferencia Exitosa" << endl;
            plata = plata - dineroEnviar;
            registroEscritura.close();
            registroLectura.close();
            plata = reescribir(identificacionString, dineroEnviar, plata, extraer, cuentaTransferir);
            operacion.open("tranferencias.txt", ios::app);
            operacion<<endl<<identificacionString<<","<<cuentaTransferir<<","<<dineroEnviar<<",T,";
            operacion.close();
        }
        else
        {
            cout << "Esa cuenta no ha sido encontrada" << endl;
        }
    }

    else
    {
        cout << "El codigo de seguridad es erroneo" << endl;
    }
}
void mostrarNombres()
{
    ifstream registroLectura;
    string linea;
    bool salir;

    registroLectura.open("registro.txt");
    while (getline(registroLectura, linea, ',') && salir == false)
    {
        cout << linea << " ";
        getline(registroLectura, linea, ',');
        cout << linea << endl;
        getline(registroLectura, linea, '\n');
    }
}

void mostrarOperaciones(){
    bool hay = false;
    ifstream registroLectura;
    string numeroId;
    string linea;
    cout<<"Ingrese su numero de Identificación"<<endl;
    cin>>numeroId;
    registroLectura.open("operacion.txt");
    while(getline(registroLectura, linea, ',')){
        if(linea == numeroId){
            getline(registroLectura, linea);
            cout<<linea<<endl;
            bool hay = true;
        }
    }
    if(hay == false){
        cout<<"NO hay operaciones con tu numero de id"<<endl;
    }
}

void promedioGente()
{
    ifstream registroLectura;
    string linea;
    int dineroGuardado;
    int dineroLinea;
    int contadorLineas;
    bool salir;

    registroLectura.open("registro.txt");
    while (getline(registroLectura, linea, ',') && salir == false)
    {
        getline(registroLectura, linea, ',');
        getline(registroLectura, linea, ',');
        getline(registroLectura, linea, ',');
        getline(registroLectura, linea, ',');
        getline(registroLectura, linea, ',');
        dineroLinea = stoi(linea);
        dineroGuardado += dineroLinea;
        contadorLineas++;
    }
    cout << "El dinero promedio es de: " << dineroGuardado / contadorLineas << endl;
}
void menu()
{
    int numeroMenu;
    string numeroId;
    int seguirNum = 1;
    while (seguirNum==1)
    {
        cout << "1- Crear cuenta" << endl;
    cout << "2- Realizar ingreso sobre su dinero o extrae su dinero" << endl;
    cout << "3- Realizar transferencias" << endl;
    cout << "4- Mostrar los nombres de las personas que tienen dinero en el banco" << endl;
    cout << "5- Mostrar ingresos u egresos de tu cuenta" << endl;
    cout << "6- Calcular promedio" << endl;
    cin >> numeroMenu;
    switch (numeroMenu)
    {
    case 1:
        crearCuenta();
        break;
    case 2:
        int num;
        cout<<"Presione 1 para ingresar dinero y 2 para extraer"<<endl;
        cin>>num;
        while (num != 1 && num != 2)
        {
            cout<<"Ingrese una opcion valida"<<endl;
            cin>>num;
        }
        if (num==1)
        {
         ingresarDinero();
        }
        else if (num==2)
        {
         extraerDinero();
        }
        break;
    case 3:
        cout << "Ingrese su numero de identificacion" << endl;
        cin >> numeroId;
        realizarTransferencia(numeroId);
        break;
    case 4:
        mostrarNombres();
        break;
    case 5:
        mostrarOperaciones();
        break;
    case 6:
        promedioGente();
        break;
    default:
        while (numeroMenu > 6 || numeroMenu <= 0)
        {
            cout << "Ingrese una opción válida" << endl;
            cin >> numeroMenu;
        }
        break;
    }
        cout<<"Presione 1 para seguir en el banco y 2 para salir"<<endl;
        cin>>seguirNum;
        while (seguirNum != 1 && seguirNum != 2)
        {
            cout<<"Ingrese una opcion valida"<<endl;
            cin>>seguirNum;
        }
    }
}
    
    
int main()
{
    menu();
}
