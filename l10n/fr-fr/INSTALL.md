# Installation d'un paquet Stumpless
Si vous souhaitez simplement utiliser stumpless sans le modifier ou le développer, le moyen le plus simple est d'utiliser l'un des paquets de publication. Ceux-ci sont disponibles pour quelques plateformes courantes et sont joints à chaque [version](https://github.com/goatshriek/stumpless/releases) de stumpless. Si vous avez besoin d'un format de paquet qui n'est pas disponible ici, veuillez soumettre une issue avec votre demande et l'équipe projet verra si cela peut être ajouté.

Stumpless n'est actuellement enregistré dans aucun dépôt de paquets en ligne comme Chocolatey ou Debian. Si vous avez besoin de la bibliothèque dans un tel endroit, veuillez ouvrir une issue et l'équipe projet verra ce qu'elle peut faire.

Les paquets de publication fournis contiennent tous les éléments de la liste suivante. Si vous souhaitez un paquet avec seulement une sélection de ces éléments, vous devrez le construire vous-même avec `cpack` et la configuration appropriée.

 * bibliothèque partagée
 * fichiers d'en-tête
 * fichier `.pc` pour les implémentations `pkg-config`
 * exemples
 * documentation HTML
 * pages de manuel


## Paquet Debian
Un paquet `.deb` est fourni pour les environnements qui les supportent, comme Debian et Ubuntu. Le paquet peut être installé avec la commande habituelle :

```sh
# vous aurez peut-être besoin de sudo (ou des privilèges root) pour installer
dpkg -i libstumpless-2.2.0-amd64.deb
```


## Paquet RPM
Un paquet `.rpm` est fourni pour les environnements Red Hat Linux. Il peut également être installé de la manière traditionnelle :

```sh
# encore une fois, assurez-vous d'avoir les bonnes permissions
rpm -i libstumpless-2.2.0-x86_64.rpm
```


## Paquet FreeBSD
Un paquet `.pkg` est fourni pour les environnements FreeBSD. Bien sûr, il s'installe comme n'importe quel autre paquet pkg :

```sh
# les permissions doivent être correctes, bien sûr
pkg add libstumpless-2.2.0-amd64.pkg
```


## Gentoo ebuild
Un paquet `.ebuild` est fourni avec chaque version de la bibliothèque, et est également généré lors de la configuration du build par cmake. L'ebuild généré se trouve dans le dossier `tools/portage` du répertoire de build.

L'ebuild généré portera le nom de la version de stumpless que vous avez. Si vous voulez le dernier commit au lieu d'une version, vous devrez le renommer en `libstumpless-9999.ebuild` pour effectuer ce que Gentoo appelle un [live ebuild](https://wiki.gentoo.org/wiki/Ebuild#Live_ebuilds). Si vous avez un commit dans une version qui n'a pas encore été publiée et que vous ne renommez pas l'ebuild, alors le téléchargement de la source échouera.

Dans les deux cas, vous pouvez installer l'ebuild en le plaçant dans un dépôt et en exécutant ebuild comme ceci :

```sh
ebuild libstumpless-2.2.0.ebuild clean manifest install merge
```

Les USE flags et autres personnalisations peuvent également être faits ici. Les installations Gentoo sont plus nuancées que ce qui peut être discuté ici ; commencez par la [page du manuel](https://wiki.gentoo.org/wiki/Ebuild) si vous souhaitez en savoir plus.


## Installateur Shell Générique
CMake génère un script shell qui peut être utilisé pour installer la bibliothèque sur des systèmes dépourvus d'un gestionnaire de paquets traditionnel, par exemple Cygwin. Exécutez simplement le script depuis le préfixe où vous souhaitez installer la bibliothèque. Le script est une archive TGZ auto-extractible qui fournit les en-têtes et les fichiers de bibliothèque.

```sh
# vous devrez peut-être faire cela avec sudo !
# assurez-vous que vos permissions permettent d'écrire dans les emplacements d'installation
cd /usr
./libstumpless-2.2.0.sh
```


## Installateur Windows
Un simple installateur `.msi` est fourni qui place la DLL, le `.lib` et les en-têtes dans un dossier Program Files. Notez que vous devrez peut-être mettre à jour les chemins de recherche pour localiser ces ressources après l'installation, car l'installateur ne gère pas cela actuellement.


## Installateurs C++
Pour chaque paquet fourni, il existe également un paquet C++ (`stumpless-cpp`) qui inclut la bibliothèque C++. Ces paquets incluent aussi la bibliothèque C, donc si vous pensez avoir besoin de la bibliothèque C++ plus tard, vous pouvez utiliser celui-ci pour l'installer en même temps que la bibliothèque de base.


## Builds Fichier Unique
La cible de build `single-file` générera les fichiers `stumpless.c` et `include/single_file/stumpless.h` dans le répertoire de build, qui peuvent être utilisés comme des "dropins" fichier unique. Ceux-ci peuvent être compilés dans d'autres programmes pour fournir la fonctionnalité stumpless sans avoir besoin de liaison statique ou dynamique de la bibliothèque. L'en-tête unique peut être utilisé comme remplacement de l'installation de toute la hiérarchie d'en-têtes dont dépend l'installation typique.

Notez que ces fichiers ne contiendront que les fonctionnalités activées par la configuration qui les a générés. De plus, le temps nécessaire pour générer ces fichiers n'est pas négligeable, et les fichiers sont relativement volumineux et contiennent beaucoup de code dupliqué. Cette option est incluse pour fournir un moyen rapide et facile d'utiliser la bibliothèque en sacrifiant un peu d'efficacité.


# Compiler Stumpless depuis la source
Pour compiler Stumpless, vous aurez au minimum besoin de cmake et d'un système de build compatible comme la toolchain GNU ou Microsoft Visual Studio. Bien que la source puisse être téléchargée avec divers outils (wget, un navigateur, etc.), git est recommandé si vous souhaitez obtenir des tags de version spécifiques, des branches, ou apporter des modifications vous-même.


## Préparer votre système
Comme il existe de nombreuses façons de configurer un environnement, stumpless ne fournit pas de méthode unique pour cela. Voici cependant quelques extraits qui peuvent tout installer pour vous dans des environnements courants.

Notez que certaines dépendances pour le développement de Stumpless sont omises ici, notamment Git, Ruby et Valgrind. Pour une liste complète des dépendances, consultez la [documentation des dépendances](../docs/dependencies.md), qui liste tous les outils dont vous pourriez avoir besoin. Les extraits ci-dessous permettent de construire et tester la bibliothèque, ainsi que de générer la documentation.

De même, si vous souhaitez seulement compiler la bibliothèque, vous n'aurez peut-être pas besoin de tout cela. Un compilateur C++ n'est nécessaire que pour construire les suites de tests, et doxygen uniquement si vous générez la documentation. Si vous souhaitez simplement compiler la bibliothèque et l'utiliser/installer immédiatement, vous n'aurez besoin que de cmake et d'une toolchain C.

Pour les systèmes Linux avec un gestionnaire de paquets comme `apt`, vous pouvez installer les outils nécessaires (pour une toolchain GNU) avec quelque chose comme :

```sh
# pour les distributions utilisant apt, comme Ubuntu ou Debian :
sudo apt-get install cmake make gcc g++ doxygen

# pour les distributions utilisant pacman comme Arch Linux ou MSYS2 :
pacman -S cmake make gcc doxygen

# Pour MinGW, assurez-vous d'utiliser les paquets MinGW, comme dans l'appel pacman suivant. Assurez-vous d'être dans un shell MinGW pour compiler de cette façon. Par exemple, MSYS2 fournit des terminaux MinGW.
pacman -S $MINGW_PACKAGE_PREFIX-cmake \
          $MINGW_PACKAGE_PREFIX-make \
          $MINGW_PACKAGE_PREFIX-gcc \
          $MINGW_PACKAGE_PREFIX-doxygen
```

Cygwin n'a pas de gestionnaire de paquets dans l'environnement lui-même, nécessitant l'installation des paquets via le script setup. Vous pouvez installer les paquets nécessaires dans l'interface graphique, ou si vous souhaitez le faire en ligne de commande :

```sh
setup-x86_64.exe -q -P cmake,make,gcc-core,gcc-g++,doxygen
```


## Compilation
Une fois toutes les dépendances de build disponibles, la compilation de la bibliothèque est simple. Les exemples ci-dessous montrent comment faire cela dans un environnement utilisant `make` à partir d'un clone frais.

```sh
# cloner la dernière version du dépôt source
# si vous ne souhaitez pas utiliser git, vous pouvez télécharger une archive zip des sources depuis github
git clone git@github.com:goatshriek/stumpless.git

# créer un nouveau dossier de compilation
mkdir build
cd build

# configurer la nouvelle compilation
cmake ../stumpless

# compiler la bibliothèque elle-même
cmake --build .
```

D'autres environnements doivent être compilés selon leur style habituel. Par exemple, Visual Studio fournit un menu CMake dans l'IDE qui affiche toutes les cibles disponibles.

CMake utilisera la toolchain de build qu'il juge la meilleure, mais sur les systèmes avec plusieurs toolchains disponibles, vous voudrez peut-être la forcer. Par exemple, les systèmes MinGW peuvent par défaut utiliser Ninja au lieu de la toolchain MinGW. Dans ces situations, vous voudrez probablement spécifier un [générateur](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) lors de la configuration. Toujours avec MinGW, cela pourrait ressembler à :

```sh
# à exécuter dans le shell MinGW, dans notre dossier de build frais
cmake -G "MinGW Makefiles" ../stumpless
```

Si vous n'êtes pas sûr des commandes de build pour la toolchain de votre système, cmake peut les exécuter pour vous si vous l'appelez en [mode build](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project). C'est particulièrement pratique dans des environnements comme Visual Studio ou MinGW, où la toolchain de build peut nécessiter des préfixes et/ou des options spécifiques.

```sh
# compiler la cible par défaut ("all") avec la toolchain détectée par cmake lors de la configuration
# l'argument du paramètre `--build` est la racine du dossier où nous avons lancé la configuration cmake
cmake --build .

# on peut compiler et exécuter toute autre cible avec l'option `--target`
# par exemple, cette commande compile et exécute la suite de tests
cmake --build . --target check
```

Le type de build peut être changé lors de la configuration en définissant le symbole `CMAKE_BUILD_TYPE`.

```sh
# les tests de benchmark doivent toujours être faits avec des builds Release
cmake -DCMAKE_BUILD_TYPE=Release ../stumpless
```

Cependant, certains environnements (Visual Studio notamment) nécessitent que la configuration soit passée lors des étapes de build. Dans l'exemple ci-dessus, les builds utiliseraient toujours le type de build par défaut, ignorant effectivement l'étape de configuration. Pour spécifier le type de build, vous devrez fournir une config lors du build :

```sh
# utiliser explicitement la configuration Release dans notre toolchain
cmake --build . --config x64-Release --target bench
```

Dans ces systèmes, il est plus simple d'utiliser un IDE qui gère cela pour vous, comme Visual Studio. Pour plus d'informations sur ces sujets, consultez la documentation CMake sur le [mode build](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project) et les [générateurs multi-config](https://cmake.org/cmake/help/latest/prop_gbl/GENERATOR_IS_MULTI_CONFIG.html).

Le reste de cette documentation utilise les commandes make pour la simplicité, mais pour toute cible vous pouvez la compiler avec cmake en mode build si vous souhaitez une invocation de ligne de commande vraiment portable.


## Générer la documentation
La documentation de la bibliothèque peut être générée avec la cible `docs`. Notez que cette cible ne sera disponible que si doxygen a été détecté lors de la configuration du système.

```sh
# la documentation générée apparaîtra dans un dossier nommé docs dans le dossier de build
cmake --build . --target docs
```


## Vérifier votre compilation
Si vous souhaitez exécuter la suite de tests sur la bibliothèque pendant le développement ou comme vérification avant l'installation, vous pouvez utiliser la cible `check` pour lancer tous les tests et afficher les résultats. Si vous craignez que la compilation ne fonctionne pas sur votre architecture, c'est le meilleur moyen de vérifier.

```sh
cmake --build . --target check
```

La cible `check` téléchargera et compilera la bibliothèque Google Test dans le dossier de build pour exécuter les tests lors de la première invocation.

Si vous êtes curieux de voir comment la bibliothèque se comporte sur votre système, utilisez la cible `bench` pour lancer les benchmarks de performance. Comme la cible `check`, cela téléchargera et compilera la bibliothèque Google Benchmark pour l'exécution.

```sh
cmake --build . --target bench
```


## Installer votre compilation
Vous pouvez utiliser la cible install pour installer la bibliothèque sur votre machine après la compilation. Cet exemple utilise la commande cmake `--install`, mais vous pouvez aussi utiliser la cible de build `install` pour votre système de build spécifique, par exemple `make install` dans un build GNU make.

```sh
cmake --install .

# si la commande ci-dessus ne fonctionne pas, vous aurez peut-être besoin de sudo pour installer les fichiers dans les bons dossiers système
sudo cmake --install .
```

Un moyen simple de vérifier que votre installation fonctionne comme prévu est de compiler l'un des exemples sans utiliser les cibles intégrées. Si la cible se compile mais que votre propre compilation échoue, alors il y a un problème avec votre installation.

```sh
# d'abord, on utilise la cible de build pour s'assurer que ça fonctionne
cmake --build . --target run-example-entry

# ensuite, on compile le même exemple manuellement
gcc docs/examples/entry/entry_example.c -lstumpless -omanual_entry_example
# cela devrait fonctionner si tout est correct
./manual_entry_example
```

Si vous rencontrez des problèmes, il y a quelques points simples à vérifier. Un problème courant est que la bibliothèque installée n'est pas dans le chemin de recherche des bibliothèques du système, ce qui conduit généralement à une erreur du type `cannot find -lstumpless` ou similaire. Si vous voyez cela, vérifiez le chemin de recherche actuel et, si besoin, définissez les variables d'environnement appropriées ou ajoutez des options de compilation pour inclure l'emplacement où stumpless a été installé. Quelques exemples sont l'option `-L` de gcc, la variable d'environnement `LD_LIBRARY_PATH` sur de nombreux systèmes Linux, et la variable `LIBRARY_PATH` sous Cygwin.

Si vous constatez que stumpless s'est installé à des emplacements inattendus et que vous souhaitez modifier cela, utilisez la définition `CMAKE_INSTALL_PREFIX` lors de l'étape de configuration du build. Vous pouvez toujours relancer cmake pour mettre à jour cela dans un arbre de build existant, ou fournir l'option `--prefix` à `cmake --install` pour le changer lors de l'installation.

```sh
# notre build initial a installé dans /usr/local, ce que nous ne voulions pas
cat install_manifest.txt
# /usr/local/include/stumpless/target/network.h
# /usr/local/include/stumpless/target/socket.h
# /usr/local/lib/libstumpless.so.2.0.0
# /usr/local/lib/libstumpless.so
# /usr/local/include/stumpless.h
# <sortie tronquée>

# refaire l'installation avec un autre préfixe
sudo cmake --install . --prefix /usr

# maintenant, les fichiers sont au bon endroit !
cat install_manifest.txt
# /usr/include/stumpless/target/network.h
# /usr/include/stumpless/target/socket.h
# /usr/lib/libstumpless.so.2.0.0
# /usr/lib/libstumpless.so
# /usr/include/stumpless.h
# /usr/include/stumpless/config.h
# <sortie tronquée>
```

Certains outils, comme Visual Studio, exécuteront l'étape d'installation pour vous. Dans Visual Studio 2022 par exemple, cela se trouve dans le menu `Build->Install stumpless`.


### Désinstallation
Il n'existe actuellement aucune cible de désinstallation, donc la suppression de la bibliothèque et de ses fichiers d'en-tête doit être faite manuellement si elle n'est plus nécessaire. Veuillez soumettre une issue sur le Github du projet si vous pensez avoir besoin d'une cible de build fournissant cette fonctionnalité. Si vous êtes sur un système Linux, vous pouvez exécuter le contenu du fichier `install_manifest.txt` (généré lors de l'installation) avec `rm` comme ceci :

```sh
xargs rm < install_manifest.txt
```


## Bibliothèque C++
Si vous souhaitez compiler, tester et installer les bindings C++ pour stumpless, vous devrez légèrement modifier les étapes ci-dessus.

Comme prérequis, vous devrez également vous assurer que le gem Wrapture est installé pour que cela fonctionne. Cela peut se faire avec un simple `gem install wrapture`, ou vous pouvez utiliser le `Gemfile` inclus dans stumpless et simplement faire un `bundle install` pour l'installer.

Si vous avez besoin d'un environnement ruby, nous recommandons d'utiliser `rvm` pour gérer les versions et les gemsets. Vous trouverez plus d'informations sur rvm sur le [site du projet](https://rvm.io/). D'autres options sont `rbenv`, la distribution ruby de votre gestionnaire de paquets, ou RubyInstaller (pour Windows).

Après avoir un environnement ruby et wrapture disponible, la compilation et les tests de la bibliothèque C++ peuvent se faire ainsi :

```sh
# dans le dossier de build, modifiez la configuration cmake pour activer c++
# cela affichera un avertissement et laissera c++ désactivé si wrapture ne peut pas être trouvé
cmake -DBUILD_CPP=ON ../stumpless

# la cible par défaut inclura maintenant la bibliothèque stumpless c++
cmake --build .

# pour tester la bibliothèque, utilisez la cible `check-cpp`
cmake --build . --target check-cpp

# quand activés, les bindings C++ sont installés avec la bibliothèque elle-même
# donc la commande suivante installera aussi les en-têtes et la bibliothèque c++
cmake --install .
```
