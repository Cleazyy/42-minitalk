# minitalk
Minitalk est un projet à réaliser dans le cursus de 42.

## But du projet :
Réaliser un programme de communication permettant de passer une chaine de caractères d’un client vers un serveur à l'aide des signaux SIGUSR1 et SIGUSR2.

### Signaux UNIX :
Un signal est une forme limitée de communication entre processus utilisée par les systèmes de type Unix.  
Il s'agit d'une notification asynchrone envoyée à un processus pour lui signaler l'apparition d'un événement.  
Ces derniers permettent à des processus différents de communiquer entre eux.  

> SIGUSR1 et SIGUSR2 sont deux signaux qui peuvent être utilisés par des processus sans conditions particulières. 
> Par défaut, la réception d'un tel signal provoque la terminaison du processus.

### PID (Process ID) :
Un PID (Process ID) est un numéro unique attribué par le système d'exploitation à chaque processus en cours d'exécution.

> Nous pouvons obtenir le PID d'un processus en utilisant la fonction getpid de la bibliothèque unistd.h.  
```c
#include <unistd.h>
#include <stdio.h>

int main(void) 
{
    pid_t pid = getpid();
    printf("Le PID du processus est %d\n", pid);
    return (0);
}
```

### int kill(pid_t pid, int sig) :
La fonction kill est une fonction du système Unix qui permet d'envoyer un signal à un processus en cours d'exécution.  
Elle est définie dans la bibliothèque signal.h et est utilisée de la manière suivante :
```c
int main(void)
{
    kill(pid, SIGUSR1);
    return (0);
}
```
Le premier argument de la fonction kill est le PID (Process ID) du processus à qui le signal doit être envoyé.  
Le second argument est le numéro du signal à envoyer.

### void (*signal(int sig, void (*func)(int)))(int) :
La fonction signal est une fonction du système Unix qui permet de définir l'action à effectuer lorsqu'un signal est reçu par un processus.  
Elle est définie dans la bibliothèque signal.h et est utilisée de la manière suivante :
```c
void my_handler(int signum) 
{
    if (signum == SIGUSR1)
        printf("Received SIGUSR1!\n");
}

int main(void)
{
    signal(SIGUSR1, my_handler);
    return (0);
}
```
Le premier argument de la fonction signal est le numéro du signal pour lequel l'action doit être définie.  
Le second argument est un pointeur vers une fonction qui sera exécutée lorsque le signal est reçu. 

### int usleep(useconds_t usec) :
La fonction usleep est une fonction de la bibliothèque C standard qui permet de suspendre l'exécution d'un programme pendant un certain nombre de microsecondes.  

On pourra donc l'utiliser coté client pour mettre en pause le programme quelques microsecondes entre chaque signaux envoyés avec la fonction kill afin d'éviter que les signaux ne s'envoient trop rapidement et que le serveur n'ait pas le temps de les gérer.

### int pause(void) :
La fonction pause est définie dans la bibliothèque unistd.h et est utilisée pour mettre en pause l'exécution du programme jusqu'à ce qu'un signal soit reçu.

Etant donné que par défaut la réception des signaux SIGUSR1 et SIGUSR2 provoque la terminaison du processus, on va pouvoir utilser cette fonction coté serveur pour boucler infiniment les signaux et mettre en pause le système en attendant la réception d'un nouveau signal.

### Binaire :
Les signaux SIGUSR1 et SIGUSR2 ne renvoient pas valeur en tant que tel, on va donc convertir chaque caractère ascii en binaire en utilisant le signal SIGUSR1 et SIGUSR2 pour indiquer les 1 et les 0 au serveur qui va reconvertir le binaire reçu en caractère ascii pour l'afficher.

Voici un exemple de fonction qui affiche un caractère ascii en binaire :
```c
void convert_char_to_binary(char c) 
{
    int    i;

    i = 7;
    while (i >= 0)
    {
        if (c & (1 << i))
            write(1, "1", 1);
        else
            write(1, "0", 1);
        i--;
    }
    write(1, "\n", 1);
}
```
Pour ce faire il faut donc comprendre les opérateurs bitwise pour faire de la manipulation de bits.
|Opérateur|Nom|Description|
|---------|---|-----------|
|&|ET binaire (AND)|Renvoie un 1 pour chaque position de bit pour laquelle les bits correspondants des deux opérandes sont des 1, si non il renvoie un 0.|
|\||OU binaire (OR)|Renvoie un 1 pour chaque position de bit pour laquelle le bit correspondant d'au moins un des deux opérandes est un 1. Si non il renvoie un 0.|
|^|OU exclusif binaire (XOR)|Renvoie un 1 pour chaque position de bit pour laquelle le bit correspondant d'un seul des deux opérandes est un 1. Si non il renvoie un 0.|
|~|NON binaire (NOT)|Inverse les bits de son opérande: 0 en 1 et 1 en 0.|
|<<|Décalage à gauche (Zero fill left shift)|Décale un bit en représentation binaire d'autre bit vers la gauche, en introduisant des zéros par la droite.|
|>>|Décalage à droite avec propagation du signe (Signed right shift)|Décale un bit en représentation binaire d'autre bit vers la droite, en rejetant les bits à droite.|
|>>>|Décalage à droite avec introduction de zéros (Zero fill right shift)|Décale un bit en représentation binaire d'autre bit vers la droite, en rejetant les bits à droite et en introduisant des zéros par la gauche.|

### Fonctionnement global du programme :
1. Notre programme compilera deux exécutables, un serveur et un client.
2. Nous allons exécuter le serveur qui va générer un PID et l'afficher.
3. Le serveur va tourner en boucle et se mettre en pause jusqu'à la réception d'un signal.
4. Nous allons exécuter le client qui prend 2 arguments, le PID et la chaîne à envoyer.
5. Le client va vérifier les arguments et convertir le PID passé en argument avec atoi pour l'utiliser.
6. Nous utilisons ensuite appeler ft_send_str qui va boucler la chaîne jusqu'à ce qu'elle se finisse.
7. Cette fonction va appeler la fonction ft_send_char pour chaque caractère.
8. Cette dernière va convertir le caractère ascii en binaire en utilisant SIGUSR1 pour les 1 et SIGUSR2 pour les 0.
9. Le serveur va utiliser le handler pour convertir le binaire vers un caractère ascii bit par bit via les signaux.
10. Le serveur va donc afficher ce caractère ascii et attendre un nouveau singal pour recommencer en boucle.

### Liens utiles :
https://devstory.net/12281/operations-sur-les-bits#:~:text=1%2D%20Bitwise,par%20le%20processeur%20(processor)  
http://fabrice.sincere.pagesperso-orange.fr/cm_electronique/electronique_numerique20/annexe/conversion_decimal_hexa02.pdf  
http://ressources.univ-lemans.fr/AccesLibre/UM/Pedago/physique/02/divers/logicalc.html  
