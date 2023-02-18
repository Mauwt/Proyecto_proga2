#include "../headers/CAlumno.h"
#include <tabulate/table.hpp>
using namespace tabulate;

// Constructor
CAlumno::CAlumno(std::string &_nombre, std::string &_apellido, int &_seccion) {
    nombre = _nombre;
    apellido = _apellido;
    seccion  = _seccion;
}

//Setters
void CAlumno::setSeccion(int _seccion, int ord) {
    seccion = _seccion;
    codigo= std::to_string(seccion) + '_'+ std::to_string(ord);
}

// Setters por examenes
void CAlumno::addExamen(CEvaluacion exam) {
    for(auto &it:examenes){
        if(exam.getNombre() == it.getNombre()){
            std::cout << "\nEl alumno ya tiene asignado este examen\n";
            calcularPromedio();
            return;
        }
    }
    examenes.push_back(exam);
    promedio += exam.getNota() / (double)examenes.size();
}


void CAlumno::setNota(std::string &_nombre, double nota) {
    for(auto &it:examenes){
        if (_nombre == it.getNombre()) {
            it.setNota(nota);
        }
    }
    calcularPromedio();
}
void CAlumno::editarNota(std::string &_nombre, double nota) {
    if (nota_modificada) std::cout << "El limite de notas a modificar es 1.\n";
    else {
        for (auto &it: examenes) {
            if (it.getNombre() == _nombre) it.setNota(nota);
            nota_modificada = true;
        }
    }
    calcularPromedio();
}

// Methods
void CAlumno::calcularPromedio() {
    promedio = 0;
    for (auto &it:examenes){
        promedio += it.getNota()*it.getPeso();
    }
}

//Funciones para mostrar informacion
void CAlumno::printNotas() {
    tabulate::Table table;
    table.add_row({nombre, apellido, "codigo: "+codigo});
    table.add_row({"Promedio :" , std::to_string(promedio)});
    table[0].format().hide_border_top().hide_border_left().hide_border_right();
    table[1].format().hide_border_top().hide_border_left().hide_border_right();

    //std::cout << "\n----------------------------------------\n";
    //std::cout << "Alumno: " << nombre<<" " << apellido <<"   codigo: "<<codigo ;

    table.add_row({" Evaluaciones "});

    table[2][1].format().hide_border_right().hide_border_left().border("");
    //std::cout << "\nPromedio: " << promedio << "\n";
    //std::cout << "\nEvaluacion" << std::setw(10)<<"Nota\n";
    for (auto it:examenes){
        table.add_row({it.getNombre(), std::to_string(it.getNota())  });
        //std::cout << std::setw(10)<<it.getNombre() << std::setw(8) << it.getNota() << "\n";
    }
    std::cout << table << std::endl;
}

