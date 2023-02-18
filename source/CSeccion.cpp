#include "../headers/CSeccion.h"
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
        std::cout << "\nCantidad de notas ingresadas incorrecta\n";
        std::cout << "Actualmente hay " << alumnos.size() << " alumnos\n";
    }
    else{
        for(int i = 0; i < notas.size(); i++){
            alumnos[i].setNota(nombre, notas[i]);
        }
    }
}
void CSeccion::addExmsXAlum(CEvaluacion exm) {
    if (aforo_exms >= cant_examenes) return;

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

    std::cout << "\nInformacion de la seccion "<< codigo << ":\n";
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
        table.add_row({it.getNombre(), it.getApellido(), it.getCodigo()});
        //std::cout << it.getNombre() << " " << it.getApellido() <<" codigo: " << it.getCodigo()<<"\n";
    }
    std::cout << table << std::endl;
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

void CSeccion::printTop10(){
    for(int i = 0; i<alumnos.size(); i++){
        for(int j = 0; j<alumnos.size()-i-1; j++){
            if(alumnos[j].getPromedio()<alumnos[j+1].getPromedio()){
                CAlumno temp = alumnos[j];
                alumnos[j] = alumnos[j+1];
                alumnos[j+1] = temp;
            }
        }
    }
    std::cout << "\nTop10\n";
    if(aforo <10) {
        for (int i = 0; i < aforo; i++) alumnos[i].printNotas();
    }else{
        for (int i = 0; i < 10; i++) alumnos[i].printNotas();
    }

}