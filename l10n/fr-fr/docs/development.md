# Développer Stumpless
Si vous souhaitez travailler sur la bibliothèque elle-même, voici quelques conseils utiles pour rendre l'expérience plus fluide et rapide.

## Pour commencer
Stumpless est configuré avec la plateforme de build populaire [CMake](https://cmake.org/). Pour le compiler depuis les sources, vous aurez besoin de cet outil ainsi que d'un système de build supporté. [GNU Make](https://www.gnu.org/software/make/) est l'un des plus connus, et de nombreux exemples en ligne l'utilisent. Si vous préférez autre chose, CMake supporte de nombreux autres systèmes de build. Par exemple, Visual Studio intègre le support CMake pour construire facilement des cibles dans l'IDE.

Le fichier `CMakeLists.txt` contient la spécification de build de stumpless, et mérite d'être consulté si vous êtes curieux de savoir où sont définis les checks de configuration, les fichiers source et test, et les autres cibles de build.

Il existe d'autres dépendances pour travailler sur stumpless, mais elles sont moins notables car vous n'aurez pas forcément à les manipuler. Par exemple, les bibliothèques Google Test et Benchmark sont nécessaires, mais elles sont téléchargées et compilées dynamiquement lors du build, donc pas besoin de s'en soucier. Ruby est aussi utilisé pour certains scripts de développement et de test, mais les builds et tests de base fonctionneront sans. Pour plus de détails sur les dépendances, consultez la [documentation des dépendances](dependencies.md).

Un workflow de développement typique implique une configuration et un build initiaux, suivis de l'exécution de la suite de tests après chaque modification. Cela pourrait ressembler à ceci :

```sh
# d'abord, la configuration initiale :

# cloner la dernière version du dépôt source
git clone git@github.com:goatshriek/stumpless.git

# créer un nouveau dossier de build
mkdir build
cd build

# configurer la nouvelle build
cmake ../stumpless

# après ces commandes initiales, un cycle de développement normal serait :

# modifiez quelques fichiers avec votre éditeur préféré - ici on utilise vim
vim ../stumpless/src/target.c

# build et exécution de la suite de tests
# ajoutez un argument parallel pour accélérer
# le nombre de cœurs de votre processeur est un bon point de départ
cmake --build . --parallel 4 --target check

# pour les systèmes multi-config comme Visual Studio, ajoutez aussi un argument de config
cmake --build . --parallel 4 --config x64-Debug --target check

# adaptez à votre environnement si besoin
```
