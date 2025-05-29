# 📚 Get Next Line

Une fonction C qui lit un fichier ligne par ligne, développée dans le cadre du cursus de l'École 42. Cette fonction permet de lire efficacement des fichiers de toute taille en utilisant un buffer configurable.

## 📋 Table des matières

- [À propos](#à-propos)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Fonctionnement](#fonctionnement)
- [Structure du projet](#structure-du-projet)
- [Compilation](#compilation)
- [Exemples](#exemples)
- [Gestion d'erreurs](#gestion-derreurs)
- [Performance](#performance)
- [Auteur](#auteur)

## 🔍 À propos

Get Next Line (GNL) est une fonction qui lit un fichier descripteur ligne par ligne jusqu'à la fin du fichier. Cette fonction est particulièrement utile pour traiter de gros fichiers sans charger tout le contenu en mémoire.

### Caractéristiques principales :
- **Lecture ligne par ligne** : Traitement efficace des gros fichiers
- **Buffer configurable** : Taille du buffer adaptable via `BUFFER_SIZE`
- **Gestion multi-descripteurs** : Support de plusieurs fichiers simultanément (version bonus)
- **Gestion mémoire optimisée** : Aucune fuite mémoire

## ✨ Fonctionnalités

- 🔄 **Lecture séquentielle** : Lit une ligne à chaque appel
- 📏 **Buffer flexible** : Taille configurable à la compilation
- 🔢 **Multi-descripteurs** : Gestion simultanée de plusieurs fichiers (bonus)
- 💾 **Mémoire statique** : Conservation des données entre les appels
- ⚡ **Performance optimisée** : Lecture efficace avec buffer
- 🛡️ **Gestion d'erreurs robuste** : Gestion des cas limites

## 🚀 Installation

### Prérequis

- GCC ou Clang
- Make
- Bibliothèque standard C

### Compilation

```bash
# Cloner le projet
git clone https://github.com/mossfreestyle/get_next_line.git
cd get_next_line

# Compiler avec votre projet
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c main.c
```

## 💻 Utilisation

### Syntaxe de base

```c
#include "get_next_line.h"

char *get_next_line(int fd);
```

### Exemple d'utilisation

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## 🔧 Fonctionnement

### Algorithme principal

1. **Lecture du buffer** : Lit `BUFFER_SIZE` caractères du fichier
2. **Recherche du '\n'** : Cherche le caractère de fin de ligne
3. **Extraction de la ligne** : Extrait la ligne complète avec le '\n'
4. **Sauvegarde du reste** : Conserve les données restantes pour l'appel suivant
5. **Retour** : Retourne la ligne ou NULL si fin de fichier

### Gestion de la mémoire statique

```c
static char *saved_line[MAX_FD];  // Sauvegarde par descripteur (bonus)
```

## 📁 Structure du projet

```
get_next_line/
├── get_next_line.c              # Fonction principale
├── get_next_line.h              # Header principal
├── get_next_line_utils.c        # Fonctions utilitaires
├── get_next_line_bonus.c        # Version multi-descripteurs
├── get_next_line_bonus.h        # Header bonus
└── get_next_line_utils_bonus.c  # Utilitaires bonus
```

## 🛠️ Compilation

### Variables de compilation

```bash
# Taille du buffer (par défaut)
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Version bonus (multi-descripteurs)
gcc -D BUFFER_SIZE=1024 get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Makefile exemple

```makefile
NAME = gnl_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=1024
SRCS = get_next_line.c get_next_line_utils.c main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(OBJS) -o $(NAME)

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

## 🎯 Exemples pratiques

### Lecture d'un fichier simple

```c
int fd = open("exemple.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("Ligne lue : %s", line);
    free(line);
}
close(fd);
```

### Lecture de l'entrée standard

```c
char *line;

printf("Entrez du texte (Ctrl+D pour terminer) :\n");
while ((line = get_next_line(0)) != NULL)
{
    printf("Vous avez tapé : %s", line);
    free(line);
}
```

### Version bonus - Multiples descripteurs

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
char *line1, *line2;

line1 = get_next_line(fd1);
line2 = get_next_line(fd2);
line1 = get_next_line(fd1);  // Continue avec file1

// Libération mémoire et fermeture
free(line1);
free(line2);
close(fd1);
close(fd2);
```

## 🛡️ Gestion d'erreurs

La fonction gère automatiquement :

- **Descripteur invalide** : Retourne NULL si fd < 0
- **Erreur de lecture** : Retourne NULL en cas d'erreur
- **Fin de fichier** : Retourne NULL quand le fichier est entièrement lu
- **Allocation échouée** : Libère la mémoire et retourne NULL
- **Buffer invalide** : Gère les cas où BUFFER_SIZE ≤ 0

### Valeurs de retour

```c
char *line = get_next_line(fd);

if (line == NULL)
{
    // Fin de fichier ou erreur
    if (/* vérifier si erreur */)
        printf("Erreur de lecture\n");
    else
        printf("Fin de fichier atteinte\n");
}
```

## ⚡ Performance

### Optimisations implémentées

- **Buffer statique** : Évite les allocations répétées
- **Lecture par blocs** : Réduit les appels système
- **Réutilisation mémoire** : Conservation des données entre appels
- **Gestion efficace des chaînes** : Utilisation optimale de ft_strjoin

### Recommandations BUFFER_SIZE

| Taille | Usage | Performance |
|--------|-------|-------------|
| 1 | Test extrême | Très lente |
| 42 | Test classique | Acceptable |
| 1024 | Usage normal | Bonne |
| 4096 | Gros fichiers | Optimale |
| 8192+ | Très gros fichiers | Excellente |

## 🧮 Fonctions utilitaires

Les fonctions helper utilisées :

```c
// get_next_line_utils.c
char    *ft_strchr(const char *s, int c);
char    *ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *s);
char    *ft_strdup(const char *s1);
char    *ft_substr(char const *s, unsigned int start, size_t len);
```

## 🔬 Tests recommandés

### Tests basiques
```bash
# Test avec différentes tailles de buffer
gcc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c test.c
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c test.c
gcc -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c test.c
```

### Tests avec fichiers spéciaux
- Fichier vide
- Fichier d'une seule ligne sans '\n'
- Fichier avec lignes très longues
- Fichier binaire
- Lecture depuis /dev/stdin

## 🏫 Projet 42

Ce projet fait partie du cursus de l'École 42 et permet d'apprendre :

- **Gestion de fichiers** : Descripteurs de fichiers et fonctions système
- **Mémoire statique** : Variables statiques et leur persistance
- **Algorithmes de parsing** : Traitement de chaînes caractère par caractère
- **Optimisation** : Gestion efficace de la mémoire et des performances
- **Gestion d'erreurs** : Robustesse et cas limites

## 📚 Fonctions système utilisées

- `read()` : Lecture depuis un descripteur de fichier
- `malloc()` : Allocation dynamique de mémoire
- `free()` : Libération de mémoire

## 🐛 Debugging conseils

### Vérification des fuites mémoire
```bash
valgrind --leak-check=full ./your_program
```

### Test avec différents BUFFER_SIZE
```bash
for size in 1 10 100 1000; do
    gcc -D BUFFER_SIZE=$size get_next_line.c get_next_line_utils.c test.c -o test_$size
    ./test_$size
done
```

## 🔗 Ressources utiles

- [Documentation read()](https://man7.org/linux/man-pages/man2/read.2.html)
- [Gestion des descripteurs de fichiers](https://www.gnu.org/software/libc/manual/html_node/File-Descriptors.html)
- [Variables statiques en C](https://www.geeksforgeeks.org/static-variables-in-c/)

## 👨‍💻 Auteur

**rwassim** - Étudiant à l'École 42

- GitHub: [@rwassim](https://github.com/mossfreestyle)
- Email: rwassim@student.42.fr

## 📄 Licence

Ce projet est développé dans le cadre du cursus de l'École 42. Code disponible pour l'apprentissage et la référence.

---

⭐ **N'hésitez pas à laisser une étoile si ce projet vous a été utile !**

*Développé avec ❤️ à l'École 42*
