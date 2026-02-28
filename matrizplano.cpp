#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath> 
#include <cctype>

using namespace std;

const int ANCHO = 20; 
const int ALTO = 20;  

class Plano 
{
private:
    char matriz[ALTO][ANCHO]; 

public:
    Plano() 
    {
        limpiar();
    }

    void limpiar() 
    {
        for (int i = 0; i < ALTO; i++) 
        {
            for (int j = 0; j < ANCHO; j++) 
            {
                matriz[i][j] = '.';
            }
        }
    }

    void pintarCoordenada(int x, int y, char simbolo) 
    {
        if (x < 0 || x >= ANCHO || y < 0 || y >= ALTO) 
        {
            cout << ">> Error: El punto (" << x << "," << y << ") no esta dentro del plano." << endl;
            return; 
        }

        int columnaMatriz = x; 
        int piso = ALTO - 1;     
        int filaMatriz = piso - y; 

        matriz[filaMatriz][columnaMatriz] = simbolo;
    }

    void mostrar() 
    {
        cout << "\n   EJE Y " << endl;
        for (int i = 0; i < ALTO; i++) {
            int filaNumero = ALTO - 1 - i;

            if (filaNumero < 10) cout << " " << filaNumero << " | ";
            else                 cout << filaNumero << " | ";

            for (int j = 0; j < ANCHO; j++) 
            {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }

        cout << "    "; 
        for(int k=0; k<ANCHO; k++) cout << "--"; 
        cout << endl;

        cout << "    "; 
        for (int j = 0; j < ANCHO; j++) 
        {
            if (j < 10) cout << j << " "; 
            else        cout << j;        
        }
        cout << "\n EJE X" << endl;
    }
};

class Punto 
{
private:
    int x, y; 
    char nombre; 

public:
    Punto(int _x, int _y, char _nombre) 
    { 
        x = _x;
        y = _y;
        nombre = _nombre;
    }

    void dibujate(Plano &plano) const
    {
        plano.pintarCoordenada(x, y, nombre); 
    }

    int getX() const { return x; }
    int getY() const { return y; }
    char getNombre() const { return nombre; }

    double calcularDistancia(const Punto &otro) const 
    {
        return sqrt(pow(x - otro.x, 2) + pow(y - otro.y, 2));
    }
};

void predecirKNN(const Punto& nuevoPunto, const vector<Punto>& listaPuntos) 
{
    if (listaPuntos.empty()) 
    {
        cout << "\n>> [KNN] Es el primer punto. Aun no hay vecinos en el plano.\n";
        return;
    }

    double distanciaMinima = 999999.0; 
    char vecinoMasCercano = ' ';

    for (const Punto& p : listaPuntos) 
    {
        double distanciaActual = nuevoPunto.calcularDistancia(p);

        if (distanciaActual < distanciaMinima) 
        {
            distanciaMinima = distanciaActual;
            vecinoMasCercano = p.getNombre();
        }
    }

    cout << "\n>> [KNN] El vecino mas cercano al nuevo Punto es el Punto '" << vecinoMasCercano 
         << "' a una distancia de " << distanciaMinima << " unidades.\n";
}

// ==============MAIN====================
int main() 
{
    Plano miPlano;
    vector<Punto> listaPuntos; 
    char proximoNombre = 'A'; 

    int x, y;
    int opcion;

    while (true) 
    {
        miPlano.limpiar();

        for (const Punto &p : listaPuntos) 
        {
            p.dibujate(miPlano);
        }

        miPlano.mostrar();

        
        cout << "\n[1] Agregar Punto  [2] Medir Distancia manual  [3] Borrar Todo  [4] Salir: ";
        cin >> opcion;

        if (opcion == 1) 
        {
            cout << "Coord X (0-" << ANCHO-1 << "): "; cin >> x;
            cout << "Coord Y (0-" << ALTO-1 << "): "; cin >> y;
            
            Punto nuevoPunto(x, y, proximoNombre);

            predecirKNN(nuevoPunto, listaPuntos);

            listaPuntos.push_back(nuevoPunto);

            proximoNombre++; 
            if (proximoNombre > 'Z') proximoNombre = 'A'; 
            
            cout << "\nPresiona Enter para continuar...";
            cin.ignore(); 
            cin.get(); 
        }
        else if (opcion == 2) 
        {
            
            if (listaPuntos.size() < 2) 
            {
                cout << "\n>> Error: Necesitas al menos 2 puntos en el plano para medir distancias.\n";
            } 
            else 
            {
                char n1, n2;
                cout << "Ingresa la letra del primer punto: "; cin >> n1;
                cout << "Ingresa la letra del segundo punto: "; cin >> n2;

                n1 = toupper(n1);
                n2 = toupper(n2);

                bool encontrado1 = false, encontrado2 = false;
                Punto p1(0,0,' '), p2(0,0,' ');

                
                for (const Punto& p : listaPuntos) 
                {
                    if (p.getNombre() == n1) { p1 = p; encontrado1 = true; }
                    if (p.getNombre() == n2) { p2 = p; encontrado2 = true; }
                }

                if (encontrado1 && encontrado2) 
                {
                    double dist = p1.calcularDistancia(p2);
                    cout << "\n>> La distancia entre el Punto " << p1.getNombre() 
                         << " y el Punto " << p2.getNombre() << " es: " << dist << " unidades.\n";
                } 
                else 
                {
                    cout << "\n>> Error: Uno o ambos puntos no existen en el plano.\n";
                }
            }
            cout << "Presiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if (opcion == 3) 
        {
            listaPuntos.clear(); 
            proximoNombre = 'A'; 
        }
        else if (opcion == 4) 
        {
            break;
        }
    }

    return 0;
}