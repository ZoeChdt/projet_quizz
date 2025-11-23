//
// Created by Aktas Julidè on 23/11/2025.
//
#include "doctest.h"
#include "questionChoixMultiples.h"

TEST_CASE("[questionChoixMultiples] La question correctement construite") {
    std::string e = "Quelle est la capitale de France ?";
    std::vector<std::string> choix {"Paris","Londres","Madrid","Berlin"};
    int reponse =0;
    questionQCM q{e,choix,reponse};

    SUBCASE("L'énoncé est correctement stocké") {
        REQUIRE_EQ(q.enonce(),e);
    }
    SUBCASE("Le numéro de réponse est correctement stocké") {
        REQUIRE_EQ(q.numeroReponse(),reponse);
    }

    SUBCASE("La réponse est correctement stockée") {
        REQUIRE_EQ(q.reponse(),"Paris");
    }

    SUBCASE("Le nombre de choix est correct") {
        REQUIRE_EQ(q.nombreChoix(),4);
    }

    SUBCASE("Le numéro de choix est correctement associé à sa réponse") {
        REQUIRE_EQ(choix[0],"Paris");
        REQUIRE_EQ(choix[1],"Londres");
        REQUIRE_EQ(choix[2],"Madrid");
        REQUIRE_EQ(choix[3],"Berlin");
    }

}
TEST_CASE("[questionChoixMultiples] reponseJuste fonctionne correctement") {
    std::string e = "Quelle est la capitale de France ?";
    std::vector<std::string> choix {"Paris","Londres","Madrid","Berlin"};
    int reponse =0;
    questionQCM q{e,choix,reponse};
    SUBCASE("reponseJuste retourne vrai pour la bonne réponse") {
        REQUIRE_EQ(q.reponseJuste("0"),true);
    }
    SUBCASE("reponseJuste retourne faux pour les mauvaises réponses") {
        REQUIRE_EQ(q.reponseJuste("1"),false);
        REQUIRE_EQ(q.reponseJuste("2"),false);
        REQUIRE_EQ(q.reponseJuste("3"),false);
    }

}

TEST_CASE("[questionChoixMultiples] reponseJuste gère les entrées invalides") {
    std::string e = "Quelle est la capitale de France ?";
    std::vector<std::string> choix {"Paris","Londres","Madrid","Berlin"};
    int reponse =0;
    questionQCM q{e,choix,reponse};
    SUBCASE("reponseJuste retourne faux en cas d'entrées numériques hors limites") {
        SUBCASE("reponseJuste renvoie faux en cas d'entrées numériques hors choix possibles") {
            REQUIRE_EQ(q.reponseJuste("56"),false);
        }
        SUBCASE("reponseJuste renvoie faux en cas d'entrées numériques négatives") {
            REQUIRE_EQ(q.reponseJuste("-3"),false);
        }
    }
    SUBCASE("reponseJuste retourne faux en cas d'entrées textuelles") {
        //bonne réponse mais expression textuelle au lieu de numérique
        CHECK_THROWS_AS(q.reponseJuste("Paris"),std::invalid_argument);
        //expression textuelle quelconque
        CHECK_THROWS_AS(q.reponseJuste("a"),std::invalid_argument);
        //espace
        CHECK_THROWS_AS(q.reponseJuste(" "),std::invalid_argument);
        //chaîne vide
        CHECK_THROWS_AS(q.reponseJuste(""),std::invalid_argument);
    }
}



