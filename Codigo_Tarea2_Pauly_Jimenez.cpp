#include <iostream>//teclado como input
#include <chrono> //medir tiempo
#include <pthread.h>//usar threads en linux 
#include <cmath>

using namespace std::chrono;
using namespace std;




//Entradas:el array principal
//Salidas: el array, con cada
//elemento elevado al cuadrado


void* PotenciaBIG(void* IN) {
    //ciclo for pasa por cada elemento
    int* Arr = (int*)IN;
    for (int k = 0; k < 100000; k++) {
        Arr[k] = pow(Arr[k], 2);

    }
    return NULL;



}
//Entradas:un array secundario
//Salidas: el array, con cada
//elemento elevado al cuadrado

void* PotenciaSMALL(void* IN) {
    //ciclo for pasa por cada elemento
    int* Arr = (int*)IN;
    for (int k = 0; k < 25000; k++) {
        Arr[k] = pow(Arr[k], 2);

    }

    return NULL;



}

int main()
{// se define el array msa grande
//y 4 arrays de un curto del tamano
    const int size = 100000;
    int BigArray[size];
    int Small1[(size / 4)];
    int Small2[(size / 4)];
    int Small3[(size / 4)];
    int Small4[(size / 4)];


    //se llena el array con numeros al azar
    std::cout << "Generando numeros al azar...\n";
    for (int i = 0; i < 100000; i++) {
        BigArray[i] = rand() % 10;
    }
    std::cout << "Listo.\n";


    //por medio de FORs, se parte BigArray
    //en 4 partes iguales
    std::cout << "Separando Array principal en 4 menores...\n";
    for (int j = 0; j < (size / 4); j++) {
        Small1[j] = BigArray[j];

    }
    for (int j = 0; j < (size / 4); j++) {
        Small2[j] = BigArray[j + (size / 4)];

    }
    for (int j = 0; j < (size / 4); j++) {
        Small3[j] = BigArray[j + (size / 2)];

    }
    for (int j = 0; j < (size / 4); j++) {
        Small4[j] = BigArray[j + ((size) * 3 / 4)];

    }

    std::cout << "Listo.\n";

    //thread unico que eleva los valores del BigArray al cudrado
    std::cout << "Caulculando con Single Thread...\n";



    //empieza el cronometro para single thread 
    auto startSingle = high_resolution_clock::now();



    pthread_t BA;
    pthread_create(&BA, NULL, PotenciaBIG, &BigArray);

    //para el cronometro, define duracion
    //y lo imprime
    pthread_join(BA, NULL);
    auto stopSingle = high_resolution_clock::now();
    auto durationSingle = duration_cast<microseconds>(stopSingle - startSingle);


    std::cout << "El tiempo de calculo Single Thread fue de:" << durationSingle.count() << " micro segundos." << endl;




    pthread_t S1;
    pthread_t S2;
    pthread_t S3;
    pthread_t S4;
    //pthread_t * Combo[]={&S1,&S2,&S3,&S4};






 //corrida de multithread
    std::cout << "Caulculando con Multi Thread...\n";
    //empieza el cronometro para single thread 
    auto startMulti = high_resolution_clock::now();



    pthread_create(&S1, NULL, PotenciaSMALL, &Small1);
    pthread_create(&S2, NULL, PotenciaSMALL, &Small2);
    pthread_create(&S3, NULL, PotenciaSMALL, &Small3);
    pthread_create(&S4, NULL, PotenciaSMALL, &Small4);



    //se espera a que terminen todos los threads
    pthread_join(S1, NULL);
    pthread_join(S2, NULL);
    pthread_join(S3, NULL);
    pthread_join(S4, NULL);
    //para el cronometro, define duracion
     //y lo imprime
    auto stopMulti = high_resolution_clock::now();
    auto durationMulti = duration_cast<microseconds>(stopMulti - startMulti);
    std::cout << "El tiempo de calculo MultiThread fue de:" << durationMulti.count() << " micro segundos." << endl;
    y termine main
        // se imprimen los tiempos, y se detiene el programa








}