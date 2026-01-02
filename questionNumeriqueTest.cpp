//
// Created by chzoe on 18/11/2025.
//
#include "doctest.h"
#include "questionNumerique.h"

// Fonctions d'assertion de haut niveau
void laReponseExacteEst(const questionNumerique& q, int reponse) {
    REQUIRE(q.reponseNumerique() == reponse);
    REQUIRE(q.reponse() == std::to_string(reponse));
}

void lesLimitesSont(const questionNumerique& q, int min, int max) {
    REQUIRE(q.limiteMinimum() == min);
    REQUIRE(q.limiteMaximum() == max);
}

void laReponseNumEstAcceptee(const question& q, const std::string& reponse) {
    REQUIRE(q.reponseJuste(reponse));
}

void laReponseNumEstRefusee(const question& q, const std::string& reponse) {
    REQUIRE_FALSE(q.reponseJuste(reponse));
}

// Tests de construction

TEST_CASE("[questionNumerique] La construction est correcte") {
    SUBCASE("L'énoncé est correctement stocké") {
        std::string enonce = "Combien font 2+2 ?";
        questionNumerique q{enonce, 4, 0, 7};
        REQUIRE_EQ(q.enonce(), enonce);
    }

    SUBCASE("La réponse est correctement stockée") {
        questionNumerique q{"Combien font 5+7 ?", 12, 0, 15};
        laReponseExacteEst(q, 12);
    }

    SUBCASE("Les limites sont correctement stockées") {
        questionNumerique q{"Question", 50, 10, 100};
        lesLimitesSont(q, 10, 100);
    }
}

TEST_CASE("[questionNumerique] La construction avec des paramètres invalides lance une exception") {
    SUBCASE("Limite minimum supérieure à la limite maximum") {
        REQUIRE_THROWS_AS(
            questionNumerique("Question ?", 5, 10, 0),
            std::invalid_argument
        );
    }

    SUBCASE("Réponse inférieure à la limite minimum") {
        REQUIRE_THROWS_AS(
            questionNumerique("Question ?", -1, 0, 10),
            std::invalid_argument
        );
    }

    SUBCASE("Réponse supérieure à la limite maximum") {
        REQUIRE_THROWS_AS(
            questionNumerique("Question ?", 11, 0, 10),
            std::invalid_argument
        );
    }
}

// Tests de validation des réponses

TEST_CASE("[questionNumerique] Seule la réponse exacte est acceptée") {
    questionNumerique q{"Combien font 10+5 ?", 15, 10, 20};

    SUBCASE("La réponse exacte est acceptée") {
        laReponseNumEstAcceptee(q, "15");
    }

    SUBCASE("Les autres valeurs dans l'intervalle sont refusées") {
        laReponseNumEstRefusee(q, "10");  // limite min
        laReponseNumEstRefusee(q, "20");  // limite max
        laReponseNumEstRefusee(q, "12");  // valeur intermédiaire
        laReponseNumEstRefusee(q, "18");  // valeur intermédiaire
    }
}

TEST_CASE("[questionNumerique] Les valeurs hors intervalle sont refusées") {
    questionNumerique q{"Combien font 10+5 ?", 15, 10, 20};

    SUBCASE("Une valeur en dessous du minimum est refusée") {
        laReponseNumEstRefusee(q, "9");
        laReponseNumEstRefusee(q, "0");
    }

    SUBCASE("Une valeur au-dessus du maximum est refusée") {
        laReponseNumEstRefusee(q, "21");
        laReponseNumEstRefusee(q, "100");
    }
}

TEST_CASE("[questionNumerique] Les entrées invalides sont refusées") {
    questionNumerique q{"Combien font 10+5 ?", 15, 10, 20};

    SUBCASE("Une chaîne non numérique est refusée") {
        laReponseNumEstRefusee(q, "abc");
    }

    SUBCASE("Une chaîne vide est refusée") {
        laReponseNumEstRefusee(q, "");
    }

    SUBCASE("Un nombre décimal est refusé") {
        laReponseNumEstRefusee(q, "15.5");
    }
}

TEST_CASE("[questionNumerique] Les réponses négatives fonctionnent correctement") {
    questionNumerique q{"Température", -5, -10, 0};

    SUBCASE("La réponse exacte négative est acceptée") {
        laReponseNumEstAcceptee(q, "-5");
    }

    SUBCASE("Les autres valeurs dans l'intervalle sont refusées") {
        laReponseNumEstRefusee(q, "-10");  // limite min
        laReponseNumEstRefusee(q, "0");    // limite max
        laReponseNumEstRefusee(q, "-7");   // valeur intermédiaire
    }

    SUBCASE("Les valeurs hors de l'intervalle sont refusées") {
        laReponseNumEstRefusee(q, "-11");
        laReponseNumEstRefusee(q, "1");
    }
}

// Tests de sauvegarde et chargement

TEST_CASE("[questionNumerique] La sauvegarde et le chargement préservent les données") {
    questionNumerique qOriginal{"Combien font 7+8 ?", 15, 0, 30};
    std::string nomFichier = "test_num_save.txt";

    // Sauvegarde
    std::ofstream fichierSave(nomFichier);
    qOriginal.sauvegarder(fichierSave);
    fichierSave.close();

    // Chargement
    std::ifstream fichierLoad(nomFichier);
    std::string type;
    std::getline(fichierLoad, type);
    auto qCharge = qOriginal.chargerDepuisFichier(fichierLoad);
    fichierLoad.close();

    SUBCASE("L'énoncé est préservé") {
        REQUIRE_EQ(qCharge->enonce(), qOriginal.enonce());
    }

    SUBCASE("La réponse est préservée") {
        REQUIRE_EQ(qCharge->reponse(), qOriginal.reponse());
    }

    SUBCASE("Seule la réponse exacte est acceptée après chargement") {
        laReponseNumEstAcceptee(*qCharge, "15");  // réponse exacte
        laReponseNumEstRefusee(*qCharge, "0");    // limite min
        laReponseNumEstRefusee(*qCharge, "30");   // limite max
        laReponseNumEstRefusee(*qCharge, "20");   // dans l'intervalle
        laReponseNumEstRefusee(*qCharge, "31");   // hors intervalle
        laReponseNumEstRefusee(*qCharge, "-1");   // hors intervalle
    }
    std::remove(nomFichier.c_str());
}
