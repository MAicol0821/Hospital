#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Paciente {
    int año_nacimiento;
    double valor_cita;
    vector<Paciente*> descendientes;
    
    Paciente(int año_nacimiento, double valor_cita) {
        this->año_nacimiento = año_nacimiento;
        this->valor_cita = valor_cita;
    }
};

class ArbolPacientes {
public:
    void agregarPaciente(int año_nacimiento, double valor_cita) {
        Paciente* p = new Paciente(año_nacimiento, valor_cita);
        pacientes[año_nacimiento].push_back(p);
        if (años.find(año_nacimiento) == años.end()) {
            años.insert(año_nacimiento);
        }
    }
    
    void agregarDescendiente(int año_ancestro, int año_descendiente, double valor_cita) {
        for (Paciente* ancestro : pacientes[año_ancestro]) {
            if (ancestro->año_nacimiento == año_ancestro) {
                Paciente* descendiente = new Paciente(año_descendiente, valor_cita);
                ancestro->descendientes.push_back(descendiente);
                pacientes[año_descendiente].push_back(descendiente);
                if (años.find(año_descendiente) == años.end()) {
                    años.insert(año_descendiente);
                }
            }
        }
    }
    
    double calcularValorCanceladoPorPaciente(int año_nacimiento) {
        double total = 0.0;
        for (Paciente* p : pacientes[año_nacimiento]) {
            total += p->valor_cita;
        }
        return total;
    }
    
    double calcularPromedioCanceladoPorAño() {
        double total = 0.0;
        int count = 0;
        for (int año : años) {
            double promedio = 0.0;
            int n = pacientes[año].size();
            for (Paciente* p : pacientes[año]) {
                promedio += p->valor_cita;
            }
            if (n > 0) {
                promedio /= n;
                total += promedio;
                count++;
            }
        }
        return total / count;
    }
    
private:
    map<int, vector<Paciente*>> pacientes;
    set<int> años;
};

int main() {
    ArbolPacientes arbol;
    int opcion;
    do {
        cout << "Seleccione una opción:\n";
        cout << "1. Agregar paciente\n";
        cout << "2. Agregar descendiente\n";
        cout << "3. Calcular valor cancelado por paciente\n";
        cout << "4. Calcular promedio cancelado por año\n";
        cout << "5. Salir\n";
        cin >> opcion;
        switch (opcion) {
            case 1: {
                int año_nacimiento;
                double valor_cita;
                cout << "Año de nacimiento: ";
                cin >> año_nacimiento;
                cout << "Valor de la cita: ";
                cin >> valor_cita;
                arbol.agregarPaciente(año_nacimiento, valor_cita);
                break;
            }
            case 2: {
                int año_ancestro, año_descendiente;
                double valor_cita;
                cout << "Año de nacimiento del ancestro: ";
                cin >> año_ancestro;
                cout << "Año de nacimiento del descendiente: ";
                cin >> año_descendiente;
                cout << "Valor de la cita: ";
                cin >> valor_cita;
                arbol.agregarDescendiente(año_ancestro, año_descendiente, valor_cita);
                break;
            }
            case 3: {
                int año_nacimiento;
                cout << "Año de nacimiento del paciente: ";
                cin >> año_nacimiento;
                double valor_cancelado = arbol.calcularValorCanceladoPorPaciente(año_nacimiento);
                cout << "Valor cancelado por el paciente: " << valor_cancelado << endl;
                break;
            }
            case 4: {
                double promedio_cancelado = arbol.calcularPromedioCanceladoPorAño();
                cout << "Promedio cancelado por año: " << promedio_cancelado << endl;
                break;
            }
            case 5: {
                cout << "Saliendo del programa...\n";
                break;
            }
            default: {
                cout << "Opción inválida. Intente de nuevo.\n";
                break;
            }
        }
    } while (opcion != 5);
    return 0;
}