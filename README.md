# SystemProject
## Premier Shell

Pour commencer le Projet nous avons tout d'abords regardé des exemples de Shell postés sur différents forum. Nous avons donc compris le fonctionement du Shelle et les différents librairies appelés. Nous avons une boucle infini qui lit un texte en entrée, l'analyse et execute différentes opération en fonction du résultat.

La première étape fut donc un boucle while qui regarde si on ecrit ```exit``` et dans ce cas arrète la boucle, sinon execute la commande. Pour executer la commande nous créons un processus fils qui executeras la commande. Nous sommes obligé de forker le processus père et d'en creer un autre car quand la commande est executé elle détruit son processus.

La deuxième étape fut de rédiriger le working directory (wd) des processus avec la commande cd. La redirection doit se faire avant le fork car un processus ne peut modifier que son propre wd. Et non celui de son fils. Donc des que nous observons la mot ```cd``` en debut de commande nous entrons dans la phase de changement de wd et n'executerons pas la commande. Une fois le cahngement de répertoire effectuer lors de la prochaine execution de commande, le répertoire père et donc le fils aussi seront dans ke bon wd.

## Gestion des entrés/sorties

Dans cette partie nous nous sommes interessé au sorties et entrées des processus. Ces redirection ce faisait à l'aide de la fonction dup2(). Tout d'abords nous devions analyser dans l'entrée utilisateur si il désirait faire une redirection à l'aide des singes ```< >```. Si oui nous recuperions les information concernant cette redirection (l'endroit de la redirection et savoir si c'était une redirection des entrée ou sortie). Pour redireiger le flux vers un fichier il faut dans un premier temps ouvrir un flux vers le fichier avec open, puis dans un deuxième temps, indiquer à l'os la redirection à l'aide de dup2. Enfin après que le processus ai fini son execution il ne faut pas oublier de rediriger les flux vers ceux standar.

Interessons nous maintenant à la fonctionalité pipe : ``` | ```. Piper des commandes c'est enchainer plusieurs commande en donnant l'output de la commande n à l'input de la commande n+1. Pour cela nous avons du, dans une première étape 
