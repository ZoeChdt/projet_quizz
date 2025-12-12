//
// Created by Kenza Bakadi on 08/12/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionChoixMultiples.h"

// Tests de construction

TEST_CASE("[questionQCM] l'enonce est correctement stocke") {
    std::vector<std::string> choix{"Paris","Londres","Berlin", "Madrid"};
    questionQCM q{"Quelle est la capitale de la France ?", choix, 0};
    REQUIRE(q.enonce() == "Quelle est la capitale de la France ?");
}

TEST_CASE("[questionQCM] le numero de reponse est correctement stocke") {
    std::vector<std::string> choix{"Mercure", "Vénus", "Mars", "Jupiter"};
    questionQCM q{"Quelle est la planète la plus proche du Soleil ?", choix, 0};
    REQUIRE(q.numeroReponse() == 0);
}

TEST_CASE("[questionQCM] le nombre de choix est correct") {
    std::vector<std::string> choix{"Rouge", "Bleu", "Vert", "Jaune"};
    questionQCM q{"Quelle est la couleur du ciel ?", choix, 1};
    REQUIRE(q.nombreChoix() == 4);
}

TEST_CASE("[questionQCM] reponse() retourne le bon choix") {
    std::vector<std::string> choix{"Italie", "Espagne", "France", "Allemagne"};
    questionQCM q{"Dans quel pays se trouve la Tour Eiffel ?", choix, 2};
    REQUIRE(q.reponse() == "France");
}

TEST_CASE("[questionQCM] acces aux choix individuels") {
    std::vector<std::string> choix{"1789", "1799", "1815", "1830"};
    questionQCM q{"En quelle année a eu lieu la Révolution française ?", choix, 0};
    REQUIRE(q.choix(0) == "1789");
    REQUIRE(q.choix(1) == "1799");
    REQUIRE(q.choix(2) == "1815");
    REQUIRE(q.choix(3) == "1830");
}

// Tests : reponseJuste

TEST_CASE("[questionQCM] reponseJuste avec bonne reponse") {
    std::vector<std::string> choix{"4", "5", "6", "7"};
    questionQCM q{"Combien de continents y a-t-il ?", choix, 2};
    REQUIRE(q.reponseJuste("2"));
}

TEST_CASE("[questionQCM] reponseJuste avec mauvaise réponse") {
    std::vector<std::string> choix{"Chien", "Chat", "Souris", "Oiseau"};
    questionQCM q{"Quel animal miaule ?", choix, 1};
    REQUIRE_FALSE(q.reponseJuste("0"));
    REQUIRE_FALSE(q.reponseJuste("2"));
    REQUIRE_FALSE(q.reponseJuste("3"));
}

TEST_CASE("[questionQCM] reponseJuste avec entree invalide") {
    std::vector<std::string> choix{"Lundi", "Mardi", "Mercredi", "Jeudi"};
    questionQCM q{"Quel est le premier jour de la semaine ?", choix, 0};
    REQUIRE_FALSE(q.reponseJuste("abc"));
    REQUIRE_FALSE(q.reponseJuste(""));
    REQUIRE_FALSE(q.reponseJuste("-1"));
    REQUIRE_FALSE(q.reponseJuste("2.5"));
}

TEST_CASE("[questionQCM] reponseJuste avec numero hors limites") {
    std::vector<std::string> choix{"Pomme", "Banane", "Orange", "Fraise"};
    questionQCM q{"Quel fruit est jaune ?", choix, 1};
    REQUIRE_FALSE(q.reponseJuste("4"));
    REQUIRE_FALSE(q.reponseJuste("10"));
}