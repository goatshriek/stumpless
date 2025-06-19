# Sécurité des threads dans Stumpless
Depuis la version 2.0, stumpless est entièrement thread-safe. Toutes les fonctions fournies par la bibliothèque sont documentées avec leur niveau de sécurité en utilisant les attributs de sécurité décrits dans la norme POSIX et les fonctionnalités de sécurité conditionnelle décrites dans certains manuels GNU libc (voir la section pertinente [ici](https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html#POSIX-Safety-Concepts)).

En plus de la sécurité des threads, la sécurité asynchrone et la sécurité d'annulation asynchrone sont également documentées. Cependant, la plupart des fonctions ne sont pas sûres dans ces situations. Vous pouvez consulter la documentation de chaque fonction dans les fichiers d'en-tête publics pour voir comment cela est indiqué.

## Approche d'implémentation
Il existe plusieurs façons d'assurer la sécurité des threads, et stumpless utilise une combinaison de ces méthodes pour équilibrer performance et simplicité. Vous pouvez trouver les symboles pour travailler avec chacun de ces types dans le fichier d'en-tête `private/config/wrapper/thread_safety.h`.

### Mutex
La plupart des structures sont protégées par un mutex, utilisé pour coordonner les lectures et écritures sur tous les membres de la structure. Certaines cibles utilisent aussi un mutex séparé pour coordonner les écritures, comme les cibles fichier et flux. Ces verrous sont maintenus le moins longtemps possible. Essayez d'éviter de garder un mutex pendant des opérations coûteuses comme des allocations mémoire.

Les mutex sont définis par le type `config_mutex_t`, et il existe quatre fonctions pour les manipuler : `config_lock_mutex` et `config_unlock_mutex` pour acquérir et libérer le mutex, `config_init_mutex` pour l'initialiser, et `config_destroy_mutex` pour le nettoyer. Les fonctions d'init et de destruction _doivent_ être appelées au début et à la fin de la vie du mutex. Pour un bon exemple, consultez l'implémentation du cache slab dans `src/cache.c` et `include/private/cache.h`, qui utilise un mutex pour rendre chaque cache thread-safe.

### Stockage local au thread
Certaines structures n'ont pas besoin d'être disponibles pour tous les threads en permanence, et peuvent utiliser des mécanismes de sécurité plus efficaces. Les structures d'erreur par thread et la structure d'entrée mise en cache utilisée par les fonctions de log sur chaîne comme `stump` en sont de bons exemples. Elles sont placées dans un stockage local au thread, donc aucun verrou n'est nécessaire. Si vous pouvez utiliser cette stratégie, elle est moins sujette à la contention et sera plus rapide dans la plupart des cas.

Vous pouvez déclarer toute variable comme locale au thread en utilisant le modificateur `CONFIG_THREAD_LOCAL_STORAGE` dans sa définition. Après cela, la variable fonctionnera normalement sans autre travail spécial.

### Types atomiques
Les valeurs atomiques sont la dernière stratégie utilisée. Elles permettent d'avoir un champ qui peut être lu et écrit sans verrou pour synchroniser l'accès. Cette méthode peut être la plus performante, mais elle est aussi délicate à utiliser correctement. L'implémentation de `stumpless_get_default_target` en est un bon exemple, nécessitant plus de logique qu'une simple lecture/écriture pour éviter une fuite mémoire potentielle.

Les types atomiques sont définis pour chaque type nécessaire, et sont accompagnés de fonctions pour lire, écrire et faire une opération de comparaison et d'échange. Vous devrez aussi initialiser la variable à la définition, avec l'initialiseur approprié. Les variables de cible courante et par défaut dans `src/target.c` montrent comment créer et utiliser un type atomique.
