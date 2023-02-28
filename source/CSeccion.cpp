#include "../headers/CSeccion.h"
#include <cmath>
#include <tabulate/table.hpp>
using namespace tabulate;

void CSeccion::notificacion(bool exito, std::string &mensaje){
    tabulate::Table chart;
    chart.format()
            .font_color(Color::white)
            .padding_left(0)
            .padding_right(0)
            .corner("x")
            .column_separator("|");
    tabulate::Table::Row_t row;
    if (!exito) {

        row.push_back(mensaje);

        chart.add_row(row);
        chart[0][0].format().color(Color::red).font_style({FontStyle::italic}).border_color(Color::yellow);
        std::cout << chart << std::endl;
        //std::cout << "\nLa seccion " << codigo << " ya existe\n";

    }
    else {

        row.push_back(mensaje);
        chart.add_row(row);
        chart[0][0].format().color(Color::green).font_style({FontStyle::italic, FontStyle::bold}).border_color(Color::white);
        std::cout << "\n";
        std::cout << chart << std::endl;

        //std::cout << "\nSeccion " << codigo << " anhadida\n";

    }
}


//Setters por alumnos

void CSeccion::setNotas(std::string nombre, std::vector<double> notas) {
    if (notas.size() != alumnos.size()) {
        std::string mensaje =  "\nCantidad de notas ingresadas incorrecta\n";
        notificacion(false, mensaje);
        std::cout << "\nActualmente hay " << alumnos.size() << " alumnos\n";
    }
    else{
        for(int i = 0; i < notas.size(); i++){
            alumnos[i].setNota(nombre, notas[i]);
        }
    }
}
void CSeccion::addExmsXAlum(CEvaluacion exm) {
    if (aforo_exms > cant_examenes) return;

    for(auto &it: alumnos){
        it.addExamen(exm);
    }
}

void CSeccion::retirar_Alum(std::string &_codigo) {
    int idx=0;
    std::string _nombre, _apellido;
    for(int i = 0; i<alumnos.size(); i++){
        if(alumnos[i].getCodigo()==_codigo){
            idx = i;
            break;
        }
    }
    alumnos.erase(alumnos.begin()+idx);
    aforo--;
}

//Getters por alumnos
CAlumno* CSeccion::get_Alm(std::string &_codigo){
    for (auto &it:alumnos){
        if (it.getCodigo() == _codigo){
            return &it;
            break;
        }
    }
    return nullptr;
}
CAlumno* CSeccion::buscarAlm(std::string &_codigo){
    for(auto &it:alumnos){
        if (_codigo == it.getCodigo()) {
            return &it;
            break;
        }
    }
    return nullptr;
}

bool CSeccion::isInExms(std::string &_nombre){
    for(auto &it:examenes){
        if (_nombre == it.getNombre()){
            return true;
        }
    }
    return false;
}
bool CSeccion::isInAlms(std::string &_codigo){
    for(auto &it:alumnos){
        if (_codigo == it.getCodigo()) {
            return true;
        }
    }
    return false;
}

//Funciones para mostrar informacion
void CSeccion::printSeccion() {
    if(alumnos.size()<1){
        std::string mensaje = " Aun no hay alumnos asiganados a esta seccion ";
        notificacion(false, mensaje);
        return;
    }

    std::cout << "\nInformacion de la seccion "<< codigo << ":\n\n";
    for(auto &it :alumnos){
        it.printNotas();
    }
}
void CSeccion::printAlumnos(){
    if(alumnos.size() == 0) {
        std::cout << "\nLa seccion esta vacia\n";
        return;
    }
    tabulate::Table table;
    table.add_row({" Nombre "," Apellido ", " Codigo "});
    std::cout << "\nAlumnos de la seccion "<< codigo << ":\n";
    for (auto &it:alumnos){
        table.add_row({ it.getNombre(),  it.getApellido(), it.getCodigo()});
        //std::cout << it.getNombre() << " " << it.getApellido() <<" codigo: " << it.getCodigo()<<"\n";
    }
    std::cout << table << std::endl;
    std::cout << std::endl;
}
void CSeccion::printExms() {
    if(examenes.size() == 0) {
        std::cout << "\nAun no se añaden evaluaciones\n";
        return;
    }
    std::cout << "\n\nEvaluaciones de la seccion "<< codigo << ":\n";
    for (auto &it:examenes){
        std::cout << it.getNombre() << "\n";
    }
}

void CSeccion::printTop10() {
    for (int i = 0; i < alumnos.size(); i++) {
        for (int j = 0; j < alumnos.size() - i - 1; j++) {
            if (alumnos[j].getPromedio() < alumnos[j + 1].getPromedio()) {
                CAlumno temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }


    std::cout << "\nTop10\n";
    if (aforo < 10) {
        for (int i = 0; i < aforo; i++) alumnos[i].printNotas();
    } else {
        for (int i = 0; i < 10; i++) alumnos[i].printNotas();
    }
}

void CSeccion::printRanking() {
    std::vector <double> promedios;
    for (CAlumno al:alumnos){
        promedios.push_back(al.getPromedio());
    }
    printSeccion();
    std::cout << "\n\n";
    std::cout<<"Ingrese el segundo numero del codigo del alumno:";

    /*
    int posi;
    int conta =0;

    std::cin>>posi;
    for(int i =0;i<promedios.size();i++){
        if(promedios[posi]>promedios[i]){
            conta++;
        }
    }
    if(conta>=cant_alumnos/10.0){
        std::cout<<"Ranking: décimo superior";
    }
    else{
        if(conta>=cant_alumnos/5.0){
            std::cout<<"Ranking: quinto superior";
        }
        else{
            if(conta>=cant_alumnos/3.0){
                std::cout<<"Ranking: tercio superior";
            }
            else{
                if(conta>=cant_alumnos/2.0){
                    std::cout<<"Ranking: medio superior";
                }
            }
        }
    }
    */
    int posi;
    int puesto =0;

    std::cin>>posi;
    for(int i =0;i<alumnos.size();i++){
        if(promedios[posi] < promedios[i]){
            puesto++;
        }
    }

    if(puesto<=alumnos.size()/10.0){
        std::cout<<"Ranking: decimo superior";
    } else if(puesto<=alumnos.size()/5.0){
        std::cout<<"Ranking: quinto superior";

    } else if(puesto<=alumnos.size()/3.0){
        std::cout<<"Ranking: tercio superior";
    } else if(puesto<=alumnos.size()/2.0) {
        std::cout<<"Ranking: medio superior";
    }else{
        std::cout << "El alumno no esta calificado en ningun ranking por pertenecer 50% con más baja nota";
    }
}




void printVector(std::vector<double>(v)){
    for(auto item : v)
        std::cout << item << " ";
    std::cout << std::endl;
}

std::vector<std::vector<char>> generarMat(int f){
    std::vector<std::vector<char>> matrix(f,std::vector<char>(21));
    for(auto & row:matrix)
        for(auto & item:row)
            item=' ';
    return matrix;
}

std::vector<std::vector<char>> hist(std::vector<std::vector<char>>(mat), std::vector<double>(v)){
    for(auto num:v) {
        for (int j = 0; j < mat[0].size(); j++) {
            if (num >= j & num < j + 1) {
                if (mat[v.size() - 1][j] == ' ')
                    mat[v.size() - 1][j] = '*';
                else
                    for (int i = 0; i < mat.size(); i++) {
                        if (mat[i][j] == '*')
                            mat[i - 1][j] = '*';
                    }
            }
        }
    }
    return mat;
}

void printHist(std::vector<std::vector<char>>(mat)){
    int cant=mat[0].size();
    int ini=0;
    bool salir=false;

    for(int i=0;i<mat.size();i++){
        for(int j=0; j<=cant;j++)
            if (mat[i][j] == '*') {
                ini = i;
                salir = true;

            }
        if (salir)
            break;
    }


    std::cout <<"\n";
    std::cout <<"                  -------------------HISTOGRAMA DE NOTAS-------------------      " <<"\n\n";
    for(int i=ini;i<mat.size();i++){
        for(int j=0; j<=cant;j++)
            std::cout<< std::setw(5)<< mat[i][j];
        std::cout << std::endl;}
    std::cout << " ";
    for (auto j = 0; j < 21; j++) {

        std::cout << j << std::setw(5) << std::setfill(' ');
    }
    std::cout << '\n';
}

void datosEstad(std::vector<double>v){
    sort(v.begin(), v.end());
    double sum=0;
    double mediana;

    for(auto &item:v)
        sum=sum+item;
    double promedio = sum/double(v.size());

    if(v.size()/2!=0)
        mediana=v[v.size()/2];
    else
    {
        mediana=  (v[v.size()/2]+v[v.size()/2 +1])/2.0;
    }


    std::cout << "\nEl promedio de notas es " << promedio;
    std::cout << "\nLa mediana de las notas es "<< mediana;


}
std::vector  <double>  CSeccion::crearVector() {
    std::vector<double> promedios;
    for(CAlumno al:alumnos){
        promedios.push_back(al.getPromedio());
    }
    return promedios;
}

void  CSeccion::printStats(std::vector<double> v) {
    int cant;

    /*srand(::time(nullptr));
    //cant  = 50;
    //vector<double>v{8.5, 2, 16.4, 0.5, 10.45, 11, 13, 2.6, 9, 10, 14, 19.4, 5, 15.8, 17.3, 1, 11.9, 13.2, 0, 14, 7.5, 12.1, 14, 4.6, 0, 20, 19, 15, 15, 11, 1, 17, 12, 0, 9, 5, 9, 20, 5 ,8 ,17, 15, 4, 15, 9 ,12 ,7,
                    20, 3 ,15};

    /*for (int i=0; i<cant; i++)
    {
        v.push_back(rand()%21);
    }*/


    std::vector<std::vector<char>> matriz=generarMat(v.size());
    printVector(v);
    std::cout << "\n\n";
    printHist(hist(matriz,v));
    datosEstad(v);
}

void CSeccion::porcentajeAprobados() {
    int aux=0,p;
    for (CAlumno al:alumnos){
        if(al.getAProbado()) aux++;
    }
    p=100*aux/alumnos.size();
    std::cout<<"El porcentaje de aprobados"<<" en la seccion "<<codigo<<" es: "<<p<<"%.\n";
}
void CSeccion::printSec_Prom(){ //ANDRES
    int acum=0, cont=0;
    for(int i = 0; i<alumnos.size(); i++){
        cont++;
        acum = acum + alumnos[i].getPromedio();
    }
    std::cout << "\nPromedio de la seccion\n";
    std::cout << acum*1.0/cont*1.0;
    std::cout << "\nPromedio de la seccion redondeado\n";
    std::cout << round(acum*1.0/cont*1.0);
}
