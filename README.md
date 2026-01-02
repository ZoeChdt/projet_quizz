# Système de Quiz Interactif en C++

## Description du Projet

Ce projet implémente un système complet de quiz en C++ orienté objet. Il permet de créer, gérer et passer des questionnaires avec différents types de questions et modes d'évaluation.

## Fonctionnalités Principales

### Types de Questions

1. **Questions Texte** (`questionTexte`)
   - Questions à réponse libre textuelle
   - Comparaison exacte de la réponse

2. **Questions Numériques** (`questionNumerique`)
   - Questions nécessitant une réponse numérique exacte
   - Validation avec intervalle min/max
   - Seule la réponse exacte est acceptée (pas de tolérance)

3. **Questions à Choix Multiples** (`questionQCM`)
   - Questions avec plusieurs options
   - Sélection d'une seule réponse correcte

### Modes de Session

#### 1. Session d'Apprentissage (`sessionApprentissage`)
- Mode simple pour parcourir les questions
- Pas de comptabilisation des scores

#### 2. Session d'Évaluation - Test (`evaluationTest`)
- Évaluation classique : une chance par question
- Pas d'affichage de la bonne réponse
- Comptabilisation du score

#### 3. Session d'Évaluation - Seconde Chance (`evaluationSecondeChance`)
- Donne une deuxième tentative en cas d'erreur
- Affiche la bonne réponse après deux échecs
- Reste sur la même question jusqu'à réussite ou épuisement des chances

#### 4. Session d'Évaluation Adaptative (`evaluationAdaptative`)
- Repose les questions ratées à la fin
- Continue jusqu'à ce que toutes les questions soient réussies
- Mode d'apprentissage progressif

### Système de Persistance

- **Sauvegarde** : Export des questionnaires dans des fichiers texte
- **Chargement** : Import avec reconstruction complète des questions
- **Pattern Prototype** : Utilisation d'un registre pour la création dynamique

### Classes Utilitaires

- **questionnaire** : Conteneur de questions
- **gestionnaire** : Gestion de la sauvegarde/chargement
- **questionRepertoire** : Singleton pour le pattern Prototype

## Patterns de Conception Utilisés

1. **Polymorphisme** : Hiérarchie de questions et sessions
2. **Template Method** : Gestion des succès/échecs dans sessionEvaluation
3. **Prototype** : Création dynamique de questions via questionRepertoire
4. **Singleton** : questionRepertoire pour l'enregistrement des types

## Structure des Fichiers

### Fichiers de Questions
- `question.h` - Interface de base
- `questionTexte.{h,cpp}` - Questions texte
- `questionNumerique.{h,cpp}` - Questions numériques
- `questionChoixMultiples.{h,cpp}` - QCM

### Fichiers de Sessions
- `session.{h,cpp}` - Classe de base
- `sessionApprentissage.{h,cpp}` - Mode apprentissage
- `sessionEvaluation.{h,cpp}` - Évaluation abstraite
- `evaluationTest.{h,cpp}` - Test classique
- `evaluationSecondeChance.{h,cpp}` - Avec seconde chance
- `evaluationAdaptative.{h,cpp}` - Mode adaptatif

### Fichiers de Gestion
- `questionnaire.{h,cpp}` - Conteneur de questions
- `gestionnaire.{h,cpp}` - Sauvegarde/chargement
- `questionRepertoire.{h,cpp}` - Registre des prototypes

### Tests
Tous les fichiers `*Test.cpp` et `*Tests.cpp` contiennent les tests unitaires utilisant le framework **doctest**.

## Compilation et Exécution

### Prérequis
- Compilateur C++ compatible C++11 ou supérieur
- Framework de test doctest (inclus)

# créer par 
AKTAS Julidè 
BAKADI Kenza 
CHAUDET Zoé 
TRAN Maryam-Nur 



---

**Note** : Ce projet est conçu à des fins pédagogiques pour illustrer les concepts de programmation orientée objet en C++.
