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

public:

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
    void ejecutar();

    CMenu(){

        int cod_secc = 1;
        CEvaluacion ex1("EX1", 0.45, 0);
        CEvaluacion ex2("EX2", 0.55, 0);

        std::vector<CEvaluacion> exs = {ex1, ex2};
        std::vector<CAlumno> als;
        for(int i = 0; i < 20; i++){
            char I = 65+i;
            std::string name(1,I);
            CAlumno al(
                    name,
                    name,
                    1,
                    exs,i
                    );

            als.push_back(al);
        }
        CSeccion secc(
                1,20,2,
                als,exs
                );
        secciones.push_back(secc);
    };

};