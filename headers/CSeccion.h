#include <iostream>
#include <vector>
#include "CAlumno.h"
#include "CEvaluacion.h"

#pragma once
class CSeccion {
private:
    int codigo;
    int cant_alumnos = 0;
    int cant_examenes = 0;
    int aforo = 0;
    int aforo_exms =0;

    double sum_peso = 0;
    std::vector<CAlumno> alumnos;
    std::vector<CEvaluacion> examenes;
public:
    //Constructor
    CSeccion() {};

    //Destructor
    ~CSeccion(){};

    //setters
    void setCodigo(int _codigo) { codigo = _codigo; }
    void setAlumnos(int _alms) { cant_alumnos = _alms; }
    void setExams(int _exms) { cant_examenes = _exms; }

    //getters
    int getCodigo(){ return codigo; }
    int getCant_alumnos(){ return cant_alumnos; }
    int getCant_examenes(){ return cant_examenes; }
    int getAforo(){ return aforo; }
    int getAforo_exms(){return aforo_exms;}
    double getSumPesos(){return sum_peso;}

    std::vector<CEvaluacion>* getExms(){return &examenes;}

    //Setters por alumnos
    void setNotas(std::string nombre, std::vector<double> notas);

    //Getters por alumnos
    CAlumno* buscarAlm(std::string &_codigo);
    bool isInExms(std::string &_nombre);
    bool isInAlms(std::string &_codigo);
    CAlumno* get_Alm(std::string &_codigo);

    //Methods
    void addExms(CEvaluacion exm) {
        if (aforo_exms >= cant_examenes) {
            std::cout << "\nSe alcanzo la cantidad maxima de evaluaciones\n";
            return;
        }
        else {
            if(exm.getPeso()+sum_peso >1){
                std::cout << "\nEl peso de la evaluacion superaria el porcentaje maximo de nota de esta seccion\n";
                return;
            }else{
                examenes.push_back(exm);
                aforo_exms++;
                sum_peso += exm.getPeso();
            }

        }
    }
    void addExmsXAlum(CEvaluacion exm);
    void addAlum( CAlumno alm) {
        if (aforo >= cant_alumnos) std::cout << "\nSe alcanzo la cantidad maxima de alumnos\n";
        else {
            alumnos.push_back(alm);
            aforo++;
        }
    }

    void retirar_Alum(std::string &_codigo);

    // Mostrar informacion
    void notificacion(bool exito, std::string &mensaje);

    void printAlumnos();
    void printExms();
    void printSeccion();
    void printTop10();
};
