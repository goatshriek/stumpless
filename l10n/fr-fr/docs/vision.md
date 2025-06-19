# Rendre possible le debug all
C'est un objectif ambitieux. La pratique actuelle consiste à garder la journalisation à un niveau élevé et à n'activer le debug qu'en cas de besoin, et même alors seulement pour les composants problématiques. Et cela pour une bonne raison. Considérez le piège d'émettre la commande `debug all` sur un équipement réseau, pour que le processeur soit submergé et que la machine plante sous le déluge de messages. Les administrateurs vont parfois jusqu'à interdire spécifiquement cette commande pour éviter que des administrateurs juniors ne causent des dégâts involontaires.

Mais cela doit-il vraiment être ainsi ? La journalisation est souvent implémentée après coup, supposée être une charge minimale pour le système. Et quand ce n'est pas le cas, on se contente de limiter les messages enregistrés, risquant de manquer des informations précieuses et forçant des redémarrages d'applications juste pour ajuster les niveaux.

Le projet Stumpless vise à rendre la journalisation plus efficace et moins contraignante pour les développeurs. C'est l'objectif principal : une interface riche et intuitive, aussi discrète que possible tout en restant suffisamment flexible pour aller d'un simple « journaliser cette chaîne » à la journalisation de données structurées. Tout cela en conformité avec les standards existants, pour faciliter l'interopérabilité avec les outils de collecte et d'analyse existants.

L'efficacité et la performance sont aussi des piliers de la conception, afin que les instructions de journalisation fournissent autant d'informations de dépannage que possible. Exécution plus rapide, support multi-thread et multi-processus, et forte compression sont autant de tactiques utilisées pour minimiser la surcharge de la journalisation.

En offrant ces fonctions directement depuis la bibliothèque, stumpless permet aux applications de fusionner la génération et la transmission des logs dans l'application elle-même. Cela supprime le besoin d'un démon de journalisation séparé pour la même fonctionnalité, réduisant les points d'intégration et les interdépendances, pour un produit final plus robuste et efficace.


# Qu'est-ce qui rend ceci spécial ?
Il existe de nombreuses autres bibliothèques de journalisation pour C, avec diverses fonctionnalités comme le header-only, la sélection de cibles variées, et des options de données structurées. Stumpless vise à rassembler les fonctionnalités les plus utiles dans une seule bibliothèque performante, construite avec des pratiques modernes comme le développement piloté par les tests et l'intégration continue. Nous espérons créer une option viable pour les développeurs ayant besoin d'une bibliothèque de journalisation légère et standardisée.


# Ce que ceci n'est pas
Le seul problème que cette bibliothèque vise à résoudre est la création de messages de log et leur envoi. Il existe d'autres tâches liées à la journalisation qui sont importantes, mais ce projet ne les prend pas en charge. Notamment :


### Analyse de logs
L'analyse, l'indexation, le stockage et l'analyse des logs sont des tâches majeures qui disposent déjà de nombreuses solutions reconnues. Bien que stumpless soit conçu pour les compléter, il ne fournit aucune de leurs fonctionnalités. Vous devriez plutôt vous tourner vers des projets comme [Splunk](https://www.splunk.com/) ou [ELK stack](https://www.elastic.co/elk-stack) pour cela.


### Gestion des logs
Bien que stumpless puisse envoyer des logs de différentes manières, il ne gère pas nécessairement le transport de bout en bout ou le stockage final. Il existe de nombreuses solutions de collecte et de transfert de logs comme [rsyslog](https://www.rsyslog.com/), [syslog-ng](https://www.syslog-ng.com/), et [les forwarders Splunk](https://www.splunk.com/en_us/download/universal-forwarder.html). Si vous cherchez à gérer des fichiers de logs, par exemple pour recevoir et transférer des logs, vous devriez envisager d'utiliser ces outils.

Certaines fonctionnalités de stumpless peuvent recouper ces outils, comme la rotation des fichiers de logs. Si c'est tout ce dont vous avez besoin, tant mieux ! Mais veillez à reconnaître quand vous cherchez une fonctionnalité hors du champ de stumpless et à chercher ailleurs.
