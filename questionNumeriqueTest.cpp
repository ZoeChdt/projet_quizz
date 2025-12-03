//
// Created by chzoe on 18/11/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionNumerique.h"

// Tests de construction

TEST_CASE("[questionNumerique] L'enoncé est correctement stocké") {
    std::string e = "Combien font 2+2 ?";
    questionNumerique q{e, 4,0,7};
    REQUIRE(q.enonce() == e);
}

TEST_CASE("[questionNumerique] La réponse est correctement stockée") {
    questionNumerique q{"Combien font 5+7 ?", 12, 0, 15};
    REQUIRE(q.reponse() == 12);
}

TEST_CASE("[questionNumerique] Construction avec LimiteMin > LimiteMax") {
    REQUIRE_THROWS_AS(questionNumerique("Q ?",5,10,0), std::invalid_argument);
}

TEST_CASE("[questionNumerique] Construction avec reponse hors limites") {
    REQUIRE_THROWS_AS(questionNumerique("Q ?", -1, 0, 10), std::invalid_argument);
    REQUIRE_THROWS_AS(questionNumerique("Q ?", 11, 0, 10), std::invalid_argument);
}

// Tests : reponseJuste

TEST_CASE("[questionNumerique] reponseJuste retourne vrai pour la bonne réponse") {
    questionNumerique q{"Combien font 10+5 ?", 15, 0, 20};
    REQUIRE(q.reponseJuste("15"));        // chaîne de caractères
}

TEST_CASE("[questionNumerique] reponseJuste retourne faux pour une mauvaise réponse") {
    questionNumerique q{"Combien font 10+5 ?", 15,0,19};
    REQUIRE_FALSE(q.reponseJuste("14"));  // chaîne de caractères
    REQUIRE_FALSE(q.reponseJuste("0"));
    REQUIRE_FALSE(q.reponseJuste("16"));
}

TEST_CASE("[questionNumerique] reponseJuste gère les entrées invalides") {
    questionNumerique q{"Combien font 10+5 ?", 15, 0, 20};
    REQUIRE_FALSE(q.reponseJuste("abc"));      // pas un nombre
    REQUIRE_FALSE(q.reponseJuste(""));         // chaîne vide
    REQUIRE_FALSE(q.reponseJuste("15.5"));     // nombre décimal
}