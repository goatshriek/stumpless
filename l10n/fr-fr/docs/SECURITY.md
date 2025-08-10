# Politique de sécurité Stumpless
Ce document décrit le support de sécurité pour Stumpless, y compris les versions qui seront corrigées et la procédure de signalement des vulnérabilités. Il inclut également des conseils pertinents pour l'utilisation sécurisée de la bibliothèque, et les pièges à éviter pour ne pas introduire de vulnérabilités dans le système.

## Versions supportées
Le tableau ci-dessous liste les versions actuellement supportées de Stumpless. En général, la version majeure courante et la précédente sont supportées à leur plus haut niveau mineur.

| Version | Supportée           |
| ------- | ------------------- |
| 2.2.x   | :heavy_check_mark:  |
| 2.1.x   | :x:                 |
| 2.0.x   | :x:                 |
| 1.6.x   | :heavy_check_mark:  |
| <= 1.5  | :x:                 |

## Signaler une vulnérabilité
Si vous découvrez un problème avec Stumpless, veuillez le signaler immédiatement au responsable du projet, [Joel Anderson](mailto:joel@goatshriek.com). Le problème sera examiné dès que possible et vous recevrez une réponse sous 14 jours.

Un correctif sera déployé sur toutes les versions supportées concernées en priorité. Cependant, il n'y a actuellement aucune garantie de délai pour le patch, le projet n'ayant pas de ressources dédiées.

Vous pouvez accélérer la réponse en incluant autant de détails que possible dans votre rapport. Les suggestions de correction sont également les bienvenues, mais nous vous demandons de limiter vos correctifs à la correspondance privée jusqu'à ce qu'un correctif soit déployé, afin de limiter le risque pour les utilisateurs de la bibliothèque.

## Utilisation sécurisée
Les aspects suivants doivent être soigneusement pris en compte par tout utilisateur de stumpless. Des erreurs dans ces domaines peuvent entraîner des vulnérabilités dans une application utilisant la bibliothèque.

### Comprendre les durées de vie `new` vs. `load`
Stumpless fournit plusieurs fonctions similaires mais avec des mécaniques différentes pour offrir aux utilisateurs le moyen le plus efficace d'accomplir ce dont ils ont besoin. Par exemple, dans certains cas, une structure comme une entrée de log ne sera nécessaire que dans une portée courte ou bien définie, et n'a donc pas besoin d'être allouée sur le tas. Les fonctions `load` permettent à l'appelant de fournir un pointeur vers une structure, évitant ainsi l'allocation sur le tas qui aurait lieu avec une fonction `new`.

Cependant, ce gain de performance comporte un risque. Les utilisateurs doivent s'assurer d'utiliser les fonctions `unload` correspondantes avec les structures initialisées de cette façon. En particulier, les destructeurs récursifs doivent être soigneusement appariés pour éviter, par exemple, d'appeler `stumpless_destroy_entry_and_contents` sur une entrée dont un paramètre a été créé avec `stumpless_load_param`.

Ne pas respecter ces règles peut entraîner des problèmes allant de fuites mémoire à des risques de sécurité graves comme le [double free](https://cwe.mitre.org/data/definitions/415.html) ou la [libération de mémoire non allouée sur le tas](https://cwe.mitre.org/data/definitions/590.html). La meilleure façon de s'en prémunir est de suivre une convention unique dans votre projet, et de s'y tenir. Évitez de mélanger les styles d'allocation sauf nécessité absolue.
