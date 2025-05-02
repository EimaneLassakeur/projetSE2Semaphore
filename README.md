# Synchronisation des Bus dans un Tunnel (Projet SE2)

Projet de simulation de synchronisation de bus avec des sémaphores, réalisé dans le cadre du cours **Systèmes d'Exploitation 2** (L3 ISIL, Université d'Alger 1 - 2024/2025).

## Contexte

Deux villes, **X** et **Y**, sont reliées par un **tunnel à voie unique**. Chaque jour :

- La ville **X** dispose de **5 bus**.
- La ville **Y** dispose de **4 bus**.
- Chaque bus effectue **10 allers-retours** (X → Y → X ou Y → X → Y).

### Contraintes de circulation :

- **Pas de croisement** : aucun bus ne peut entrer si un bus circule en sens opposé.
- **Circulation groupée** : plusieurs bus dans le **même sens** peuvent utiliser le tunnel simultanément.
- **Équité** : un sens ne doit pas bloquer l’autre indéfiniment (pas de famine).
- **Simulation** : chaque trajet dure entre **1 et 1.5 secondes**.

---

## Technologies utilisées

- Langage : **C**
- Threads : `pthread`
- Sémaphores : `semaphore.h` (POSIX)
- OS : Linux / UNIX recommandé

---

## Compilation et exécution

### Prérequis

- Un compilateur C (ex: `gcc`)
- Système compatible POSIX (Linux/Mac)

### Compilation

```bash
gcc -o tunnel tunnel.c -lpthread
```

### Exécution

```bash
./tunnel
```
---

## Organisation du code

-**tunnel.c** : fichier source principal contenant :

  -La gestion des threads pour les bus
  -L’utilisation des sémaphores pour synchroniser l’accès au tunnel
  -Les fonctions d’entrée/sortie du tunnel
  -La simulation des trajets

---

## Auteurs


-**Eimane El Fadil LASSAKEUR**

-**Younes Mohamed MEDBOUH**

Projet réalisé dans le cadre du module Systèmes d’Exploitation 2
Université d'Alger 1 - Département d'Informatique
Année universitaire 2024/2025
