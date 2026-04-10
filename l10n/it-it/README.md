![Stumpless logo](./assets/logo-and-name.svg)

**Una libreria di logging in C progettata per alte prestazioni e un ricco set di funzionalità.**

[![Linux Builds](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/linux.yml)
[![Windows Builds](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/windows.yml)
[![Mac Builds](https://github.com/goatshriek/stumpless/actions/workflows/mac.yml/badge.svg)](https://github.com/goatshriek/stumpless/actions/workflows/mac.yml)
[![Coverage Report](https://codecov.io/gh/goatshriek/stumpless/branch/latest/graph/badge.svg)](https://codecov.io/gh/goatshriek/stumpless)
[![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=stumpless&metric=alert_status)](https://sonarcloud.io/dashboard?id=stumpless)
[![Gitter](https://badges.gitter.im/stumpless/community.svg)](https://gitter.im/stumpless/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Apache 2.0 License](https://img.shields.io/badge/license-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v2.1-ff69b4.svg)](https://github.com/goatshriek/stumpless/blob/latest/docs/CODE_OF_CONDUCT.md)


[Français](./l10n/fr-fr/README.md) | [한국어](./l10n/ko-kr/README.md) | [简体中文](./l10n/zh-cn/自述.md)


[funzionalità chiave](#funzionalità-chiave) |
[Compilazione e installazione](#compilazione-e.installazione) |
[Utilizzi di base](#utlizzi-di-base) |
[Contribuire](#contribuire)


## funzionalità chiave
Stumpless offre molte funzionalità che rendono il logging in C veloce e facile:
 * invia log a [molteplici destinazioni](#a-cosa-può-inviare-i-log) come Splunk, rsyslog,
   journald, the Windows Event Log, sqlite, e altro!
 * logging strutturato e non strutturato per soddisfare ogni esigenza
 * compilabile su Linux, Windows, Mac, FreeBSD, MinGW, MSYS2, Cygwin, DOS, e altro!
 * thread safe
 * può essere regolato o rimosso durante la compilazione per un zero cost runtime
 * localizzato in diverse lingue 🇦🇱 🇧🇷 🇧🇬 🇨🇳 🇨🇿 🇩🇪 🇩🇰 🇪🇸 🇫🇷 🇬🇷 🇭🇺 🇮🇳 🇮🇱 🇮🇹
   🇯🇵 🇰🇪 🇰🇷 🇵🇱 🇸🇰 🇱🇰 🇸🇪 🇹🇷 🇺🇸 🇪🇬
   ([aggiungi la tua!](https://github.com/goatshriek/stumpless/blob/latest/docs/localization.md))
 * facile accesso a
   [documentazione](https://goatshriek.github.io/stumpless/docs/c/latest/),
   [esempi](https://github.com/goatshriek/stumpless/tree/latest/docs/examples),
   e [supporto](https://gitter.im/stumpless/community).


### A cosa può inviare i log?
L'obbiettivo principale di questa libreria è fornire un'interfaccia di logging
coerente per una grande varietà di targets. Ciò significa che puoi concentrarti
sulla definizione degli eventi e della loro destinazione, senza dover cercare
altri SDK o aggiungere daemon e plugin. Stumpless può scrivere log su:
 * Semplici buffer di caratteri
 * File e stream
 * Socker Unix (come un daemon syslog locale)
 * Server di rete (IPv4 o IPv6, TCP o UDP)
 * Servizio Systemd Journald
 * Database Sqlite3
 * Registro eventi di Windows
 * Funzioni personalizzate, per qualsiasi altra necessità!

Non vedi quello che ti serve? Crea un
[issue](https://github.com/goatshriek/stumpless/issues/new?template=feature_request.md)
con la tua richiesta e la inseriremo nella nostra
[roadmap](https://github.com/goatshriek/stumpless/blob/latest/docs/roadmap.md)!


## Compilazione e Installazione Rapida
Stumpless richiede solo cmake e una toolchain di compilazione supportata da cmake
(come GCC o Visual Studio) per essere compilato.

```sh
# clonare la versione più recente della source tree
git clone git@github.com:goatshriek/stumpless.git

# creare una nuova build directory
mkdir build
cd build

# configurare la nuova build
cmake ../stumpless

# compilazione di stumpless (con 4 thread - regola come preferisci)
cmake --build . --parallel 4

# installa la libreria (probabilmente è necessario sudo per farlo)
sudo cmake --install .
```

Consulta le [Istruzioni di Installazione](../../INSTALL.md) per maggiori dettagli
sulla compilazione e l'installazione di stumpless in diversi ambienti e/o con
altre toolchain.


## Utilizzo di Base
Il modo più semplice per iniziare è usare la funzione `stumplog` come sostituto
diretto della funzione `syslog` della libreria standard:

```c
// se sei abituato/a a farlo:
syslog( LOG_INFO | LOG_USER, "My message #%d", count );

// allora puoi iniziare a cambiarlo a questo:
stumplog( LOG_INFO | LOG_USER, "My message #%d", count );
```

Se non hai aperto una destinazione (target), i messaggi verranno registrati nella
destinazione predefinita per la piattaforma: su Linux è `/dev/log`, su sistemi
Mac è `/var/run/syslog`, mentre su macchine Windows è il Registro Eventi di
Windows (Windows Event Log). Se apri una o più destinazioni prima di chiamare
`stumplog`, i log verranno inviati alla destinazione aperta più recentemente.

Se desideri una chiamata di funzione ancora più breve, puoi usare la funzione
`stump` per inviare un messaggio alla destinazione corrente. Puoi anche usare gli
specificatori di formato proprio come faresti con `printf`:

```c
stump( "Login attempt failure #%d for user %s", count, username );
```

Se non hai bisogno degli specificatori di formato, usa una delle varianti `_str`:
è sia più veloce che più sicuro!

```c
stump_str( "Login failure! See structured data for info." );
```

Se vuoi aprire una destinazione specifica invece di usare quella predefinita,
apri semplicemente quella di cui hai bisogno e inizia a inviare messaggi. Ad
esempio, per registrare i log su un file chiamato `example.log`:

```c
target = stumpless_open_file_target( "example.log" );

// per impostazione predefinita usa l'ultima destinazione aperta
stump( "Login attempt failure #%d for user %s", count, username );
```

Inviare messaggi via rete a sistemi come Splunk o rsyslog è altrettanto facile:

```c
target = stumpless_open_udp4_target( "send-to-splunk-example",
                                     "mylogserver.com" ); // o usa un IP
stump( "Login attempt failure #%d for user %s", count, username );
```

Se hai più destinazioni, puoi inviare messaggi a una destinazione specifica in
questo modo:

```c
stumpless_add_message( target,
                       "Login attempt failure #%d for user %s",
                       count,
                       username );
```


### Scorciatoie per la Gravità
È comune specificare i livelli di gravità direttamente nelle chiamate di logging, quindi stumpless fornisce alcune macro per rendere tutto meno verboso e più efficiente. Ad esempio, per registrare messaggi con una gravità di tipo INFO, puoi fare così:

```c
stump_i( "this gets logged as an info message" );
```

E se vuoi vedere anche le informazioni sul file sorgente, il numero di riga e il
nome della funzione in ogni messaggio, puoi usare `_t` (la 't' sta per trace):

```c
stump_t( "this includes source info" );
```

L'uso di queste funzioni offre l'ulteriore vantaggio di poterle rimuovere in fase
di compilazione semplicemente definendo i simboli `STUMPLESS_ENABLE_UPTO` o
`STUMPLESS_DISABLE_DOWNTO`. Ciò rende facile cambiare i livelli di logging tra le
diverse build, ad esempio per avere versioni di produzione (prod) e di debug
senza differenze nel codice sorgente.

```c
// assicurati di definire questo simbolo prima di includere stumpless.h
#define STUMPLESS_ENABLE_UPTO_INFO

// ...

// questo log verrà registrato correttamente
stump_i( "I'm doing that thing you asked" );

// questo messaggio di debug viene rimosso completamente: nessun impatto sulle prestazioni
stump_d( "DEBUG info: %d, %d, %s", thing_1, thing_2, stringy_thingy );
```

Consulta gli header in
[stumpless/level](https://github.com/goatshriek/stumpless/tree/latest/include/stumpless/level)
per vedere l'elenco completo delle funzioni rapide per la gravità, oppure l'
[esempio sui livelli di gravità](https://github.com/goatshriek/stumpless/tree/latest/docs/examples/severity_level)
per vedere un programma completo in azione.


### Ancora più esempi
Per esempi più dettagliati sugli scenari sopra citati, sull'uso di tipi di
destinazione specifici, su come gestire strutture di messaggi più complicate e
altro ancora, dai un'occhiata agli [esempi](../../docs/examples). Questi
includono file di codice d'esempio annotati da compilare, eseguire e modificare
per aiutarti a iniziare.


## Contribuire
Hai notato un problema o hai una richiesta di funzionalità? Crea semplicemente un
issue utilizzando uno dei template e risponderemo il più rapidamente possibile.
Puoi anche consultare le [Linee guida peril contributo](../../docs/CONTRIBUTING.md) del
progetto per maggiori dettagli sui diversi modi in cui puoi restituire qualcosa alla
comunità open source!

Se vuoi scrivere del codice o apportare un aggiornamento tu stesso, dai un'occhiata
alla [guida allo sviluppo](../../docs/development.md) per un orientamento
dettagliato. Ci sono diverse opzioni in base al tuo livello di esperienza e alla
tua familiarità nel dare contributi.

La prima opzione è scorrere l'elenco dei problemi (issue) contrassegnati con
l'etichetta [good first issue](https://github.com/goatshriek/stumpless/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22). Questi problemi sono selezionati per essere un lavoro piccolo ma
significativo e includono dettagli sull'approccio generale da adottare per
completarli. Sono un ottimo punto di partenza se stai cercando di "tastare il
terreno" in questo progetto o nel contributo open source in generale.

Gli sviluppatori più esperti potrebbero preferire guardare l'elenco completo degli
issue del progetto, così come la [roadmap](https://github.com/goatshriek/stumpless/blob/latest/docs/roadmap.md). Se un elemento cattura il tuo interesse, lascia
un commento nell'issue esistente o aprine uno nuovo se non esiste ancora e dichiara
la tua intenzione di lavorarci, in modo che gli altri sappiano che è in fase di
sviluppo.


## Documentazione e Community
Se vuoi scoprire come funziona qualcosa in stumpless che non è stato spiegato
qui, puoi consultare la sezione appropriata della documentazione, che si trova
nella cartella [docs](https://github.com/goatshriek/stumpless/blob/latest/docs/).
Le cartelle nel repository contengono i propri file README che descrivono nel
dettaglio il loro contenuto e ogni altra informazione pertinente. La
documentazione per ogni funzione è ospitata anche sul [sito web del progetto](https://goatshriek.github.io/stumpless/),
sia per la libreria C che per i binding in altri linguaggi come C++.

Stumpless include la documentazione anche nelle installazioni locali sotto forma
di pagine `man`. Una volta installata la libreria, puoi consultare la
documentazione di qualsiasi file header (e delle funzioni che contiene) eseguendo
il comando `man` con il nome dell'header in cui i percorsi delle cartelle sono
sostituiti da trattini bassi (underscore); ad esempio, `man stumpless_log.h` per
visualizzare la documentazione delle funzioni che registrano semplici messaggi
testuali.

Esistono inoltre diversi modi per contattare il team del progetto e la comunità
più ampia per ricevere supporto:
 * Gli [Issue](https://github.com/goatshriek/stumpless/issues) e le [discussioni](https://github.com/goatshriek/stumpless/discussions)
 su GitHub sono ottimi modi per ottenere una risposta se hai una domanda
 specifica o un suggerimento.
 * È disponibile una chat persistente su [Gitter](https://gitter.im/stumpless/community)
dove puoi trovare annunci e fare domande.
 * Le novità sul progetto vengono solitamente annunciate anche su Twitter da [goatshriek](https://twitter.com/goatshriek),
usando l'hashtag [#StumplessLib](https://twitter.com/search?q=%23StumplessLib).
 * Puoi contattare il manutentore principale via [email](mailto:joel@goatshriek.com) se desideri una comunicazione privata. Questo è il
 metodo preferito per [segnalarci](https://github.com/goatshriek/stumpless/blob/latest/docs/SECURITY.md#reporting-a-vulnerability) problemi di sicurezza, in
 modo da poterli gestire il più rapidamente possibile per ridurre il rischio di
 abusi.
