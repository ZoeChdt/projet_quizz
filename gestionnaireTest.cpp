//
// Created by chzoe on 13/12/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "gestionnaire.h"
#include "questionTexte.h"
#include "questionNumerique.h"
#include "questionChoixMultiples.h"
#include <fstream>
#include <sstream>

TEST_CASE("[gestionnaire] Sauvegarder un questionnaire vide") {
    gestionnaire g;
    questionnaire q{"Questionnaire vide"};

    std::string nomFichier = "test_vide.txt";
    REQUIRE_NOTHROW(g.sauvegarder(q, nomFichier));

    // Vérifier que le fichier existe
    std::ifstream fichier(nomFichier);
    REQUIRE(fichier.good());
    fichier.close();

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Sauvegarder un questionnaire avec une question texte") {
    gestionnaire g;
    questionnaire q{"Quiz texte"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Capitale de France ?", "Paris"));

    std::string nomFichier = "test_texte.txt";
    REQUIRE_NOTHROW(g.sauvegarder(q, nomFichier));

    std::ifstream fichier(nomFichier);
    REQUIRE(fichier.good());
    fichier.close();

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Sauvegarder un questionnaire avec plusieurs types de questions") {
    gestionnaire g;
    questionnaire q{"Quiz mixte"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Capitale ?", "Paris"));
    q.ajouterQuestion(std::make_unique<questionNumerique>("2+2 ?", 4, 0, 10));
    std::vector<std::string> choix{"A", "B", "C"};
    q.ajouterQuestion(std::make_unique<questionQCM>("Choix ?", choix, 1));

    std::string nomFichier = "test_mixte.txt";
    REQUIRE_NOTHROW(g.sauvegarder(q, nomFichier));

    std::ifstream fichier(nomFichier);
    REQUIRE(fichier.good());
    fichier.close();

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Charger un questionnaire vide") {
    gestionnaire g;
    questionnaire q{"Questionnaire vide"};

    std::string nomFichier = "test_chargement_vide.txt";
    g.sauvegarder(q, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);
    REQUIRE(qCharge.titre() == "Questionnaire vide");
    REQUIRE(qCharge.nombreQuestions() == 0);

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Charger un questionnaire avec une question texte") {
    gestionnaire g;
    questionnaire q{"Quiz texte"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Capitale de France ?", "Paris"));

    std::string nomFichier = "test_chargement_texte.txt";
    g.sauvegarder(q, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);
    REQUIRE(qCharge.titre() == "Quiz texte");
    REQUIRE(qCharge.nombreQuestions() == 1);
    REQUIRE(qCharge.recupererQuestion(0).enonce() == "Capitale de France ?");
    REQUIRE(qCharge.recupererQuestion(0).reponse() == "Paris");
    REQUIRE(qCharge.recupererQuestion(0).typeQuestion() == "TEXTE");

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Charger un questionnaire avec une question numérique") {
    gestionnaire g;
    questionnaire q{"Quiz numérique"};
    q.ajouterQuestion(std::make_unique<questionNumerique>("Combien font 5+7 ?", 12, 0, 20));

    std::string nomFichier = "test_chargement_num.txt";
    g.sauvegarder(q, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);
    REQUIRE(qCharge.titre() == "Quiz numérique");
    REQUIRE(qCharge.nombreQuestions() == 1);
    REQUIRE(qCharge.recupererQuestion(0).enonce() == "Combien font 5+7 ?");
    REQUIRE(qCharge.recupererQuestion(0).reponse() == "12");
    REQUIRE(qCharge.recupererQuestion(0).typeQuestion() == "NUMERIQUE");

    // Seule la réponse exacte (12) est acceptée
    REQUIRE(qCharge.recupererQuestion(0).reponseJuste("12"));
    REQUIRE_FALSE(qCharge.recupererQuestion(0).reponseJuste("15"));  // dans l'intervalle mais pas exacte
    REQUIRE_FALSE(qCharge.recupererQuestion(0).reponseJuste("25"));  // hors intervalle

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Charger un questionnaire avec un QCM") {
    gestionnaire g;
    questionnaire q{"Quiz QCM"};
    std::vector<std::string> choix{"Paris", "Londres", "Berlin"};
    q.ajouterQuestion(std::make_unique<questionQCM>("Capitale de France ?", choix, 0));

    std::string nomFichier = "test_chargement_qcm.txt";
    g.sauvegarder(q, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);
    REQUIRE(qCharge.titre() == "Quiz QCM");
    REQUIRE(qCharge.nombreQuestions() == 1);
    REQUIRE(qCharge.recupererQuestion(0).enonce() == "Capitale de France ?");
    REQUIRE(qCharge.recupererQuestion(0).reponse() == "Paris");
    REQUIRE(qCharge.recupererQuestion(0).typeQuestion() == "QCM");
    REQUIRE(qCharge.recupererQuestion(0).reponseJuste("0"));
    REQUIRE_FALSE(qCharge.recupererQuestion(0).reponseJuste("1"));
    REQUIRE_FALSE(qCharge.recupererQuestion(0).reponseJuste("2"));

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Charger un questionnaire avec plusieurs questions") {
    gestionnaire g;
    questionnaire q{"Quiz complet"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Question 1", "Réponse 1"));
    q.ajouterQuestion(std::make_unique<questionNumerique>("Question 2", 42, 0, 100));
    std::vector<std::string> choix{"A", "B", "C"};
    q.ajouterQuestion(std::make_unique<questionQCM>("Question 3", choix, 2));

    std::string nomFichier = "test_chargement_complet.txt";
    g.sauvegarder(q, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);
    REQUIRE(qCharge.titre() == "Quiz complet");
    REQUIRE(qCharge.nombreQuestions() == 3);

    REQUIRE(qCharge.recupererQuestion(0).typeQuestion() == "TEXTE");
    REQUIRE(qCharge.recupererQuestion(0).enonce() == "Question 1");

    REQUIRE(qCharge.recupererQuestion(1).typeQuestion() == "NUMERIQUE");
    REQUIRE(qCharge.recupererQuestion(1).enonce() == "Question 2");

    REQUIRE(qCharge.recupererQuestion(2).typeQuestion() == "QCM");
    REQUIRE(qCharge.recupererQuestion(2).enonce() == "Question 3");

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] Sauvegarde et chargement préservent les données") {
    gestionnaire g;
    questionnaire qOriginal{"Quiz de géographie"};
    qOriginal.ajouterQuestion(std::make_unique<questionTexte>("Capitale de France ?", "Paris"));
    qOriginal.ajouterQuestion(std::make_unique<questionNumerique>("Nombre de continents ?", 7, 1, 10));
    std::vector<std::string> choix{"Mercure", "Vénus", "Terre", "Mars"};
    qOriginal.ajouterQuestion(std::make_unique<questionQCM>("Troisième planète ?", choix, 2));

    std::string nomFichier = "test_persistance.txt";
    g.sauvegarder(qOriginal, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);

    REQUIRE(qCharge.titre() == qOriginal.titre());
    REQUIRE(qCharge.nombreQuestions() == qOriginal.nombreQuestions());

    for (size_t i = 0; i < qOriginal.nombreQuestions(); ++i) {
        const question& qOrig = qOriginal.recupererQuestion(i);
        const question& qLoad = qCharge.recupererQuestion(i);

        REQUIRE(qLoad.typeQuestion() == qOrig.typeQuestion());
        REQUIRE(qLoad.enonce() == qOrig.enonce());
        REQUIRE(qLoad.reponse() == qOrig.reponse());
    }

    std::remove(nomFichier.c_str());
}

TEST_CASE("[gestionnaire] La validation des réponses fonctionne après chargement") {
    gestionnaire g;
    questionnaire qOriginal{"Quiz de validation"};

    // Question texte
    qOriginal.ajouterQuestion(std::make_unique<questionTexte>("Capitale ?", "Paris"));

    // Question numérique
    qOriginal.ajouterQuestion(std::make_unique<questionNumerique>("2+2 ?", 4, 0, 10));

    // Question QCM
    std::vector<std::string> choix{"Rouge", "Vert", "Bleu"};
    qOriginal.ajouterQuestion(std::make_unique<questionQCM>("Couleur du ciel ?", choix, 2));

    std::string nomFichier = "test_validation.txt";
    g.sauvegarder(qOriginal, nomFichier);

    questionnaire qCharge = g.charger(nomFichier);

    SUBCASE("Question texte : validation correcte") {
        const question& q = qCharge.recupererQuestion(0);
        REQUIRE(q.reponseJuste("Paris"));
        REQUIRE_FALSE(q.reponseJuste("Londres"));
    }

    SUBCASE("Question numérique : seule la réponse exacte est acceptée") {
        const question& q = qCharge.recupererQuestion(1);
        REQUIRE(q.reponseJuste("4"));      // réponse exacte
        REQUIRE_FALSE(q.reponseJuste("5")); // dans l'intervalle mais pas exacte
        REQUIRE_FALSE(q.reponseJuste("0")); // limite min
        REQUIRE_FALSE(q.reponseJuste("10")); // limite max
        REQUIRE_FALSE(q.reponseJuste("11")); // hors intervalle
    }

    SUBCASE("Question QCM : validation correcte") {
        const question& q = qCharge.recupererQuestion(2);
        REQUIRE(q.reponseJuste("2"));
        REQUIRE_FALSE(q.reponseJuste("0"));
        REQUIRE_FALSE(q.reponseJuste("1"));
    }

    std::remove(nomFichier.c_str());
}