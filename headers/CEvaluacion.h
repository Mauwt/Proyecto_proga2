

#include <iostream>
#pragma once
//using namespace std;
class CEvaluacion {
private:
    std::string nombre;
    double peso;
    double nota=0;
public:
    //Constructors
    CEvaluacion(){};
    CEvaluacion(std::string &_nombre, float &_peso, float &_nota) : nombre(_nombre), peso(_peso),nota(_nota){}

    //Destructor
    ~CEvaluacion(){};
    //Setters
    void setNombre(std::string &_nombre){nombre = _nombre;}
    void setPeso(double _peso){peso = _peso;}
    void setNota(double _nota){nota = _nota;}

    //Getters
    std::string getNombre(){return nombre;};
    double getPeso() {return peso;}
    double getNota() {return nota;}
};



