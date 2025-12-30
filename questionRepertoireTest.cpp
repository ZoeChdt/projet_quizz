//
// Created by chzoe on 22/12/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionRepertoire.h"
#include "questionTexte.h"
#include "questionNumerique.h"
#include "questionChoixMultiples.h"
#include <sstream>
#include <fstream>

// Tests de l'instance singleton

TEST_CASE("[questionRepertoire] L'instance singleton retourne toujours la meme reference") {
    questionRepertoire& rep1 = questionRepertoire::instance();
    questionRepertoire& rep2 = questionRepertoire::instance();
    REQUIRE(&rep1 == &rep2);
}

// Tests de chargement des types de questions

TEST_CASE("[questionRepertoire] Charger une question de type TEXTE") {
    SUBCASE("La question texte chargee est correcte") {
        std::string nomFichier = "test_rep_texte.txt";
        std::ofstream fichier(nomFichier);
        fichier << "Question texte test\n";
        fichier << "Reponse test\n";
        fichier.close();

        std::ifstream fichierLecture(nomFichier);
        auto q = questionRepertoire::instance().charger(fichierLecture, "TEXTE");
        fichierLecture.close();

        REQUIRE(q->typeQuestion() == "TEXTE");
        REQUIRE(q->enonce() == "Question texte test");
        REQUIRE(q->reponse() == "Reponse test");

        std::remove(nomFichier.c_str());
    }
}

TEST_CASE("[questionRepertoire] Charger une question de type NUMERIQUE") {
    SUBCASE("La question numerique chargee est correcte") {
        std::string nomFichier = "test_rep_num.txt";
        std::ofstream fichier(nomFichier);
        fichier << "Combien font 5+5 ?\n";
        fichier << "10\n";
        fichier << "0\n";
        fichier << "20\n";
        fichier.close();

        std::ifstream fichierLecture(nomFichier);
        auto q = questionRepertoire::instance().charger(fichierLecture, "NUMERIQUE");
        fichierLecture.close();

        REQUIRE(q->typeQuestion() == "NUMERIQUE");
        REQUIRE(q->enonce() == "Combien font 5+5 ?");
        REQUIRE(q->reponse() == "10");

        std::remove(nomFichier.c_str());
    }

    SUBCASE("La validation des reponses fonctionne correctement") {
        std::string nomFichier = "test_rep_num2.txt";
        std::ofstream fichier(nomFichier);
        fichier << "Combien font 5+5 ?\n";
        fichier << "10\n";
        fichier << "0\n";
        fichier << "20\n";
        fichier.close();

        std::ifstream fichierLecture(nomFichier);
        auto q = questionRepertoire::instance().charger(fichierLecture, "NUMERIQUE");
        fichierLecture.close();

        REQUIRE(q->reponseJuste("10"));
        REQUIRE(q->reponseJuste("15"));
        REQUIRE_FALSE(q->reponseJuste("25"));

        std::remove(nomFichier.c_str());
    }
}

TEST_CASE("[questionRepertoire] Charger une question de type QCM") {
    SUBCASE("La question QCM chargee est correcte") {
        std::string nomFichier = "test_rep_qcm.txt";
        std::ofstream fichier(nomFichier);
        fichier << "Quelle est la couleur du ciel ?\n";
        fichier << "3\n";
        fichier << "Rouge\n";
        fichier << "Vert\n";
        fichier << "Bleu\n";
        fichier << "2\n";
        fichier.close();

        std::ifstream fichierLecture(nomFichier);
        auto q = questionRepertoire::instance().charger(fichierLecture, "QCM");
        fichierLecture.close();

        REQUIRE(q->typeQuestion() == "QCM");
        REQUIRE(q->enonce() == "Quelle est la couleur du ciel ?");
        REQUIRE(q->reponse() == "Bleu");

        std::remove(nomFichier.c_str());
    }

    SUBCASE("La validation des reponses fonctionne correctement") {
        std::string nomFichier = "test_rep_qcm2.txt";
        std::ofstream fichier(nomFichier);
        fichier << "Quelle est la couleur du ciel ?\n";
        fichier << "3\n";
        fichier << "Rouge\n";
        fichier << "Vert\n";
        fichier << "Bleu\n";
        fichier << "2\n";
        fichier.close();

        std::ifstream fichierLecture(nomFichier);
        auto q = questionRepertoire::instance().charger(fichierLecture, "QCM");
        fichierLecture.close();

        REQUIRE(q->reponseJuste("2"));
        REQUIRE_FALSE(q->reponseJuste("0"));

        std::remove(nomFichier.c_str());
    }
}

// Tests des erreurs

TEST_CASE("[questionRepertoire] Charger un type de question inconnu lance une exception") {
    std::string nomFichier = "test_rep_inconnu.txt";
    std::ofstream fichier(nomFichier);
    fichier << "Question test\n";
    fichier.close();

    std::ifstream fichierLecture(nomFichier);
    REQUIRE_THROWS_AS(
        questionRepertoire::instance().charger(fichierLecture, "TYPE_INCONNU"),
        std::runtime_error
    );
    fichierLecture.close();

    std::remove(nomFichier.c_str());
}

// Tests de chargement de plusieurs questions

TEST_CASE("[questionRepertoire] Charger plusieurs questions de types differents") {
    questionRepertoire& rep = questionRepertoire::instance();

    SUBCASE("Charger une question texte puis une question numerique") {
        std::string nomFichier1 = "test_multi_texte.txt";
        std::ofstream f1(nomFichier1);
        f1 << "Question 1\nReponse 1\n";
        f1.close();

        std::ifstream if1(nomFichier1);
        auto q1 = rep.charger(if1, "TEXTE");
        if1.close();

        std::string nomFichier2 = "test_multi_num.txt";
        std::ofstream f2(nomFichier2);
        f2 << "Question 2\n42\n0\n100\n";
        f2.close();

        std::ifstream if2(nomFichier2);
        auto q2 = rep.charger(if2, "NUMERIQUE");
        if2.close();

        REQUIRE(q1->typeQuestion() == "TEXTE");
        REQUIRE(q2->typeQuestion() == "NUMERIQUE");
        REQUIRE(q1->enonce() == "Question 1");
        REQUIRE(q2->enonce() == "Question 2");

        std::remove(nomFichier1.c_str());
        std::remove(nomFichier2.c_str());
    }

    SUBCASE("Charger une question numerique puis une question QCM") {
        std::string nomFichier1 = "test_multi_num2.txt";
        std::ofstream f1(nomFichier1);
        f1 << "Question numerique\n42\n0\n100\n";
        f1.close();

        std::ifstream if1(nomFichier1);
        auto q1 = rep.charger(if1, "NUMERIQUE");
        if1.close();

        std::string nomFichier2 = "test_multi_qcm3.txt";
        std::ofstream f2(nomFichier2);
        f2 << "Question QCM\n2\nChoix A\nChoix B\n1\n";
        f2.close();

        std::ifstream if2(nomFichier2);
        auto q2 = rep.charger(if2, "QCM");
        if2.close();

        REQUIRE(q1->typeQuestion() == "NUMERIQUE");
        REQUIRE(q2->typeQuestion() == "QCM");

        std::remove(nomFichier1.c_str());
        std::remove(nomFichier2.c_str());
    }
}