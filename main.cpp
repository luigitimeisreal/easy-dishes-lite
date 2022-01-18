#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

const int NUM_COMIDAS=60;

struct TIngrediente {
    char nombre[10];
};

struct TComida {
    int id;
    char nombre[20];
    bool es_comida;
    TIngrediente ingredientes[10];
    int ingredientes_actuales;
};

struct TSemana {
    int dia_semana;
    TComida comida[7];
    TComida cena[7];
};

//Las comidas no tienen ningún ingrediente al iniciar el programa
void ingredientesActualesInicializacion(TComida comidas[]) {
    for(int i=0; i< NUM_COMIDAS; ++i) {
        comidas[i].ingredientes_actuales=0;
    }
}

//Permite añadir ingredientes a una determinada comida
void modificarIngredientes(TComida comidas[], int &num_comida, int &num_ingrediente) {
    char continuar_ingredientes='s';
    num_ingrediente = comidas[num_comida].ingredientes_actuales;
    do {
        num_ingrediente = comidas[num_comida].ingredientes_actuales;
        cout << "Añadir ingrediente número " << num_ingrediente + 1 << endl;
        cin.ignore();
        cout << "Nombre del ingrediente: ";
        cin.getline(comidas[num_comida].ingredientes[num_ingrediente].nombre, 10);
        num_ingrediente++;
        cout << "¿Quieres continuar? (s/n): ";
        cin >> continuar_ingredientes;
        comidas[num_comida].ingredientes_actuales = num_ingrediente;
    } while(continuar_ingredientes=='s');
}

//Registra una nueva comida
void nuevaComida(TComida comidas[], int &num_comida, int &num_ingrediente) {
    char opcion_comida='0';
    cin.ignore();
    cout << "Nombre: ";
    cin.getline(comidas[num_comida].nombre,20);
    cout << "Comida(c) o cena(d)?: ";
    cin >> opcion_comida;
    if(opcion_comida=='c') {
        comidas[num_comida].es_comida=true;
    }
    else {
        comidas[num_comida].es_comida=false;
    }
    modificarIngredientes(comidas, num_comida, num_ingrediente);
    cout << "¡Comida registrada! " << endl;
    num_comida++;
    num_ingrediente=0;
}

//Permite escribir las comidas en el archivo
void escribirComida(TComida comidas[], int &num_comida, int &num_ingrediente) {
    fstream archivoComidas;
    archivoComidas.open("comidas.txt", ios::out);
    if(archivoComidas.is_open()) {
        archivoComidas << "\n";
        archivoComidas << num_comida;
        archivoComidas << "\n";
        for(int i=0; i<num_comida;i++) {
            archivoComidas << "\n";
            archivoComidas << i;
            archivoComidas << "\n";
            archivoComidas << comidas[i].nombre;
            archivoComidas << "\n";
            if(comidas[i].es_comida) {
                archivoComidas << "comida\n";
            }
            else {
                archivoComidas << "cena\n";
            }
            for(int j=0; j<comidas[i].ingredientes_actuales; j++) {
                archivoComidas << comidas[i].ingredientes[j].nombre;
                archivoComidas << "\n";
            }
            archivoComidas << comidas[i].ingredientes_actuales;
            archivoComidas << "\n";
        }
    }

}

//Permite leer todas las comidas del archivo y copiarlas a la memoria del programa
void leerComida(TComida comidas[], int &num_comida) {
    fstream archivoComidas;
    archivoComidas.open("comidas.txt", ios::in);
    if(archivoComidas.is_open()) {
        string line;
        while(getline(archivoComidas, line)) {
            cout << line << endl;
        }
    }


}

//Permite ver todas las comidas
void verComidas(TComida comidas[], int &num_comida) {
    for(int i=0; i<num_comida; ++i) {
        cout << "\n*** " << i+1 << ".- " << comidas[i].nombre << " ***" << endl;
        cout << "Comida/Cena: ";
        if(comidas[i].es_comida) {
            cout << " comida" << endl;
        }
        else {
            cout << " cena" << endl;
        }
        cout << "\n";
    }
}

//Permite modificar los días de la semana
void modificarCalendario(TSemana &semana, TComida comidas[], int &num_comida) {
    int opcion_dia=0, opcion_comida=0;
    cout << "1.- Lunes" << endl;
    cout << "2.- Martes" << endl;
    cout << "3.- Miércoles" << endl;
    cout << "4.- Jueves" << endl;
    cout << "5.- Viernes" << endl;
    cout << "6.- Sábado" << endl;
    cout << "7.- Domingo" << endl;
    cout << "Selecciona el día que quieres modificar: ";
    cin >> opcion_dia;
    opcion_dia--;
    verComidas(comidas, num_comida);
    cout << "Selecciona la comida que quieres añadir: ";
    cin >> opcion_comida;
    opcion_comida--;
    if(comidas[opcion_comida].es_comida) {
        strcpy_s(semana.comida[opcion_dia].nombre, comidas[opcion_comida].nombre);
        semana.comida[opcion_dia].ingredientes_actuales = comidas[opcion_comida].ingredientes_actuales;
        for(int i=0;i<comidas[opcion_comida].ingredientes_actuales; ++i) {
            strcpy_s(semana.comida[opcion_dia].ingredientes[i].nombre, 10, comidas[opcion_comida].ingredientes[i].nombre);
        }
    }
    else {
        strcpy_s(semana.cena[opcion_dia].nombre, comidas[opcion_comida].nombre);
        semana.cena[opcion_dia].ingredientes_actuales = comidas[opcion_comida].ingredientes_actuales;
        for(int i=0;i<comidas[opcion_comida].ingredientes_actuales; ++i) {
            strcpy_s(semana.cena[opcion_dia].ingredientes[i].nombre, 10, comidas[opcion_comida].ingredientes[i].nombre);
        }
    }
}

//Resetea todas las comidas
void resetearSemana(TSemana &semana) {
    char opcion='s';
    cout << "Hacer esto eliminará todas las comidas de la semana (Añadir nueva semana). ¿Continuar? (s/n): ";
    cin >> opcion;
    if(opcion=='s') {
        for(int i=0; i<7; ++i) {
            strcpy_s(semana.comida[i].nombre,20,"Vacio");
            strcpy_s(semana.cena[i].nombre,20,"Vacio");
        }
    }
}

//Permite ver la semana que está por venir
void verSemana(TSemana &semana) {
    cout << "\n** Lunes **" << endl;
    cout << "Comida: " << semana.comida[0].nombre << endl;
    cout << "Cena: " << semana.cena[0].nombre << endl;
    cout << "\n** Martes **" << endl;
    cout << "Comida: " << semana.comida[1].nombre << endl;
    cout << "Cena: " << semana.cena[1].nombre << endl;
    cout << "\n** Miércoles **" << endl;
    cout << "Comida: " << semana.comida[2].nombre << endl;
    cout << "Cena: " << semana.cena[2].nombre << endl;
    cout << "\n** Jueves **" << endl;
    cout << "Comida: " << semana.comida[3].nombre << endl;
    cout << "Cena: " << semana.cena[3].nombre << endl;
    cout << "\n** Viernes **" << endl;
    cout << "Comida: " << semana.comida[4].nombre << endl;
    cout << "Cena: " << semana.cena[4].nombre << endl;
    cout << "\n** Sábado **" << endl;
    cout << "Comida: " << semana.comida[5].nombre << endl;
    cout << "Cena: " << semana.cena[5].nombre << endl;
    cout << "\n** Domingo **" << endl;
    cout << "Comida: " << semana.comida[6].nombre << endl;
    cout << "Cena: " << semana.cena[6].nombre << endl;
}

//Permite ver la lista de la compra
void listaCompra(TSemana &semana, TComida comidas[], int &num_comida) {
    cout << "*** Lista de la compra ***" << endl;
    for(int i=0; i<num_comida; ++i) {
        for(int j=0; j<comidas[i].ingredientes_actuales; j++) {
            if(strcmp(comidas[i].ingredientes[j].nombre, semana.comida[i].ingredientes[j].nombre)==0) {
                cout << comidas[i].ingredientes[j].nombre << endl;
            }
        }
        for(int k=0; k<comidas[i].ingredientes_actuales; k++) {
            if(strcmp(comidas[i].ingredientes[k].nombre, semana.cena[i].ingredientes[k].nombre)==0) {
                cout << comidas[i].ingredientes[k].nombre << endl;
            }
        }
    }
}

//Menu Principal
void mostrarMenu() {
    cout << "--- EasyDishes Lite ---" << endl;
    cout << "1.- Comidas" << endl;
    cout << "2.- Calendario " << endl;
    cout << "3.- Salir" << endl;
    cout << "Opción?: ";
}

//Sub menu comidas
void menuComidas(TComida comidas[], int &num_comida, int &num_ingrediente) {
    bool menu_comidas = true;
    int opcion=0;
    do {
        cout << "1.- Nueva Comida" << endl;
        cout << "2.- Ver comidas" << endl;
        cout << "3.- Volver al menú principal" << endl;
        cout << "Opción?: ";
        cin >> opcion;
        switch(opcion) {
        case 1:
            nuevaComida(comidas, num_comida, num_ingrediente);
            escribirComida(comidas, num_comida, num_ingrediente);
            break;
        case 2:
            leerComida(comidas, num_comida);
            verComidas(comidas, num_comida);
            break;
        case 3:
            menu_comidas=false;
            break;
        }
    } while(menu_comidas);
}

//Sub menu calendario
void menuCalendario(TComida comidas[], int &num_comida, int &num_ingrediente, TSemana semana) {
    bool menu_calendario = true;
    int opcion=0;
    do {
        cout << "1.- Ver semana" << endl;
        cout << "2.- Modificar calendario" << endl;
        cout << "3.- Resetear semana" << endl;
        cout << "4.- Ver lista de la compra" << endl;
        cout << "5.- Volver al menú principal" << endl;
        cout << "Opción?: ";
        cin >> opcion;
        switch(opcion) {
        case 1:
            verSemana(semana);
            break;
        case 2:
            modificarCalendario(semana, comidas, num_comida);
            break;
        case 3:
            resetearSemana(semana);
            cout << semana.comida[0].nombre << endl;
            break;
        case 4:
            listaCompra(semana, comidas, num_comida);
            break;
        case 5:
            menu_calendario=false;
            break;
        }
    } while(menu_calendario);
}

int main()
{
    bool programa=true;
    int opcion_principal=0;
    int num_comida=0, num_ingrediente=0;
    TComida comidas[NUM_COMIDAS];
    TSemana semana;
    ingredientesActualesInicializacion(comidas);
    do {
        mostrarMenu();
        cin >> opcion_principal;
        switch(opcion_principal) {
        case 1:
            menuComidas(comidas, num_comida, num_ingrediente);
            break;
        case 2:
            menuCalendario(comidas, num_comida, num_ingrediente, semana);
            break;
        case 3:
            programa=false;
            break;
        }
    } while (programa);
    return 0;
}
