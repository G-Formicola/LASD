
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include <string>

#include "../zlasdtest/test.hpp"

#include "../hashtable/opnadr/htopnadr.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"

/* ************************************************************************** */
// Main Menu
void Menu();

// Menu che permette di scegliere il tipo di test da eseguire
int SceltaTipoTest();

// Menu che permette di scegliere il tipo di struttura dati sfruttata concretamente
int SceltaTipoImplementazione();

// Menu che permette di scegliere il tipo dei dati che conterrà la struttura
int SceltaTipoDati();

// Menu che permette di scegliere il tipo di struttura dati sfruttata concretamente
int SceltaTipoImplementazione();

// Menu di funzionalità per i bst
void HashTableMenu(int,int);

// Genera un numero intero random
int IntegerGenerator();

// Genera un numero reale random
double DoubleGenerator();

// Genera una stringa random
std::string StringGenerator();


template<typename Data>
void AuxPrint(Data&, void*);

void AuxProdotto(const int&, const void* , void* ) ;

void AuxSomma(const double&, const void*, void* ) ;

void AuxConcat(const std::string&, const void* , void* ) ;


/* ************************************************************************** */

#endif
