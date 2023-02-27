#include "../headers/CMenu.h"
#include <tabulate/table.hpp>
using namespace tabulate;

//Interaccion con la consola
void limpiar() {
    system("cls");
}

template <typename T>
T input(std::string label){
    T value;
    std::cout << label;
    std::cin >> value;
    std::cin.clear();
    return value;
}
void esperar() {
    char w;
    do {
        w = input<char>("\nPresione X y Enter para volver al menu\n");
    }while (toupper(w) != 'X');
}


// Funciones para mostrar informacion
void CMenu::printSecciones(){
    tabulate::Table table;
    table.add_row({"       " , " Codigo "});
    table[0][0].format().font_align(FontAlign::center).font_color(Color::yellow).font_background_color(Color::grey);

    for(int i  = 0; i < secciones.size(); i++){
        int cod = secciones[i].getCodigo();
        table.add_row({ "Seccion", std::to_string(cod)});
    }

    std::cout << table << std::endl;
}
CSeccion* CMenu::findSeccion(int &cod){
    for (auto &it:secciones){
        if(cod == it.getCodigo()) {
            return &it;
            break;
        }
    }
    return nullptr;
}
void CMenu::notificacion(bool exito, std::string &mensaje){
    tabulate::Table chart;
    chart.format()
        .font_color(Color::white)
        .padding_left(0)
        .padding_right(0)
        .corner("x")
        .column_separator("|");


    tabulate::Table::Row_t row;
    if (!exito) {
        limpiar();

        row.push_back(mensaje);

        chart.add_row(row);
        chart[0][0].format().color(Color::red).font_style({FontStyle::italic}).border_color(Color::yellow);
        std::cout << chart << std::endl;
        //std::cout << "\nLa seccion " << codigo << " ya existe\n";

    }
    else {

        limpiar();
        row.push_back(mensaje);
        chart.add_row(row);
        chart[0][0].format().color(Color::green).font_style({FontStyle::italic, FontStyle::bold}).border_color(Color::white);
        std::cout << "\n";
        std::cout << chart << std::endl;

        //std::cout << "\nSeccion " << codigo << " anhadida\n";

    }
}


// Methods
void CMenu::addSeccion(){
    CSeccion new_seccion;

    int codigo;
    int cant_alumnos, cant_exams;
    std::cout << "\nIngresar el codigo de la nueva seccion (numero entero): ";
    std::cin >> codigo;
    std::cout << "\nIngresar la cantidad de alumnos de la seccion: ";
    std::cin >> cant_alumnos;
    std::cout << "\nIngresar la cantidad de examenes de la seccion: ";
    std::cin >> cant_exams;

    new_seccion.setCodigo(codigo);
    new_seccion.setAlumnos(cant_alumnos);
    new_seccion.setExams(cant_exams);

    tabulate::Table chart;
    chart.format()
            .font_color(Color::white)
            .padding_left(0)
            .padding_right(0)
            .corner("x")
            .column_separator("|");
    tabulate::Table::Row_t row;

    bool existe_seccion = false;
    for(auto it:secciones){
        if(codigo == it.getCodigo()){
            existe_seccion =true;
            break;
        }
    }
    if (existe_seccion) {
        limpiar();

        row.push_back("La seccion " + std::to_string(codigo) + " ya existe");

        chart.add_row(row);
        chart[0][0].format().color(Color::red).font_style({FontStyle::italic}).border_color(Color::yellow);
        std::cout << chart << std::endl;
        //std::cout << "\nLa seccion " << codigo << " ya existe\n";
        esperar();
    }
    else {
        secciones.push_back(new_seccion);
        limpiar();
        row.push_back("Seccion " + std::to_string(codigo) + " anhadida ");
        chart.add_row(row);
        chart[0][0].format().color(Color::green).font_style({FontStyle::italic, FontStyle::bold}).border_color(Color::white);
        std::cout << "\n";
        std::cout << chart << std::endl;

        //std::cout << "\nSeccion " << codigo << " anhadida\n";
        esperar();
    }
}

void CMenu::addExam(){
    int cod;
    CEvaluacion new_exm;
    std::cout << "\nIngresar el codigo de la seccion a la que desea agregar un examen: \n";
    printSecciones();

    std::cout << "\nSalir : 0";
    std::cout <<"\nCodigo: ";
    std::cin >> cod;

    if(cod == 0) return;

    CSeccion* seccion = findSeccion(cod);

    if (!seccion || seccion->getAforo_exms() >= seccion->getCant_examenes()){
        std::string mensaje ="La seccion no existe o no se puede añadir mas examenes";
        notificacion(false,mensaje);
        esperar();
        return;
    }
    else{
        std::cout << "\n";
        std::string nombre;
        double peso;

        std::cout << "\nNombre del nuevo examen: ";
        std::cin >> nombre;
        std::cout << "\nPeso del examen(valor porcentual en decimal): ";
        std::cin >> peso;

        if(peso<=0){
            std::string mensaje = "Se ingreso un peso invalido";
            notificacion(false, mensaje);
            esperar();
            return;
        }

        if(peso + seccion->getSumPesos() > 1.0){
            std::string mensaje = "El peso de la evaluacion superaria el porcentaje maximo de nota de esta seccion ";
            notificacion(false, mensaje);
            esperar();
            return;
        }

        new_exm.setPeso(peso);
        new_exm.setNombre(nombre);

        seccion->addExms(new_exm);
        seccion->addExmsXAlum(new_exm);

        limpiar();
        std::string mensaje = "Se agrego la evaluacion " + nombre + " a la seccion" + std::to_string(cod);
        notificacion(true, mensaje);
        //std::cout << "Se agrego la evaluacion "<< nombre << "a la seccion " << secciones[opc-1].getCodigo() << "\n";
        esperar();
    }
}

void CMenu::addAlumno(){
    int cod;
    std::cout << "\nIngresar el codigo de la seccion del alumno nuevo: \n";
    printSecciones();
    std::cout << "\n\n0:Salir\n";
    std::cout << "Seccion: ";
    std::cin >> cod;

    if (cod == 0) return;

    CSeccion* seccion = findSeccion(cod) ;


    if(!seccion || seccion->getAforo() >= seccion->getCant_alumnos()) {
        std::string mensaje = "La seccion " + std::to_string(cod) + " ha alcanzado la cantidad maxima de alumnos o no  existe";
        notificacion(false, mensaje);

        esperar();
    }
    else{
        limpiar();

        CAlumno new_alm;
        std::string nombre, apellido;

        std::cout << "\nNombre: ";
        std::cin >> nombre;
        std::cout <<"\nApellido: ";
        std::cin >> apellido;


        new_alm.setNombre(nombre);
        new_alm.setApellido(apellido);
        new_alm.setSeccion(seccion->getCodigo(), seccion->getAforo());

        std::vector<CEvaluacion>* examenes= seccion->getExms();

        for(const auto &it:*examenes ){
            new_alm.addExamen(it);
        }

        seccion->addAlum(new_alm);

        std::string mensaje = "Se agrego a " + nombre + " " + apellido+ " a la seccion " + std::to_string(cod);
        notificacion(true, mensaje);

        esperar();
    }
}

void CMenu::setNotas() {
    int cod;
    limpiar();
    std::cout << "\nSeleccione el codigo de la seccion a la que desea agregar notas: \n";
    printSecciones();
    std::cout << "\n\n0:Salir\n";
    std::cout << "Seccion: ";
    std::cin >> cod;

    if (cod == 0) return;


    limpiar();
    CSeccion* seccion = findSeccion(cod);

    if(!seccion ) {
        std::string mensaje = "La seccion " + std::to_string(cod) + " ha alcanzado la cantidad maxima de alumnos o no  existe";
        notificacion(false, mensaje);

        esperar();
        return;
    }
    std::string exm_nombre ;
    std::vector <double> notas;

    seccion ->printExms();
    std::cout << "\nIngrese el nombre de la evaluacion que desea calificar: \n";
    std::cin >> exm_nombre;

    if(!seccion->isInExms(exm_nombre)){
        std::cout << "\nLa evaluacion no existe o no esta asignada a esta seccion\n";
        esperar();
        return;
    }

    limpiar();
    seccion->printAlumnos();
    std::cout << "\nIngrese las notas respectivas a cada alumno separadas por espacios\n";

    for (int i = 0; i < seccion->getAforo() ; i++){
        double n;

        std::cin >> n;
        if(n<0 || n>20){
            std::string mensaje = "\nNo puede ingresar notas mayores a 20 o menores a 0";
            notificacion(false, mensaje);
            esperar();
            return;
            break;
        }
        notas.push_back(n);

    }
    seccion->setNotas(exm_nombre, notas);
    esperar();
    limpiar();

}

void CMenu::ver_seccion(){
    int opc;
    printSecciones();

    std::cout << "\nSeleccione el codigo de la seccion que desea ver: ";
    std::cin >> opc;

    if(opc == 0) return;

    CSeccion* seccion = findSeccion(opc);

    limpiar();
    seccion->printSeccion();
    esperar();
}

void CMenu::ver_alumno(){
    std::string codigo ;
    limpiar();
    std::cout << "\nIngresar el codigo del alumno \n";
    std::cout << "El codigo debe tener el formato: \"seccion_numeroDeOrden\" ejm: 1_12\n";
    std::cout << "\nCodigo:";
    std::cin >> codigo;

    int n = (int)codigo.find('_');
    std::string codigo_seccion = codigo.substr(0,n);

    CSeccion* seccion = nullptr ;

    for(auto &it:secciones){
        if(std::to_string(it.getCodigo()) == codigo_seccion) {
            seccion = &it;
            break;
        }
    }

    if(!seccion){
        std::string mensaje =  " No se encontro la seccion ";
        notificacion(false, mensaje);
        esperar();
        return;
    }
    limpiar();
    CAlumno* alumno = seccion->buscarAlm(codigo);
    if (!alumno){
        std::string mensaje = "No se encontro al alumno";
        notificacion(false, mensaje);
        esperar();
        return;
    }
    alumno->printNotas();
    alumno -> MostrarAprobado();
    esperar();
}

void CMenu::cambiarNota(){
    std::cout << "\nSeleccione la seccion del alumno\n";
    int cod;
    printSecciones();

    std::cout << "\n\nSalir : 0";
    std::cout <<"\nOpcion: ";
    std::cin >> cod;
    if(cod == 0) return;


    CSeccion* seccion = findSeccion(cod);
    if(!seccion){
        std::string mensaje = " No se encontro la seccion ";
        notificacion(false,mensaje);
        esperar();
        return;
    }
    seccion->printAlumnos();

    std::string codigo_alm ;
    std::cout << "\n\nIngrese el codigo del alumno: \n";
    std::cin >> codigo_alm;

    CAlumno* alumno =  seccion->get_Alm(codigo_alm);
    if(!alumno){
        std::string mensaje = " No se encontro al alumno ";
        notificacion(false, mensaje);
        esperar();
        return;
    }
    /*if(!seccion->isInAlms(codigo_alm)){
        std::string mensaje =  " Ingrese un codigo valido ";
        notificacion(false, mensaje);
        esperar();
        return;
    }*/

    // CAlumno* alm = seccion->get_Alm(codigo_alm);
    if(alumno->getNotaModificada()) {
        std::string mensaje = " Ya se ha modificado  1 nota de este alumno anteriormente ";
        notificacion(false,mensaje);
        esperar();
        return;
    }
    limpiar();
    seccion ->printExms();
    std::string examen ;
    std::cout << "\nIngrese el nombre de la evaluacion a modificar:  ";
    std::cin >> examen;
    if(!seccion->isInExms(examen)) {
        std::string mensaje = " La evaluacion "+ examen + " no esta asignada a la seccion " + std::to_string(cod) + " o no existe ";
        notificacion(false, mensaje);
        esperar();
        return;
    }
    else{
        double nota;
        do{
            std::cout << "\nIngrese la nueva calificacion: ";
            std::cin >> nota;
            if(nota<0 || nota >20) std::cout << "\nIngrese una calificacion valida\n";
        } while(nota<0 || nota >20);

        alumno->editarNota(examen, nota);

        std::string  mensaje = " La nota ha sido modificada";
        notificacion(true, mensaje);

    }

    esperar();

}

void CMenu::eliminarAlum(){
    int cod;
    std::cout << "\nIngresar el codigo de la seccion del alumno nuevo: \n";
    printSecciones();
    std::cout << "\nSeccion: ";
    std::cin >> cod;

    CSeccion* seccion ;

    for (auto &it:secciones){
        if(cod == it.getCodigo()) {
            seccion = &it;
            break;
        }
    }
    tabulate::Table chart;
    chart.format()
            .font_color(Color::white)
            .padding_left(0)
            .padding_right(0)
            .corner("x")
            .column_separator("|");
    tabulate::Table::Row_t row;
    if(!seccion) {
        row.push_back("La seccion " + std::to_string(cod) + " no existe");

        chart.add_row(row);
        chart[0][0].format().color(Color::red).font_style({FontStyle::italic}).border_color(Color::yellow);
        limpiar();
        std::cout << chart << std::endl;

        //std::cout << "\nLa seccion " << cod << " no existe \n" ;
        esperar();
    }
    else{

        std::string _codigo;

        std::cout << "\nCodigo del alumno a retirar: ";
        std::cin >> _codigo;

        if(!seccion->isInAlms(_codigo)){
            limpiar();
            row.push_back("No se encontro al alumno con codigo:  " + _codigo );
            chart.add_row(row);
            chart[0][0].format().color(Color::red).font_style({FontStyle::italic, FontStyle::bold}).border_color(Color::yellow);
            std::cout << "\n";
            std::cout << chart << std::endl;
            return;
        }
        seccion->retirar_Alum(_codigo);

        limpiar();
        row.push_back("Alumno con codigo " + _codigo + " fue retirado de la seccion " + std::to_string(seccion->getCodigo()));
        chart.add_row(row);
        chart[0][0].format().color(Color::green).font_style({FontStyle::italic, FontStyle::bold}).border_color(Color::white);
        std::cout << "\n";
        std::cout << chart << std::endl;

        esperar();
    }

}

void CMenu::Ranking(){
    int opc;
    printSecciones();

    std::cout << "\nSeleccione el codigo de la seccion que desea ver: ";
    std::cin >> opc;

    if(opc == 0) return;

    CSeccion* seccion = findSeccion(opc);

    if(!seccion){
        std::string mensaje = " No se encontro la seccion ";
        notificacion(false,mensaje);
        esperar();
        return;
    }

    seccion->printRanking();
    esperar();

}

void CMenu::top_10(){
    int opc;
    for(int i  = 0; i < secciones.size(); i++){
        int cod = secciones[i].getCodigo();
        std::cout << "\n" << i+1  <<". Seccion: \t" << cod << "\n";
    }
    do{
        std::cout << "\nSeleccione la OPCION que desea ver: ";
        std::cin >> opc;
        if (opc <=0 || opc > secciones.size()) std::cout << "\nIngrese una opcion valida\n";
    } while (opc <=0 || opc > secciones.size());

    CSeccion* seccion = &secciones[opc-1];
    seccion->printTop10();
    esperar();
}

void CMenu::noelia(){
    int opc;
    printSecciones();

    std::cout << "\nSeleccione el codigo de la seccion que desea ver: ";
    std::cin >> opc;

    if(opc == 0) return;
    CSeccion* seccion = findSeccion(opc);

    if(!seccion ) {
        std::string mensaje = "La seccion " + std::to_string(opc) + " ha alcanzado la cantidad maxima de alumnos o no  existe";
        notificacion(false, mensaje);

        esperar();
        return;
    }

    std::vector<double> v = seccion -> crearVector();
    seccion->printStats(v);
    esperar();
    /*
    for (CSeccion i:secciones)
        if (seccion==i.getCodigo()){
            i.crearVector();
        }
    */

}

void CMenu::seccionAprobados() {

    //falta imrpimir el cuadrito con las secciones
    int cod;
    limpiar();
    std::cout << "\nSeleccione el codigo de la seccion a la que desea agregar notas: \n";
    printSecciones();
    std::cout << "\n\n0:Salir\n";
    std::cout << "Seccion: ";
    std::cin >> cod;

    if (cod == 0) return;


    limpiar();
    CSeccion* seccion = findSeccion(cod);

    if(!seccion ) {
        std::string mensaje = "La seccion " + std::to_string(cod) + " ha alcanzado la cantidad maxima de alumnos o no  existe";
        notificacion(false, mensaje);

        esperar();
        return;
    }



    seccion -> porcentajeAprobados();
    esperar();
}

void CMenu::Nota_Prom(){ //ANDRES
    /*int sec;
    for(int i  = 0; i < secciones.size(); i++){
        int msec = secciones[i].getCodigo();
        std::cout << "\n" << i+1  <<". Seccion: \t" << msec << "\n";
    }*/

    int cod;
    limpiar();
    std::cout << "\nSeleccione el codigo de la seccion a la que desea agregar notas: \n";
    printSecciones();
    std::cout << "\n\n0:Salir\n";
    std::cout << "Seccion: ";
    std::cin >> cod;

    if (cod == 0) return;

    limpiar();
    CSeccion* seccion = findSeccion(cod);

    if(!seccion ) {
        std::string mensaje = "La seccion " + std::to_string(cod) + " ha alcanzado la cantidad maxima de alumnos o no  existe";
        notificacion(false, mensaje);

        esperar();
        return;
    }
   // std::cout << "\nSeleccione la Seccion que desea ver: ";
    //std::cin >> sec;

    seccion->printSec_Prom();
    esperar();
}

//Menu

enum class Opciones { add_secc=1, add_alm, add_exm , ver_alm, set_notas,  cambiar_nota, ver_secc,  elm_alm ,top_10 , ranking, estats, aprobados, promxSec};

void CMenu::setOpcion() {
    limpiar();
    switch(Opciones(opcion)) {
        case Opciones::add_secc:  //
            addSeccion();
            break;
        case Opciones::add_alm:  //
            addAlumno();
            break;
        case Opciones::add_exm:  //
            addExam();
            break;
        case  Opciones::set_notas://
            setNotas();
            break;
        case  Opciones::ver_secc://
            ver_seccion();
            break;
        case Opciones::ver_alm:
            ver_alumno();
            break;
        case Opciones::cambiar_nota:
            cambiarNota();
            break;
        case Opciones::elm_alm:
            eliminarAlum();
            break;
        case Opciones::top_10:
            top_10();
            break;
        case Opciones::ranking:
            Ranking();
            break;
        case Opciones::estats:
            noelia();
            break;
        case Opciones::aprobados:
            seccionAprobados();
            break;
        case Opciones::promxSec:
            Nota_Prom();
            break;
        default:
            std::cout << "\nIngrese una opcion valida\n";
            break;
    }
}

void CMenu::imprimirMenu() {

    tabulate::Table opciones;
    opciones.add_row({"Operaciones por Seccion", "Operaciones por alumno"});
    opciones.add_row({" 1. Agregar seccion" ," 2. Agregar alumno" });
    opciones.add_row({" 3. Agregar evaluacion" , " 4.Ver informacion de un estudiante" });
    opciones.add_row({" 5. Ingresar notas por seccion", "6. Cambiar nota de un alumno" });
    opciones.add_row({" 7. Ver alumnos por seccion", " 8. Eliminar alumno" });
    opciones.add_row({" 9. Top 10", " " });
    opciones.add_row({" 10. Ranking", " " });
    opciones.add_row({" 11. Estadisticas" });
    opciones.add_row({" 11. Aprobados", " " });
    opciones.add_row({" 13. Promedio por seccion", " " });
    opciones.add_row({" 0  " ,"Salir" });

    opciones[0][0].format().font_color(Color::yellow).font_align(FontAlign::center).font_style({FontStyle::bold});
    opciones[0][1].format().font_color(Color::yellow).font_align(FontAlign::center).font_style({FontStyle::bold});

    opciones[10][0].format().font_align(FontAlign::center).font_color(Color::red).font_background_color(Color::white);
    opciones[10][1].format().font_style({FontStyle::italic}).font_align(FontAlign::center).font_color(Color::red).font_background_color(Color::white);
    for(int i = 1; i<10;i++){
        opciones[i][0].format().font_align(FontAlign::right);
        opciones[i][1].format().font_align(FontAlign::right);
    }

    limpiar();

    std::cout << opciones << std::endl;
    std::cout << "OPCION:  ";
    /*
    cout << "Elija una opcion\n\n";
    cout << "1. Agregar una seccion\n";
    cout << "2. Agregar un alumno\n";
    cout << "3. Agregar una evaluacion\n";
    cout << "4. Ingresar notas de toda una seccion\n";
    cout << "5. Ver alumnos de una seccion\n";
    cout << "6. Ver informacion de un estudiante\n";
    cout << "7. Cambiar una nota de un alumno \n";
    cout << "8. Top 10 por seccion\n\n";
    cout << "\nopcion:  ";*/

}
void CMenu::ejecutar() {
    do {
        imprimirMenu();
        std::cin >> opcion;
        setOpcion();
    } while (opcion != 0);
    std::cout << "Programa finalizado\n";
}