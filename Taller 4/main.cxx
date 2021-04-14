#include <iostream>
#include <fstream>
#include "quadtree.h"
#include "quadnodo.h"
#include <string>
#include <ctime>
#include <set>
#include <list>

void funcion(QuadNodo<int> *nodo, int cuadroNivel, int posicionX, int posicionY, int (&matriz)[256][256])
{
    QuadNodo<int> *nuevohijoExtIzqVar = nodo->obtenerHijoExtIzq();
    QuadNodo<int> *nuevohijoIzqVar = nodo->obtenerHijoIzq();
    QuadNodo<int> *nuevohijoDerVar = nodo->obtenerHijoDer();
    QuadNodo<int> *nuevohijoExtDerVar = nodo->obtenerhijoExtrDer();
    int contador = 0;
    if (nuevohijoExtIzqVar == NULL || nuevohijoIzqVar == NULL || nuevohijoDerVar == NULL || nuevohijoExtDerVar == NULL)
    {
        std::cout << "ALGUNO DE LOS HIJOS ES NULO" << std::endl;
    }
    

    if (nuevohijoExtIzqVar->obtenerDato() == 2)
    {
        funcion(nuevohijoExtIzqVar, (cuadroNivel / 2), posicionX, posicionY , matriz);
        contador++;
    }
    else
    {
        for (int i = posicionX; i < posicionX + cuadroNivel; i++)
        {
            for(int j = posicionY; j < posicionY + cuadroNivel; j++)
            {
                matriz[i][j] = nuevohijoExtIzqVar->obtenerDato();
            }
        } 
        contador++;
        
    }

    if (nuevohijoIzqVar->obtenerDato() == 2)
    {
        funcion(nuevohijoIzqVar, (cuadroNivel / 2), posicionX, posicionY + (cuadroNivel), matriz);
        contador++;
    }
    else
    {
        for (int i = posicionX; i < posicionX + cuadroNivel; i++)
        {
            for(int j = posicionY+ (cuadroNivel); j < posicionY + cuadroNivel*2; j++)
            {
                matriz[i][j] = nuevohijoIzqVar->obtenerDato();
            }
        } 
        contador++;
    }

    if (nuevohijoExtDerVar->obtenerDato() == 2)
    {
        funcion(nuevohijoExtDerVar, (cuadroNivel / 2), posicionX  + (cuadroNivel), posicionY , matriz);
        contador++;
    }
    else
    {
        for (int i = posicionX+ (cuadroNivel); i < posicionX + cuadroNivel*2; i++)
        {
            for(int j = posicionY; j < posicionY + cuadroNivel; j++)
            {
                matriz[i][j] = nuevohijoExtDerVar->obtenerDato();
            }
        } 
        contador++;
    }

    if (nuevohijoDerVar->obtenerDato() == 2)
    {
        funcion(nuevohijoDerVar, (cuadroNivel / 2), posicionX+ (cuadroNivel), posicionY + (cuadroNivel), matriz);
        contador++;
    }
    else
    {
        for (int i = posicionX+ (cuadroNivel); i < posicionX + cuadroNivel*2; i++)
        {
            for(int j = posicionY+ (cuadroNivel); j < posicionY + cuadroNivel*2; j++)
            {
                matriz[i][j] = nuevohijoDerVar->obtenerDato();
            }
        } 
        contador++;
    }
    

    std::cout << contador << std::endl;
}

/*

funcion1

cuadroPorNivel = 8;
llamado a fimcopm 2 (nodo, cuadronivel/2, posicion por hijo x / y)

funcion 2 recive 4

nodo actual

if nodoactual == 2 
    funcion 2 con cuadropornivel /2

for linea por cantidad cuadro nivel


    for columnas por cantidad cuadro nivel

*/

std::string reordenarCadena(std::string cadena)
{
    int posicionDos = 0;
    std::string nuevoS = "", aux;
    while (cadena.size() > 1)
    {
        for (int i = 0; i <= cadena.size(); i++)
        {
            if ((cadena[i] == '2') && (cadena.size() - (i + 1) >= 4))
            {
                posicionDos = i;
            }
        }

        aux = cadena.substr(posicionDos + 1, 4);
        nuevoS = aux + nuevoS;
        cadena.erase(posicionDos + 1, 4);
    }
    nuevoS = "2" + nuevoS;

    return nuevoS;
}

int main(int argc, char *argv[])
{
    Quadtree<int> arbol;
    std::string v = "2222222201111111111111221211210002110102121101012211002112110000002221001002100100221001002101112111221112201001201100112011200200100222202011112011111112121211012100012100111221122110021100002110211012112111201002211002111000202020100000002200022000102001112002020111120111200200100112121210210011111121222120001112000200012121011111200220011111220011200111111112121112112112211101211100202010000211021211000210002200202002001002200101112002011120011200200200112001122101101122211120110112201101120110112220111111111112211122111211101122011011201102121212100101210011212120001210111111122220110111111111211221121212100101210011122110212110002100021122111012111002020100000022002002001120011221011011202002001002200101112002011120011112121212000121011111111122211221121121100211011211121121100211002020211100000221210000210000002112112121101210011112112112112211012100000211211011121112211121110112201001102222011011220110111111212210021001002210010021001222101102000110220001021011111112212121210012100111111220002000210112002002001000220011220011111112212101111220001011111122111211211121112010021120211000001122022020110001102202001020111011220111111200200120011200200112001112111211121121110201002112112110021102110012222121210000210010100212000200012210110210111122022111011020201102011000112020201102011102200101112002001002222011111111111121221200111122001120011111111112112221112010012111211102020100001120220110112011022011011102212110211010212110121000122211002110000221100211100000022100100210210011211122111221112011011220110112011011222201111111111112212112211221000000212110102110121122110012010000002112121121001121210012100111122121212101111111221112111011202111000222000200010200200112101121200011120020201111120020011200111112202201101120110220110112011101122020010120010111212112211002112010000021211211001221000000211210011222100100210200011020022001120111112200112001111221210111120002101111122221220001020011111202002001001111222020111120111111111121112220110110112011011222220010112011111111111122112211212100101122121100021000000021210012120001210111112111222020100002211101211100002111211120110222011011201101122011111120020020010002222002011120011220010111111111112121222101101120020011200111111111221221122121101021101221000000002112112100111211211122011011020221100120100000202201101122001011201111220020011200112020111111122121210012100112121011111200020002000122120001112002001121011111211221211211001021211010211012211211002110021112111020201000000222100000000011211121112211121112010011220211102011001120201102011002222201120111111111212121121101122100000021121000122211010021001002210010021001121221021011102210112000111111122221121100211002112110021100002112111211102021110002022010011020110001122002001120011220020010022011011112200111111111212122221001020001102200110111200220010201111120011111111";
    std::string cadena;
    int matriz[256][256];

    /*202210021100010200010
    

                     2
    0             2            2               1
                0021           1020
                1000            0010*/

    cadena = reordenarCadena(v);
    arbol.insertar1(cadena);

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            matriz[i][j] = 5;
        }
    }

    funcion(arbol.nodoRaiz(),128, 0, 0, matriz);

    
}
