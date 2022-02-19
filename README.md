# DinerHub
Progetto per il corso di Advanced Programming Languages del corso di Laurea Magistrale LM-32, Università degli Studi di Catania, A.A. 2021/2022.

Progetto sviluppato da **Daniele Amenta** e **Daniele D'Agosta**.

##
Lo scopo dell’elaborato è quello di realizzare un’applicazione che consenta la gestione degli ordini nei ristoranti.

All'interno della directory __*/src*__ si trova il codice sorgente dei moduli che compongono l'applicazione, suddiviso in subdirectory.

Per maggiori dettagli sulla struttura e funzionamento del progetto, è possibile consultare la relazione dal nome "**DinerHub - docs**", presente all'interno della directory __*/docs*__.

# Dipendenze
Per avviare correttamente il sistema è necessario installare sulla propria macchina oltre a Python v3.10, C++ ed C# le seguenti dipendenze tramite i link forniti in basso:

- [MongoDB](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-windows/) , database NoSQL usato per la gestione della persistenza

Come IDE di riferimento per il **Server** C# è stato utilizzato Visual Studio 2022 ed è stato necessario installare i seguenti pacchetti tramite il gestore pacchetti NuGet:

- Microsoft.AspNetCore.Authentication.JwtBearer v3.1.20;
- Microsoft.AspNetCore.Mvc.NewtonsoftJson v3.1.6;
- Microsoft.IdentityModel.Tokens v6.14.0;
- MongoDB.Driver v2.12.4;
- Swashbuckle.AspNetCore v6.2.3;
- System.IdentityModel.Tokens.Jwt v6.14.0.

Come IDE di riferimento per il **Client** C++ è stato utilizzato Visual Studio 2022 ed è stato necessario installare i seguenti pacchetti tramite la seguente procedura:

- installare il gestore di pacchetti [vcpkg](https://github.com/Microsoft/vcpkg) seguendo la procedura linkata,
- aprire la shell nel percorso in cui si trova il file _vcpkg.exe_ e digitare i seguenti comandi:
```[shell]
.\vcpkg install cpr:x64-windows
.\vcpkg install nlohmann-json:x64-windows
.\vcpkg install openssl:x64-windows
.\vcpkg integrate install
```

Per quanto riguarda lo **Stats Server** sviluppato in Python è stato utilizzato PyCharm come IDE di riferimento ed è necessario installare le seguenti librerie usando la pip:
- pymongo;
- matplotlib;
- numpy;
- flask;
- pyjwt.

## Avvio
Prima di avviare l’applicazione assicurarsi che le porte 5276, 5000 e 27017 siano disponibili perché utilizzate rispettivamente da Server, Stats Server e MongoDB.
Per avviare correttamente l’applicazione occorre:
- Avviare un’istanza di **MongoDB** sulla propria macchina;
- Compilare e lanciare il **Server**;
- Lanciare lo **Stats Server**, digitando il comando all’interno della directory del progetto:
```[shell]
python .\src\Stats-Server\main.py
```
- Compilare e lanciare il **Client**.