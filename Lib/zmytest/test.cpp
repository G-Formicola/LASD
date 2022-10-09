#include "test.hpp"

#include <iostream>
#include <random>

/* ************************************************************************** */

void Menu(){

  int TipoTest, TipoDati, TipoImpl;

 do{
    // Scelta tra i test dello studente e quelli del Professore
    TipoTest = SceltaTipoTest();

    // Se l'utente sceglie i test dello studente
    if ( TipoTest == 1)
    {
         TipoDati = SceltaTipoDati();

         if (TipoDati != 0)
         {
            TipoImpl = SceltaTipoImplementazione();
         }

         if (TipoDati == 0 || TipoImpl == 0)
         {
           std::cout << "/* Indietro */" << '\n';
         }
         else
         {
           HashTableMenu(TipoDati,TipoImpl);
         }
    }

    // Se l'utente sceglie i test del Professore
    if ( TipoTest == 2 )
    {
      lasdtest();
    }

    if ( TipoTest == 0 )
    {
      std::cout << "/* Fine Esecuzione */" << '\n';
    }


  }while(TipoTest!=0);

}

// return 0 to exit
int SceltaTipoTest(){

  int scelta ;

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;
  std::cout<<"~ Libreria LASD A.A. 21/22 Formicola Giorgio N86002220 ~"<<std::endl ;
  std::cout<<"~                                                      ~"<<std::endl ;
  std::cout<<"~                        MENU                          ~"<<std::endl ;
  std::cout<<"~                                                      ~"<<std::endl ;
  std::cout<<"~ 1 : Test Studente                                    ~"<<std::endl ;
  std::cout<<"~ 2 : Test Professore                                  ~"<<std::endl ;
  std::cout<<"~                                                      ~"<<std::endl ;
  std::cout<<"~ 0 : Exit                                             ~"<<std::endl ;
  std::cout<<"~                                                      ~"<<std::endl ;
  std::cout<<"~                                           exercise5  ~"<<std::endl ;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;

  do {

    std::cout<<"Scelta : ";
    std::cin>>scelta ;
    if ( scelta < 0 || scelta > 2){
      std::cout << "Scelta non supportata ! Inserire un nuovo valore !" << std::endl;
    }

  } while( scelta < 0 || scelta > 2 );

  return scelta ;

}


// return 0 to exit
int SceltaTipoDati(){

    int scelta ;

    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;
    std::cout<<"~   Che tipo di dati dovrà contenere la struttura ?    ~"<<std::endl ;
    std::cout<<"~                                                      ~"<<std::endl ;
    std::cout<<"~ 1 : int - Numeri Interi                              ~"<<std::endl ;
    std::cout<<"~ 2 : double - Numeri Virgola Mobile                   ~"<<std::endl ;
    std::cout<<"~ 3 : string - Stringe di Caratteri                    ~"<<std::endl ;
    std::cout<<"~                                                      ~"<<std::endl ;
    std::cout<<"~ 0 : Indietro                                         ~"<<std::endl ;
    std::cout<<"~                                                      ~"<<std::endl ;
    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;

    do {

      std::cout<<"Scelta : ";
      std::cin>>scelta ;

      if ( scelta < 0 || scelta > 3 )
        std::cout << "/* Attenzione scelta non consentita */" << std::endl ;

  } while(scelta < 0 || scelta > 3);

  return scelta ;
}

int SceltaTipoImplementazione(){

  int scelta ;

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;
  std::cout<<"~              Che tipo di implementazione concreta si desidera                ~"<<std::endl ;
  std::cout<<"~             utilizzare per la realizzazione della struttura dati             ~"<<std::endl ;
  std::cout<<"~                                                                              ~"<<std::endl ;
  std::cout<<"~  1 : Gestione dei conflitti attraverso Indirizzamento Chiuso/Open Hashing    ~"<<std::endl ;
  std::cout<<"~  2 : Gestione dei conflitti attraverso Indirizzamento Aperto/Closed Hashing  ~"<<std::endl ;
  std::cout<<"~                                                                              ~"<<std::endl ;
  std::cout<<"~  0 : Indietro                                                                ~"<<std::endl ;
  std::cout<<"~                                                                              ~"<<std::endl ;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;

  do {

    std::cout<<"Scelta : ";
    std::cin>>scelta ;
    if ( scelta < 0 || scelta > 2){
      std::cout << "Scelta non supportata ! Inserire un nuovo valore !" << std::endl;
    }

  } while( scelta < 0 || scelta > 2 );

  return scelta ;
}

void HashTableMenu(int TipoDati, int TipoImpl){

  lasd::HashTable<int>* hashTableInt = nullptr  ;
  lasd::HashTable<double>* hashTableDouble = nullptr ;
  lasd::HashTable<std::string>* hashTableString = nullptr ;

  if ( TipoDati == 1 ) {
      if ( TipoImpl == 1 ){
        hashTableInt = new lasd::HashTableClsAdr<int>();
      }else{
        hashTableInt = new lasd::HashTableOpnAdr<int>();
      }
  }

  if ( TipoDati == 2 ) {
      if ( TipoImpl == 1 ){
        hashTableDouble = new lasd::HashTableClsAdr<double>();
      }else{
        hashTableDouble = new lasd::HashTableOpnAdr<double>();
      }
  }

  if ( TipoDati == 3 ){
    if ( TipoImpl == 1 ){
      hashTableString = new lasd::HashTableClsAdr<std::string>();
    }else{
      hashTableString = new lasd::HashTableOpnAdr<std::string>();
    }
  }



  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;
  std::cout<<"~               MENU Binary Search Tree                   ~"<<std::endl ;
  std::cout<<"~                                                         ~"<<std::endl ;
  std::cout<<"~ 1  : Inserimento nella struttura di N valori casuali    ~"<<std::endl ;
  std::cout<<"~ 2  : Visita e stampa tutti gli elementi                 ~"<<std::endl ;
  std::cout<<"~ 3  : Test di esistenza di un elemento                   ~"<<std::endl ;
  std::cout<<"~ 4  : Funzione Speciale                                  ~"<<std::endl ;
  std::cout<<"~ 5  : Inserimento di un elemento                         ~"<<std::endl ;
  std::cout<<"~ 6  : Cancellazione di un elemento                       ~"<<std::endl ;
  std::cout<<"~ 7  : Numero di chiavi presenti                          ~"<<std::endl ;
  std::cout<<"~ 8  : Svuotamento della struttura                        ~"<<std::endl ;
  std::cout<<"~                                                         ~"<<std::endl ;
  std::cout<<"~ 0  : Indietro                                           ~"<<std::endl ;
  std::cout<<"~                                                         ~"<<std::endl ;
  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;

  int operazione ;
  long numElem ;
  ulong dimen ;

  do
  {

    std::cout<<"Scelta : ";
    std::cin>>operazione ;

    switch (operazione) {
      case 0:
      // Do Nothing
      break;

      // Popolamento struttura
      case 1:

          do {

                std::cout<<"Quanti elementi dovrà contenere la tabella hash  ? : ";
                std::cin>>numElem ;

                if ( numElem < 0 )
                std::cout << "/* Attenzione scelta non consentita */" << std::endl ;

          } while(numElem < 0);

          dimen = (ulong) numElem ;

          if ( TipoDati == 1 ) {
              for (ulong index = 0; index < numElem ; index ++ ){
                int tmp = IntegerGenerator();
                hashTableInt->Insert(tmp);
                std::cout << tmp << std::endl ;
              }
          }

          if ( TipoDati == 2 ) {
              for (ulong index = 0; index < numElem ; index ++ ){
                double tmp = DoubleGenerator();
                hashTableDouble->Insert(tmp);
                std::cout << tmp << std::endl ;

              }
          }

          if ( TipoDati == 3 ){
            for (ulong index = 0; index < numElem ; index ++ ){
              std::string tmp = StringGenerator();
              hashTableString->Insert(tmp);
              std::cout << tmp << std::endl ;

            }
          }

          std::cout << "/* Inserimento andato a buon fine (Eccetto per eventuali valori generati ripetutamente che saranno inseriti soltanto una volta) */" << std::endl ;

      break;

      // Visita e stampa tutti gli elementi
      case 2:

      if ( TipoDati == 1 ) {
          hashTableInt->Map(&AuxPrint<int>, nullptr);
          std::cout << std::endl ;
      }

      if ( TipoDati == 2 ) {
          hashTableDouble->Map(&AuxPrint<double>, nullptr);
          std::cout << std::endl ;
      }

      if ( TipoDati == 3 ){
          hashTableString->Map(&AuxPrint<std::string>, nullptr);
          std::cout << std::endl ;
      }

      std::cout << "/* Fine visita */" << std::endl ;

      break;


      //  Test di esistenza di un elemento
      case 3:

      if ( TipoDati == 1 ){
            int value ;
            bool result ;
            std::cout << "Inserire il valore per controllarne l'esistenza : ";
            std::cin>>value ;
            result = hashTableInt->Exists(value);
            if(result == true)
            {
                  std::cout << "/* Valore presente all'interno della struttura dati */" << std::endl ;
            }
            else
            {
                  std::cout << "/* Valore assente all'interno della struttura dati */" << std::endl ;
            }
        }

        if ( TipoDati == 2 ){
          double value ;
          bool result ;
          std::cout << "Inserire il valore per controllarne l'esistenza : ";
          std::cin>>value ;
          result = hashTableDouble->Exists(value);
          if(result == true)
          {
                std::cout << "/* Valore presente all'interno della struttura dati */" << std::endl ;
          }
          else
          {
                std::cout << "/* Valore assente all'interno della struttura dati */" << std::endl ;
          }
        }

        if ( TipoDati == 3 ){
          std::string value ;
          bool result ;
          std::cout << "Inserire il valore per controllarne l'esistenza : ";
          std::cin>>value ;
          result = hashTableString->Exists(value);
          if(result == true)
          {
                std::cout << "/* Valore presente all'interno della struttura dati */" << std::endl ;
          }
          else
          {
                std::cout << "/* Valore assente all'interno della struttura dati */" << std::endl ;
          }
        }

      break;

      //  Funzione Speciale
      case 4 :

          int limit ;

          std::cout<<"Verrà ora calcolata una delle seguenti informazioni in base al tipo di dati scelto : "<<std::endl ;
          std::cout<<"1 - INTERI - saranno moltiplicati tutti gli interi minori di N dato in input "<<std::endl ;
          std::cout<<"2 - Double - saranno sommati tra loro tutti i double maggiori di N "<<std::endl ;
          std::cout<<"3 - STRING - saranno concatenate le stringhe di lungezza minore o uguale ad N "<<std::endl ;
          std::cout<<"Inserire un valore numerico per N : " ;
          std::cin >> limit ;


          std::cout << "-------" << std::endl << "Il risultato è : " ;
          // interi
          if ( TipoDati == 1 ) {
            int resultI = 1;
            hashTableInt->Fold(&AuxProdotto, &limit, &resultI );
            if (resultI == 1)
            {
            std::cout << "0" << std::endl ;
            }
            else
            {
            std::cout << resultI << std::endl ;
            }
          }

          // double
          if ( TipoDati == 2 ) {
            double resultF = 0;
            hashTableDouble->Fold(&AuxSomma, &limit, &resultF);
            std::cout << resultF << std::endl ;
          }

          // stringhe
          if ( TipoDati == 3 ){
            std::string resultS {""};
            hashTableString->Fold(&AuxConcat, &limit, &resultS);
            if (resultS == "")
            {
            std::cout << " Stringa Vuota !" << std::endl ;
            }
            else
            {
            std::cout << resultS << std::endl ;
            }
          }

      break ;


      // Inserimento di un elemento
      case 5 :


            if ( TipoDati == 1 ){
                  int value ;
                  bool result ;
                  std::cout << "Inserire il valore da inserire nella struttura : ";
                  std::cin>>value ;
                  result = hashTableInt->Insert(value);
                  if(result == true)
                  {
                        std::cout << "/* Inserimento nella struttura riuscito correttamente */" << std::endl ;
                  }
                  else
                  {
                        if (hashTableInt->Exists(value))
                          std::cout << "/* Inserimento non andato a buon fine, il dato già presente all'interno della struttura */" << std::endl ;
                        else
                          std::cout << "/* Inserimento non andato a buon fine, motivo sconosciuto */" << std::endl ;
                  }
              }

              if ( TipoDati == 2 ){
                double value ;
                bool result ;
                std::cout << "Inserire il valore per controllarne l'esistenza : ";
                std::cin>>value ;
                result = hashTableDouble->Insert(value);
                if(result == true)
                {
                      std::cout << "/* Inserimento nella struttura riuscito correttamente */" << std::endl ;
                }
                else
                {
                      if (hashTableDouble->Exists(value))
                        std::cout << "/* Inserimento non andato a buon fine, il dato già presente all'interno della struttura */" << std::endl ;
                      else
                        std::cout << "/* Inserimento non andato a buon fine, motivo sconosciuto */" << std::endl ;
                }
              }

              if ( TipoDati == 3 ){
                std::string value ;
                bool result ;
                std::cout << "Inserire il valore per controllarne l'esistenza : ";
                std::cin>>value ;
                result = hashTableString->Insert(value);
                if(result == true)
                {
                      std::cout << "/* Inserimento nella struttura riuscito correttamente */" << std::endl ;
                }
                else
                {
                      if (hashTableString->Exists(value))
                        std::cout << "/* Inserimento non andato a buon fine, il dato già presente all'interno della struttura */" << std::endl ;
                      else
                        std::cout << "/* Inserimento non andato a buon fine, motivo sconosciuto */" << std::endl ;
                }
              }

      break ;

      // Cancellazione di un elemento
      case 6 :


            if ( TipoDati == 1 ){
                  int value ;
                  bool result ;
                  std::cout << "Inserire il valore da rimuovere dalla struttura : ";
                  std::cin>>value ;
                  result = hashTableInt->Remove(value);
                  if(result == true)
                  {
                        std::cout << "/* Rimozione dalla struttura riuscita correttamente */" << std::endl ;
                  }
                  else
                  {
                        if (hashTableInt->Exists(value))
                          std::cout << "/* Rimozione non andata a buon fine, il dato è presente all'interno della struttura, ed il motivo sconosciuto */" << std::endl ;
                        else
                          std::cout << "/* Rimozione non andata a buon fine, dato non presente */" << std::endl ;
                  }
              }

              if ( TipoDati == 2 ){
                double value ;
                bool result ;
                std::cout << "Inserire il valore da rimuovere dalla struttura : ";
                std::cin>>value ;
                result = hashTableDouble->Remove(value);
                if(result == true)
                {
                      std::cout << "/* Rimozione dalla struttura riuscita correttamente */" << std::endl ;
                }
                else
                {
                      if (hashTableDouble->Exists(value))
                        std::cout << "/* Rimozione non andata a buon fine, il dato è presente all'interno della struttura, ed il motivo sconosciuto */" << std::endl ;
                      else
                        std::cout << "/* Rimozione non andata a buon fine, dato non presente */" << std::endl ;
                }
              }

              if ( TipoDati == 3 ){
                std::string value ;
                bool result ;
                std::cout << "Inserire il valore da rimuovere dalla struttura : ";
                std::cin>>value ;
                result = hashTableString->Remove(value);
                if(result == true)
                {
                      std::cout << "/* Rimozione dalla struttura riuscita correttamente */" << std::endl ;
                }
                else
                {
                      if (hashTableString->Exists(value))
                        std::cout << "/* Rimozione non andata a buon fine, il dato è presente all'interno della struttura, ed il motivo sconosciuto */" << std::endl ;
                      else
                        std::cout << "/* Rimozione non andata a buon fine, dato non presente */" << std::endl ;
                }
              }

      break ;


      // Numero di chiavi presenti
      case 7:

      ulong dim ;

      if ( TipoDati == 1 ) {
          dim = hashTableInt->Size();
          std::cout << std::endl ;
      }

      if ( TipoDati == 2 ) {
          dim = hashTableDouble->Size();
          std::cout << std::endl ;
      }

      if ( TipoDati == 3 ){
          dim = hashTableString->Size();
          std::cout << std::endl ;
      }

      std::cout << "/* Dimensione della struttura : "<<dim<<" */"<< std::endl ;

      break;



      // Svuotamento della struttura
      case 8:

      if ( TipoDati == 1 ) {
          hashTableInt->Clear();
          std::cout << std::endl ;
      }

      if ( TipoDati == 2 ) {
          hashTableDouble->Clear();
          std::cout << std::endl ;
      }

      if ( TipoDati == 3 ){
          hashTableString->Clear();
          std::cout << std::endl ;
      }

      std::cout << "/* Struttura svuotata correttamente */" << std::endl ;

      break;


      default:
        std::cout << "/* Attenzione scelta non consentita */" << std::endl ;
      break;

    }

    std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl ;

  } while(operazione != 0); // 0 indica la scelta da parte dell'utente di tornare indietro al menù principale

  if(hashTableInt != nullptr)
    delete hashTableInt;
  if(hashTableDouble != nullptr)
    delete hashTableDouble;
  if(hashTableString != nullptr)
    delete hashTableString;
}


// Funzioni Ausiliari


int IntegerGenerator(){
  std::default_random_engine genx(std::random_device{}());
  std::uniform_int_distribution<int> distx(-100000, 100000);
  int number = distx(genx) ;
  return number ;
}

double DoubleGenerator(){
  std::default_random_engine genx(std::random_device{}());
  std::uniform_int_distribution<int> distx(-100000, 1000);
  int number1 = distx(genx) ;
  int number2 = distx(genx) ;
  double doubleNumber = (static_cast<double>(number1)/static_cast<double>(number2)) ;
  int integerPart = doubleNumber ;
  double support = round((doubleNumber-integerPart)*100) ;

  return static_cast<double>(integerPart)+(1.0/100)*support ;
}

std::string StringGenerator(){
  std::array<std::string, 36> alfabeto {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","1","2","3","4","5","6","7","8","9","0"} ;
  std::string result = "";

  std::default_random_engine genx(std::random_device{}());
  std::uniform_int_distribution<int> distx(0, 35);

  int length = distx(genx);
  int x ;

  for ( ulong i = 0 ; i<length ; i++ ){
    x = distx(genx);
    result = result + alfabeto[x] ;
  }
  return result ;
}


template <typename Data>
void AuxPrint(Data& dat, void* _) {
  std::cout << dat << std::endl;
}


void AuxProdotto(const int& dat, const void* limit, void* result){
    if ( dat < *((int*)limit) ){
      *((int*)result) = (*((int*)result)) * dat ;
    }
}


void AuxSomma(const double& dat, const void* limit, void* result){
    if ( dat > *((double*)limit) ){
      *((double*)result) = *((double*)result) + dat ;
    }
}

void AuxConcat(const std::string& dat, const void* limit, void* result) {
  if ( dat.length() <= *((int*)limit) ){
    ((std::string*) result)->append(dat);
  }
}
