#include <iostream>
#include <iomanip>
#include <vector>
#include "CEvaluacion.h"


#pragma once
//using namespace  std;

class CAlumno {
private:
    std::string nombre;
    std::string apellido;
    std::string codigo;
    double promedio=0;
    bool aprobado = false;
    bool nota_modificada = false;
    int seccion;

    std::vector <CEvaluacion> examenes;
public:
    //Constructor
    CAlumno(){};
    CAlumno(std::string &_nombre, std::string &_apellido, int &_seccion );


    // Setters
    void setNombre(std::string _nombre){nombre = _nombre ;}
    void setApellido(std::string _apellido) {apellido = _apellido;}
    void setSeccion(int _seccion, int ord);
    void setNota(std::string &_nombre, double nota);

    //Getters
    std::string getNombre(){return  nombre;}
    std::string getApellido() {return  apellido;}
    std::string getCodigo(){return codigo;}
    double getPromedio() {return promedio;}
    bool getEstado() {return aprobado;}
    int getSeccion() {return seccion;}
    bool getNotaModificada(){return nota_modificada;}

    //Methods
    void addExamen(CEvaluacion exam);
    void editarNota(std::string &_nombre, double nota);

    //Mostrar informacion
    void printNotas();
    void calcularPromedio();
};


