# SystemProject
## Premier Shell

Pour commencer le Projet nous avons tout d'abords regardé sir internet des exemples de Shell postés sur différents forum. Nous avons donc compris le fonctionement du Shell et les différentes librairies utilisées. Un shell c'est une boucle infini qui lit un texte en entrée, l'analyse et execute différentes opération en fonction du résultat.

La première étape fut de créer un boucle while qui regarde si on ecrit ```exit``` et dans ce cas arrète la boucle, sinon execute la commande. Pour executer la commande nous créons un processus fils qui executeras la commande. Nous sommes obligé de forker le processus père et d'en creer un autre car quand la commande est executé elle détruit son processus.

La deuxième étape fut de rédiriger la partie en charge de changer le working directory (wd) des processus à l'aide de la commande ```cd```. La redirection doit se faire avant le fork car un processus ne peut modifier que son propre wd. Et non celui de son fils.
Donc des que nous observons la mot clé ```cd``` en debut de commande nous entrons dans la phase de changement de wd et non dans la phase d'éxecution d'une commande. Une fois le cahngement de répertoire effectué, lors de la prochaine execution de commande, le répertoire père et donc le fils seront au bon endroit.

## Gestion des entrés/sorties

Dans cette partie nous nous sommes interessé aux sorties et entrées des processus. Ces redirection ce font à l'aide de la fonction ```dup2()```. Tout d'abords nous devons analyser l'entrée utilisateur pour savoir si il désire faire une redirection dans un fichier, à l'aide des singes ```< >```. Si oui nous recuperions les information concernant cette redirection (l'endroit de la redirection et savoir si c'était une redirection des entrée ou sortie). Pour redireiger le flux vers un fichier il faut dans un premier temps ouvrir un flux vers le fichier avec ```open()```, puis dans un deuxième temps, indiquer à l'os la redirection vers ce flux à l'aide de ```dup2()```. Enfin après que le processus ai fini son execution il ne faut pas oublier de rediriger les flux vers ceux standar.

Interessons nous maintenant à la fonctionalité pipe : ``` | ```. Piper des commandes c'est enchainer plusieurs commande en donnant l'output de la commande n à l'input de la commande n+1. Pour cela nous avons du séparer l'entrée utilisateurs en plusieurs commandes, celles ci séparés par des pipes.
Une fois les différentes commandes séparés, nous devons les executér une à une en redirigeant les sorties et entrés de manière appropriés.

Il est très dur de debugguer des redirections de sorties et entrés car lorsque nous changeons la sortie, les éléments ne s'affichent plus sur la console. Une autre difficulté auquel nous avons eu affaire dans cette partie était la fermeture des flux de communication. En effet si les flux étaient mals fermés, les processus enfants ne pouvais plus communiquer et le programme plantais.

## Rédaction des tests
Les tests du shell sont fait à la main. Pour cela nous regardons que les fonctionalités implémentés marchent et qu'elles donnent les résulats attendu (ceux du vrai shell)

Pour la première partie nous avons dans l'ordre testé : 
 - la commande exit en tapant exit
 - une commande qui n'existe par pour verifier que le terminal ne plante pas
 - une commande de base sans argument comme ls
 - une commande de base avec argument comme ls puis le nom d'un fichier

La commande cd :
 - nous avons tester la direction à partir de la branche actuelle (```cd nextDirectory```), le retour en arrière (```cd ..```), le retour à la racine (```cd /```). Pour verifier le bon fonctionement de ses commandes nous nous sommes fié aux fichiers présents sur l'ordinateur

La gestion des flux :
 - Nous avons testé la sortie en effectuant ```ls > out.txt```(ecrire les fichiers du wd dans le fihcier out.txt) et ```sort < input.txt``` (trie les différents éléments (une liste de mot) du fichier input.txt et les affiches dans le terminale). Nous avons aussi testé que l'entrée et la sortie pouvait être modifié en même temps à l'aide de la commande ```./addOne < input.txt > out.txt``` (nous avions mis dans input.txt un chiffre et nous devions retrouver dans out.txt ce chiffre plus un)

Les pipes :
 - Nous avons testé les pipes grace aux commande ```ls | sort -r | sort | wc``` et ses dérivés. Nous avons ensuite vérifié que nous obtenions bien les même résulats avec le terminale dans le même wd. Au début nous avions un pipe qui marchait avec 2 commande comme ```ls | sort``` mais qui arrétait de fonctionné. Nous avons testé qu'une unique fonction marchait et que toutes les fonctionalité précédentes fonctionnait toujours et nous avons testé ce porcessus jusqu'aux 10 commandes maximales. Chiffre que nous avons fixé arbitrairement(```ls | sort -r | sort | sort | sort | sort | sort | sort | sort | sort -r```). Bien sur au dela nous obtenons un message d'erreur. 
 





