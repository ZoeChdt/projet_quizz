//
// Created by chzoe on 18/11/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionNumerique.h"

// Tests de construction

TEST_CASE("[questionNumerique] L'enoncé est correctement stocké") {
    std::string e = "Combien font 2+2 ?";
    questionNumerique q{e, 4, 0, 7};
    REQUIRE(q.enonce() == e);
}

TEST_CASE("[questionNumerique] La réponse est correctement stockée") {
    questionNumerique q{"Combien font 5+7 ?", 12, 0, 15};
    REQUIRE(q.reponseNumerique() == 12);
    REQUIRE(q.reponse() == "12");
}

TEST_CASE("[questionNumerique] Les limites sont correctement stockées") {
    questionNumerique q{"Question", 50, 10, 100};
    REQUIRE(q.limiteMinimum() == 10);
    REQUIRE(q.limiteMaximum() == 100);
}

TEST_CASE("[questionNumerique] Construction avec LimiteMin > LimiteMax") {
    REQUIRE_THROWS_AS(questionNumerique("Q ?", 5, 10, 0), std::invalid_argument);
}

TEST_CASE("[questionNumerique] Construction avec reponse hors limites") {
    REQUIRE_THROWS_AS(questionNumerique("Q ?", -1, 0, 10), std::invalid_argument);
    REQUIRE_THROWS_AS(questionNumerique("Q ?", 11, 0, 10), std::invalid_argument);
}

// Tests : reponseJuste

TEST_CASE("[questionNumerique] reponseJuste accepte toute valeur dans l'intervalle") {
    questionNumerique q{"Combien font 10+5 ?", 15, 10, 20};
    REQUIRE(q.reponseJuste("15"));  // réponse exacte
    REQUIRE(q.reponseJuste("10"));  // limite min
    REQUIRE(q.reponseJuste("20"));  // limite max
    REQUIRE(q.reponseJuste("12"));  // autre valeur dans l'intervalle
    REQUIRE(q.reponseJuste("18"));  // autre valeur dans l'intervalle
}

TEST_CASE("[questionNumerique] reponseJuste retourne faux pour valeur hors intervalle") {
    questionNumerique q{"Combien font 10+5 ?", 15, 10, 20};
    REQUIRE_FALSE(q.reponseJuste("9"));    // en dessous du min
    REQUIRE_FALSE(q.reponseJuste("21"));   // au-dessus du max
    REQUIRE_FALSE(q.reponseJuste("0"));    // hors intervalle
    REQUIRE_FALSE(q.reponseJuste("100"));  // hors intervalle
}

TEST_CASE("[questionNumerique] reponseJuste gère les entrées invalides") {
    questionNumerique q{"Combien font 10+5 ?", 15, 10, 20};
    REQUIRE_FALSE(q.reponseJuste("abc"));      // pas un nombre
    REQUIRE_FALSE(q.reponseJuste(""));         // chaîne vide
    REQUIRE_FALSE(q.reponseJuste("15.5"));     // nombre décimal
}

TEST_CASE("[questionNumerique] Intervalle avec nombres négatifs") {
    questionNumerique q{"Température", -5, -10, 0};
    REQUIRE(q.reponseJuste("-5"));
    REQUIRE(q.reponseJuste("-10"));
    REQUIRE(q.reponseJuste("0"));
    REQUIRE(q.reponseJuste("-7"));
    REQUIRE_FALSE(q.reponseJuste("-11"));
    REQUIRE_FALSE(q.reponseJuste("1"));
}