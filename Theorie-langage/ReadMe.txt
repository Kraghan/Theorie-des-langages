Merci d'utiliser le main fournit avec les sources pour tester le code.

Pour créer un automate, il faut le créer avec la fonction fa_create() (qui
se contente de réserver l'espace mémoire de l'automate) puis ajouter
manuellement les états un à un avec la fonction fa_add_state().

Attention ! Aucun état n'est ajouté par la suite. Si lors de la création, on
 demande à créer 5 états, on ne pourra pas en ajouter 6 avec fa_add_state().
 De plus, lors de la completion de l'automate, il est possible qu'un état
 soit ajouté, dans ce cas, il faut prévoir A L'AVANCE, lors de la création de
  l'automate l'espace pour cet état.