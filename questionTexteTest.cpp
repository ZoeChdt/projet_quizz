//
// Created by chzoe on 19/11/2025.
//
#include "doctest.h"
#include "questionTexte.h"

//Tests de construction

TEST_CASE("[questionTexte] L'enoncé est correctement stocké") {
    std::string e = "Quelle est la capitale de France ?";
    questionTexte q{e, "Paris"};
    REQUIRE(q.enonce() == e);
}

TEST_CASE("[questionTexte] La réponse est correctement stockée") {
    questionTexte q{"Quelle est la capitale de France ?", "Paris"};
    REQUIRE(q.reponse() == "Paris");
}

// Tests : reponse Juste

TEST_CASE("[questionTexte] Retourne juste pour bonne reponse") {
    questionTexte q{"Quelle est la capitale de France ?", "Paris"};
    REQUIRE(q.reponseJuste("Paris"));
}

//Tests : reponse Fausse

TEST_CASE("[questionTexte] Retourne juste pour mauvaise reponse") {
    questionTexte q{"Quelle est la capitale de France ?", "Paris"};
    REQUIRE_FALSE(q.reponseJuste("Londres"));
}

TEST_CASE("[questionTexte] Chaine de caractère vide") {
    questionTexte q{"Quelle est la capitale de France ?", "Paris"};
    REQUIRE_FALSE(q.reponseJuste(""));
}
