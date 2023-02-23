#include "CSeccion.h"
#include <iostream>
#include <iomanip>
#include <vector>

#pragma once


class CMenu
{
private:
    int opcion;
    std::vector <CSeccion> secciones;
    CSeccion* findSeccion(int &cod);
    void notificacion(bool exito, std::string &mensaje);


    static void imprimirMenu();
    void setOpcion();
    void addSeccion(); // listo
    void addExam(); // listo
    void addAlumno(); //listo
    void setNotas(); //listo
    void ver_seccion(); //listo
    void ver_alumno();  //listo
    void cambiarNota();//listo
    void top_10(); // listo
    void eliminarAlum();
    void Ranking();
    void noelia();
    void seccionAprobados();
    void Nota_Prom();


    void printSecciones();

public:
    CMenu(): opcion{} {}
    void ejecutar();
};