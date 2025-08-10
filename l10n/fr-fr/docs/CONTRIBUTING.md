## Aidez Stumpless à s'améliorer, à moins rater
Stumpless vise à bien faire une petite chose tout en restant aussi petit que possible. Si vous avez un problème avec le projet, une excellente idée de nouvelle fonctionnalité, ou que vous souhaitez simplement contribuer, consultez les directives ci-dessous pour savoir comment commencer. Veuillez également vous assurer de respecter le [Code de Conduite](CODE_OF_CONDUCT.md) quelle que soit votre participation.

### **Je sais ce que je fais**
Si vous êtes un utilisateur régulier de la bibliothèque et la connaissez bien, vous pouvez aider la communauté simplement en aidant d'autres personnes qui ont une question. Rendez-vous sur le [gitter du projet](https://gitter.im/stumpless/community) et si une question vous semble accessible, n'hésitez pas à intervenir !

### **Ça a cassé**
Si vous avez un problème avec le projet, assurez-vous d'avoir fait ce qui suit avant de soumettre une issue :

 * Consultez la documentation pour vérifier que le comportement n'est pas intentionnel
 * Cherchez dans les autres issues du projet pour vous assurer que ce problème n'est pas déjà signalé
 * Reproduisez le problème à partir de la branche de la dernière version

Si vous avez effectué toutes ces étapes et que le problème persiste, soumettez une issue sur le [projet GitHub](https://github.com/goatshriek/stumpless) en utilisant le modèle fourni et en remplissant toutes les informations.

Encore mieux : si vous savez comment corriger le problème, soumettez une pull request en utilisant le modèle fourni, en mentionnant le numéro de l'issue correspondante.

### **J'aide !**
Vous avez fait des modifications et souhaitez partager votre travail ? Super ! Soumettez une pull request et nous l'examinerons pour l'inclure dans la dernière version. Assurez-vous de suivre ces directives :
 * Si vous travaillez sur quelque chose de relativement petit, ne vous souciez pas du nombre de commits dans votre branche, ils seront "squashés" avant d'être fusionnés dans la branche `latest`. Si vous travaillez sur une "good first issue" par exemple, ne vous souciez pas de l'historique des commits et concentrez-vous sur l'essentiel ! Vous resterez l'auteur du commit, pour que la contribution soit reconnue dans l'historique et sur GitHub.
 * Si vous travaillez sur quelque chose de plus important, il n'est pas toujours pertinent de tout fusionner en un seul commit, et le nombre de commits devient alors plus important. Essayez de faire en sorte que chaque commit soit logique et apporte de la valeur à l'historique. Si vous avez besoin d'aide pour ajuster l'historique, consultez [ce chapitre](https://git-scm.com/book/en/v2/Git-Tools-Rewriting-History) du Git Book. Ce cas sera rare, demandez conseil si vous n'êtes pas sûr.
 * Si un commit résout ou est lié à une issue particulière, mentionnez-la dans le corps du commit.

### **Ce serait bien si...**
Si vous avez une nouvelle fonctionnalité à proposer, ouvrez une issue sur le projet github en utilisant le modèle "Feature Request". Si cela correspond au projet, vous pouvez commencer à travailler sur un fork et soumettre une pull request pour que nous puissions suivre l'avancement et l'intégrer une fois terminée. Sinon, nous l'ajouterons à la [feuille de route](../../../docs/roadmap.md) et l'implémenterons selon les priorités.

### **Ce que nous n'acceptons pas**
Nous apprécions toute personne souhaitant contribuer ! Cependant, nous devons aussi optimiser le temps passé à soutenir le projet et ses contributeurs. Pour cette raison, certains types de contributions ne seront pas acceptés. Merci de consulter cette liste et d'éviter ces types de pull requests :
 * Les corrections de fautes d'orthographe ou de grammaire évidentes peuvent être acceptées au cas par cas, selon la gravité du problème. Les changements de ce type ont plus de chances d'être acceptés s'ils concernent plusieurs documents. Si vous souhaitez contribuer en relisant, relisez plus d'un document !
 * Les changements de capitalisation, de ponctuation ou d'autres choix de style ne seront pas acceptés.

### **Je ne sais pas par où commencer**
Si vous souhaitez contribuer mais ne savez pas par où commencer, consultez les issues et voyez si quelque chose vous semble accessible ! En particulier, les labels 'help wanted' et 'good first issue' marquent respectivement les issues qui nécessitent de l'attention et celles qui sont relativement simples à corriger. Les issues 'good first issue' ne sont pas urgentes, donc pas de pression sur les délais, mais pensez à donner des nouvelles si cela prend du temps.

Les [notes de développement](development.md) contiennent une section pour les nouveaux contributeurs, à lire absolument.

#### Non, je veux dire que je **ne sais vraiment pas** par où commencer
Si vous êtes tout nouveau dans la communauté et cherchez plus de détails sur la contribution, cette section devrait vous aider.

Stumpless a une branche par défaut nommée `latest` sur laquelle toutes les nouvelles branches de fonctionnalités sont basées. Une fois tous les changements prévus pour la prochaine version implémentés, un tag sera ajouté pour le commit, nommé selon la version sémantique, et la branche `release` sera mise à jour pour pointer sur ce commit. Ainsi, `latest` a toujours les changements les plus récents et `release` pointe toujours sur la dernière version complète publiée.

Pour créer votre propre fonctionnalité ou mise à jour, forkez le dépôt et créez une nouvelle branche basée sur `latest`. N'oubliez pas de mettre à jour le ChangeLog avec vos modifications, et quand vous êtes prêt, ouvrez une pull request vers `latest`.

Il est rare, mais possible, qu'il soit préférable de baser votre travail sur la branche `release` plutôt que `latest`. C'est plus de travail, car il faudra fusionner les changements dans `latest` qui peut avoir divergé. Cela peut aussi nécessiter une nouvelle version patch. Ne faites cela que si c'est vraiment nécessaire, par exemple pour corriger une fonctionnalité cassée dans la dernière release ou pour des mises à jour critiques de documentation.

Vérifiez la [liste des dépendances](dependencies.md) pour vous assurer que votre environnement de développement dispose de tous les outils nécessaires. Plus précisément, assurez-vous de pouvoir exécuter les tests et outils de développement avant de faire des changements importants, pour pouvoir tester au fur et à mesure.

Un tutoriel détaillé sur le git flow traditionnel dépasse le cadre de cette documentation, mais ces guides sont de bons points de départ :
 * [GitHub Guides](https://guides.github.com/introduction/flow/)
 * [Créer une Pull Request depuis un fork](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork)

Pour résumer, forkez le dépôt, créez une branche basée sur `latest` (ou `release` si nécessaire), et quand vous avez fini, ouvrez une pull request vers le dépôt principal.

### Toujours là ?
L'équipe du projet vise à être aussi réactive que possible, en répondant généralement aux issues et pull requests en quelques jours. Il est courant de demander des clarifications ou des modifications, et souvent un échange est nécessaire avant qu'une contribution soit acceptée.

Malheureusement, il arrive que ces discussions s'enlisent. Dans ce cas, l'élément sera finalement fermé comme "stale". Les éléments sans réponse pendant deux mois seront marqués comme "stale" et un avertissement sera posté. Si un mois supplémentaire passe sans réponse, l'élément sera fermé.

Les éléments "stale" peuvent toujours être rouverts, donc la discussion n'est jamais définitivement close ! Nous voulons juste garder le travail actif bien visible pour tous.

## Note sur l'IA
Les contributions sont jugées principalement sur leur qualité. Vous pouvez utiliser les outils que vous souhaitez, y compris des IA génératives, à condition d'avoir suffisamment de droits sur le résultat pour le contribuer librement.

Cependant, si vous utilisez l'IA pour générer une pull request, une issue ou une réponse de discussion de faible qualité, elle sera traitée comme n'importe quel travail de faible qualité. Les mainteneurs pourront alors appliquer les [règles d'application](https://github.com/goatshriek/stumpless/blob/latest/docs/CODE_OF_CONDUCT.md#enforcement-guidelines) du Code de Conduite. Soyez respectueux du temps de chacun et relisez votre travail avant de le soumettre.

## Merci !
Et peu importe la façon dont vous contribuez, merci de faire vivre la communauté !

L'équipe Stumpless
