# Portabilité dans Stumpless
Stumpless est conçu pour être compact et efficace, ce qui en fait une excellente option pour les scénarios embarqués. Cela signifie que la portabilité est un facteur clé de la conception : pour fonctionner dans des environnements contraints, il doit pouvoir gérer une variété de situations qui ne se présentent pas dans les environnements de bureau ou de serveur standards.

Stumpless suit quelques principes de conception clés afin d'être riche en fonctionnalités et facile à maintenir tout en restant aussi portable que possible :
 * **Aucune directive `#ifdef` n'est autorisée dans les fichiers source (`.c`).**
   Le code source avec des directives du préprocesseur qui ajoutent, modifient ou suppriment des fonctionnalités est facile à ajouter, mais disperse le comportement spécifique à la configuration et les dépendances de l'environnement de build dans les fichiers source, rendant le flux du programme plus difficile à comprendre. Ces extraits doivent plutôt être regroupés dans des modules de configuration séparés qui gardent le code de portabilité à l'écart des autres logiques et faciles à trouver, comprendre et modifier.
 * **Avoir un comportement par défaut pour gérer les dépendances manquantes.**
   Cela ne signifie pas qu'il faut réimplémenter d'autres bibliothèques, mais il faut fournir un comportement de repli raisonnable qui fonctionnera en leur absence. Cela peut être aussi simple que de lever une erreur de cible non supportée ou de remplir une valeur inconnue avec une supposition raisonnable.

# Conventions
Stumpless a des conventions pour gérer les dépendances de manière portable, qui peuvent être utilisées chaque fois qu'un comportement spécifique à la configuration est nécessaire. Cela repose sur la famille d'en-têtes, de sources et de symboles `config`.

## En-têtes de configuration et wrappers
Un grand soin est apporté pour séparer les impacts de la configuration des autres fonctionnalités de la bibliothèque. Il y a deux en-têtes où se trouvent les informations sur la build : l'un pour les informations qui décrivent les fonctionnalités et autres variables qui affectent la fonctionnalité, et un autre pour les facteurs qui n'affectent que le code interne.

L'en-tête `stumpless/config.h` est installé avec la bibliothèque et peut être référencé depuis le code qui l'inclut ou inclut `stumpless.h`. Par exemple, la version de stumpless se trouve dans cet en-tête, `STUMPLESS_VERSION` pour une chaîne littérale et `STUMPLESS_MAJOR_VERSION`, `STUMPLESS_MINOR_VERSION` et `STUMPLESS_PATCH_VERSION` avec des valeurs entières pour chaque partie. La prise en charge de certains types de cibles est également disponible, par exemple si le symbole `STUMPLESS_SOCKET_TARGETS_SUPPORTED` est défini, alors les sockets Unix sont disponibles dans cette build. Une liste complète des symboles de cet en-tête se trouve dans la [documentation](https://goatshriek.github.io/stumpless/docs/c/latest/).

Cependant, cet en-tête n'inclut pas les informations nécessaires pour prendre certaines décisions internes. Par exemple, l'en-tête public n'indiquera pas si un en-tête particulier était disponible lors de la build du système. Pour ce type d'information, il existe un second fichier de configuration, `private/config.h`, qui donne des détails sur les en-têtes et symboles disponibles dans l'environnement de build. Un cas typique est le symbole `HAVE_WINSOCK2_H`, défini lorsque le système de build dispose de `winsock2.h`.

Ces deux en-têtes peuvent être utilisés chaque fois que ces informations sont nécessaires dans le code source de Stumpless lui-même. Mais, pour respecter le premier principe ci-dessus, ils ne sont utilisés que dans les fichiers d'en-tête pour définir conditionnellement d'autres symboles qui peuvent ensuite être référencés dans le code source sans avoir à se soucier des symboles `#ifdef` ou d'autres directives du préprocesseur. Il existe d'ailleurs une autre convention établie pour cela : les en-têtes wrappers et la famille de fonctions `config`.

## L'en-tête Wrapper et les fonctions `config`
Un en-tête en particulier dans la liste des includes privés mérite une mention spéciale : `private/config/wrapper.h`. Ce fichier contient des définitions de nombreuses fonctions et symboles commençant tous par `config_` qui encapsulent des fonctionnalités spécifiques à la configuration. Cet en-tête est alors tout ce dont le code de la bibliothèque a besoin pour utiliser cette fonctionnalité, sans avoir à vérifier toutes les combinaisons de configuration possibles.

Ceci est plus facile à comprendre avec un exemple. Regardons le code utilisé pour déterminer s'il faut utiliser la version "sûre" de Microsoft de l'appel de bibliothèque `fopen`, ou simplement l'appel `fopen` standard fourni par les systèmes Linux. L'extrait de l'en-tête wrapper qui gère cela ressemble à ceci :

```c
#ifdef HAVE_FOPEN_S
#  include "private/config/have_fopen_s.h"
#  define config_fopen fopen_s_fopen
#else
#  include <stdio.h>
#  define config_fopen fopen
#endif
```

Le symbole `HAVE_FOPEN_S` est défini dans l'en-tête `private/config.h`, et est défini sur les systèmes où le symbole est détecté lors de l'exécution de CMake. Si le symbole est trouvé, l'en-tête de configuration avec la déclaration de la fonction qui utilisera la fonction `fopen_s` est inclus, et `config_fopen` est défini comme un alias pour cette fonction. Sinon, `config_fopen` est simplement défini comme un alias pour l'appel de bibliothèque `fopen`. Tout code de la bibliothèque qui a besoin de la fonctionnalité `fopen` utilisera alors simplement `config_fopen` sans avoir à savoir quel appel sous-jacent est fourni.

Les fichiers d'en-tête et les fonctions suivent une convention de nommage pour indiquer clairement à quel élément de configuration ils se rapportent.

 * `have_xxx_.h` désigne que l'en-tête ou la fonction nommée `xxx` est supposée présente dans le code à l'intérieur. Les fonctions dans ces en-têtes commencent toujours par un préfixe `xxx_` où xxx est le nom de l'en-tête ou de la fonction utilisée.
 * Les en-têtes de la forme `no_xxx.h` sont l'opposé du cas précédent : ils supposent que l'en-tête ou la fonction n'est _pas_ disponible. Ces fonctions sont nommées avec un préfixe `no_xxx_`, encore une fois où xxx est le nom du symbole disponible.
 * Les en-têtes `xxx_supported.h` contiennent du code qui suppose qu'il y a un support de la plateforme et/ou de la bibliothèque pour une fonctionnalité donnée. Par exemple, les sockets abstraits ne peuvent être utilisés que sur les systèmes Linux. Un autre cas concerne les cibles réseau, qui peuvent être désactivées dans certaines builds. Les fonctions dans ces en-têtes commencent par un préfixe `xxx_` avec xxx remplacé par le nom de la fonctionnalité. Notez que parfois ce préfixe est le nom complet de la fonction (sans le _ à la fin), si la fonctionnalité supportée est la fonction elle-même.
 * Logiquement, les en-têtes `xxx_unsupported.h` contiennent du code pour gérer le cas où une fonctionnalité n'est pas disponible. Les fonctions dans ces en-têtes commencent par le préfixe `no_xxx_` avec xxx rempli par le nom de la fonctionnalité.

Pour toutes ces fonctions, le préfixe désigné est remplacé par `config_` par le wrapper qui désigne celle choisie. Les fonctions qui n'ont pas ou n'ont pas besoin d'une fonction wrapper `config_` ne suivent pas nécessairement cette convention de nommage. Les fonctions publiques entrent dans cette catégorie, car elles commencent par un préfixe `stumpless_` pour se conformer à la norme générale de la bibliothèque, et ne sont pas encapsulées par un en-tête de configuration.

Le fichier d'en-tête et les fichiers source de configuration ne résident pas nécessairement dans le répertoire config s'il existe un meilleur emplacement. L'exemple le plus marquant concerne les types de cibles qui peuvent ne pas être disponibles dans une configuration donnée. Ces fichiers source existent dans le répertoire target avec les autres fichiers liés aux cibles plutôt que dans le répertoire config.

## Autres en-têtes wrappers
Il existe d'autres en-têtes wrappers qui masquent les détails liés à la configuration au-delà de `private/config/wrapper.h`. Le plus important est `private/config/wrapper/locale.h` qui inclut le bon ensemble de définitions de chaînes localisées en fonction de la locale choisie lors de la configuration de la build. Un autre exemple est `private/windows_wrapper.h` qui inclut les fichiers d'en-tête liés à Windows uniquement s'ils sont trouvés et dans le bon ordre.

## Comportement de repli
Stumpless est conçu pour fonctionner dans une variété d'environnements, et peut généralement trouver un moyen d'accomplir ce dont il a besoin s'il y a une possibilité. Cependant, dans certains environnements, les capacités nécessaires sont tout simplement absentes, et la bibliothèque doit échouer de la manière la plus conviviale possible.

Dans ces scénarios, la famille de fonctions de configuration `fallback` entre en jeu. Elles doivent être définies chaque fois qu'il est possible qu'une option de configuration ne soit pas disponible, mais que stumpless doit quand même fonctionner. Cela garde le comportement spécifique à la configuration dans des emplacements faciles à trouver au lieu d'exiger que le code de la bibliothèque indépendante de la plateforme implémente son propre code de repli.

Un bon exemple de cette convention se trouve dans l'appel pour obtenir la taille de page mémoire du système, utilisée pour rendre les caches slab de certaines structures de données internes plus efficaces. Cet appel est défini dans l'en-tête wrapper comme décrit ci-dessus, comme ceci :

```c
#ifdef HAVE_UNISTD_H
#  include "private/config/have_unistd.h"
#  define config_getpagesize unistd_getpagesize
#elif HAVE_WINDOWS_H
#  include "private/config/have_windows.h"
#  define config_getpagesize windows_getpagesize
#else
#  include "private/config/fallback.h"
#  define config_getpagesize fallback_getpagesize
#endif
```

La plupart des systèmes auront soit `unistd.h` soit `windows.h` disponible, donc la fonction de repli ne sera généralement pas nécessaire. Cependant, il est possible qu'aucun des deux ne soit disponible, comme cela a été observé sur certaines builds Cygwin (voir l'issue Github [#60](https://github.com/goatshriek/stumpless/issues/60) pour plus d'infos). Pour ces cas, la fonction de repli est utilisée, qui a une implémentation simple et indépendante de la configuration :

```c
size_t
fallback_getpagesize( void ) {
  return 4096;
}
```

Les fonctions de repli doivent être totalement indépendantes de toute hypothèse basée sur la configuration, et doivent avoir du sens dans le contexte où elles sont utilisées. Cet exemple utilise une taille de page mémoire de repli de 4 Ko, une taille courante et une supposition raisonnable.

Les fonctions de repli peuvent lever des erreurs si aucun comportement "par défaut" naturel n'existe, mais cela ne doit être fait que dans les cas où les autres options de configuration pourraient aussi lever des erreurs. Une gestion d'erreur supplémentaire ne doit pas être introduite uniquement pour éviter du travail supplémentaire dans l'option de repli.
