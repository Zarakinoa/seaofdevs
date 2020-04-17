# Sea of Devs

## Objectif

Le projet consiste en l’implémentation d’une bataille navale. Un nombre donné de joueurs,
chacun représenté par un navire, doivent parcourir un océan à la recherche des autres pour
être le dernier survivant. La vie du navire est symbolisée par une valeur C appelée coque,
et son endurance par une valeur K appelée kerosene. Chaque action effectuée par le navire
aura une incidence sur sa coque et son kerosene. Si l’une de ces ressources vient à manquer,
le navire coule. Le jeu fonctionne en tour par tour : durant un tour, (1) chaque joueur dé-
termine la prochaine action à effectuer puis en informe le serveur ; (2) ce dernier effectue
les actions en fonction de différents critères (priorité par exemple) ; (3) puis il informe les
joueurs de leur nouvel état (nouvelles coordonnées, perte de points de coque ou de kerosene,
etc.). Le jeu se termine lorsqu’il ne reste plus qu’un seul survivant, ou si un nombre de tours
prédéfini a été atteint.

## Serveur et gestion de la partie

Dans cette première version, on a implémenté de manière simple le serveur de
jeu. Prenant en argument un fichier d’entrée, son rôle est de créer la carte navale fournie
dans le fichier d’entrée et d’effectuer un nombre donné de tours de jeu, constitué d’actions
pré-définies dans le programme.

## Joueur et algorithme de décision

Dans cette seconde version, on aimplémenté le côté joueur qui est un thread, ayant en charge un
navire

Le serveur et chaque joueur agi dans des threads distincts. A l’initialisation du
programme, une fois le fichier d’entrée lu, le processus principal générera n thread,
avec n le nombre de joueurs demandés.

A la réception de la mise à jour de son état par le serveur, le joueur détermine
l’action pour le prochain tour qu’il devra transmettre au serveur.

Le serveur, une fois toutes les actions recueillies, procède au déroulement du tour de jeu (valeurs C et K, position effective, cible touchée, etc.).