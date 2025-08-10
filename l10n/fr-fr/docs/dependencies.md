## Environnement de compilation
Pour compiler la bibliothèque, une suite standard d'outils de build doit être disponible. Ces outils sont classiques pour les projets C et sont listés ci-dessous :
 * `cmake` pour la gestion des cibles et l'orchestration
 * une chaîne d'outils utilisable par cmake (gcc, par exemple)

Si vous souhaitez compiler les liaisons C++ du projet, vous aurez besoin de `wrapture`. Il est disponible sur rubygems.org en tant que gem. Vous pouvez aussi utiliser bundler pour l'installer avec le Gemfile du projet (`bundle install`), mais notez que cela est destiné au développement et peut installer d'autres gems inutiles si vous voulez juste compiler et installer la bibliothèque.

## Tests
La suite de tests du projet est écrite avec Google Test. Elle sera trouvée et/ou téléchargée et compilée automatiquement si les tests sont activés (c'est le cas par défaut).

Plus d'informations sur Google Test sont disponibles sur la [page Github du projet](https://github.com/google/googletest).

Si vous souhaitez tester les wrappers générés pour d'autres langages que C, vous devrez avoir l'environnement du langage installé pour exécuter les tests.

La suite de tests de performance utilise Google Benchmark. Comme pour Google Test, elle sera trouvée et/ou téléchargée et compilée automatiquement si le benchmarking est activé.

Plus d'informations sur Google Benchmark sont disponibles sur la [page Github du projet](https://github.com/google/benchmark).

Valgrind est utilisé pour vérifier les fuites mémoire et effectuer d'autres tests de robustesse. Ces tests sont lancés dans l'intégration continue pour le build Linux debug, mais peuvent aussi être lancés manuellement.

Plus d'informations sur Valgrind sont disponibles sur la [page d'accueil du projet](https://valgrind.org/).

## Documentation
La documentation générale du comportement des fonctions est incluse sous forme de commentaires dans les fichiers d'en-tête publics. La documentation peut aussi être générée avec `doxygen`. Cela se fait avec la cible de build `docs`, disponible uniquement si doxygen est détecté sur le système de build.

Si vous souhaitez seulement consulter la documentation, vous pouvez éviter de télécharger le dépôt et de le compiler en visitant le [site du projet](https://goatshriek.github.io/stumpless/), qui propose la documentation C et C++ de la dernière version.

## Développement
Si vous souhaitez développer dans le projet stumpless lui-même, il vous faudra quelques outils supplémentaires :
 * `ruby` pour certains scripts de développement. Si vous avez bundler, vous pouvez utiliser le Gemfile (exécutez `bundle install` à la racine du projet) pour installer tous les gems nécessaires d'un coup.

## Simplified Wrapper Interface Generator (SWIG)
Le projet SWIG est utilisé pour exposer les fonctionnalités de Stumpless à d'autres langages que le C. L'exécutable `swig` doit être disponible pour compiler tout support de langage supplémentaire (par exemple, Python). SWIG n'est pas requis pour la compilation de la bibliothèque de base, donc si vous n'avez pas besoin de support pour d'autres langages, il n'est pas nécessaire de l'installer.

Plus d'informations sur SWIG sont disponibles sur la [page Github du projet](https://github.com/swig/swig).
