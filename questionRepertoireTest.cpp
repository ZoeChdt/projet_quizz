//
// Created by chzoe on 22/12/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionRepertoire.h"
#include "questionTexte.h"
#include "questionNumerique.h"
#include "questionChoixMultiples.h"
#include <fstream>

// Fonctions d'assertion de haut niveau
void creerFichierTexte(const std::string& nomFichier, const std::string& enonce, const std::string& reponse) {
    std::ofstream fichier(nomFichier);
    fichier << enonce << "\n" << reponse << "\n";
    fichier.close();
}

void creerFichierNumerique(const std::string& nomFichier, const std::string& enonce, int reponse, int min, int max) {
    std::ofstream fichier(nomFichier);
    fichier << enonce << "\n" << reponse << "\n" << min << "\n" << max << "\n";
    fichier.close();
}

void creerFichierQCM(const std::string& nomFichier, const std::string& enonce, const std::vector<std::string>& choix, int numeroReponse) {
    std::ofstream fichier(nomFichier);
    fichier << enonce << "\n";
    fichier << choix.size() << "\n";
    for (const auto& c : choix) {
        fichier << c << "\n";
    }
    fichier << numeroReponse << "\n";
    fichier.close();
}

std::unique_ptr<question> chargerQuestion(const std::string& nomFichier, const std::string& type) {
    std::ifstream fichier(nomFichier);
    auto q = questionRepertoire::instance().charger(fichier, type);
    fichier.close();
    return q;
}

void supprimerFichier(const std::string& nomFichier) {
    std::remove(nomFichier.c_str());
}

void laQuestionEstDuType(const question& q, const std::string& type) {
    REQUIRE_EQ(q.typeQuestion(), type);
}

void laQuestionALEnonce(const question& q, const std::string& enonce) {
    REQUIRE_EQ(q.enonce(), enonce);
}

void laQuestionALaReponse(const question& q, const std::string& reponse) {
    REQUIRE_EQ(q.reponse(), reponse);
}

void laReponseEstAcceptee(const question& q, const std::string& reponse) {
    REQUIRE(q.reponseJuste(reponse));
}

void laReponseEstRefusee(const question& q, const std::string& reponse) {
    REQUIRE_FALSE(q.reponseJuste(reponse));
}

// Tests du singleton

TEST_CASE("[questionRepertoire] Le singleton fonctionne correctement") {
    SUBCASE("L'instance retourne toujours la même référence") {
        questionRepertoire& rep1 = questionRepertoire::instance();
        questionRepertoire& rep2 = questionRepertoire::instance();
        REQUIRE_EQ(&rep1, &rep2);
    }
}

// Tests de chargement des questions texte

TEST_CASE("[questionRepertoire] Le chargement d'une question texte fonctionne") {
    std::string nomFichier = "test_rep_texte.txt";
    creerFichierTexte(nomFichier, "Question texte test", "Reponse test");

    auto q = chargerQuestion(nomFichier, "TEXTE");

    SUBCASE("Le type est correct") {
        laQuestionEstDuType(*q, "TEXTE");
    }

    SUBCASE("L'énoncé est correct") {
        laQuestionALEnonce(*q, "Question texte test");
    }

    SUBCASE("La réponse est correcte") {
        laQuestionALaReponse(*q, "Reponse test");
    }

    supprimerFichier(nomFichier);
}

// Tests de chargement des questions numériques

TEST_CASE("[questionRepertoire] Le chargement d'une question numérique fonctionne") {
    std::string nomFichier = "test_rep_num.txt";
    creerFichierNumerique(nomFichier, "Combien font 5+5 ?", 10, 0, 20);

    auto q = chargerQuestion(nomFichier, "NUMERIQUE");

    SUBCASE("Les propriétés de base sont correctes") {
        laQuestionEstDuType(*q, "NUMERIQUE");
        laQuestionALEnonce(*q, "Combien font 5+5 ?");
        laQuestionALaReponse(*q, "10");
    }

    SUBCASE("Seule la réponse exacte est acceptée") {
        laReponseEstAcceptee(*q, "10");   // réponse exacte
        laReponseEstRefusee(*q, "15");    // autre valeur dans l'intervalle
        laReponseEstRefusee(*q, "0");     // limite min
        laReponseEstRefusee(*q, "20");    // limite max
    }

    SUBCASE("Les valeurs hors intervalle sont refusées") {
        laReponseEstRefusee(*q, "25");    // au-dessus
        laReponseEstRefusee(*q, "-1");    // en dessous
    }

    supprimerFichier(nomFichier);
}

// Tests de chargement des QCM

TEST_CASE("[questionRepertoire] Le chargement d'un QCM fonctionne") {
    std::string nomFichier = "test_rep_qcm.txt";
    std::vector<std::string> choix{"Rouge", "Vert", "Bleu"};
    creerFichierQCM(nomFichier, "Quelle est la couleur du ciel ?", choix, 2);

    auto q = chargerQuestion(nomFichier, "QCM");

    SUBCASE("Les propriétés de base sont correctes") {
        laQuestionEstDuType(*q, "QCM");
        laQuestionALEnonce(*q, "Quelle est la couleur du ciel ?");
        laQuestionALaReponse(*q, "Bleu");
    }

    SUBCASE("La validation des réponses fonctionne") {
        laReponseEstAcceptee(*q, "2");
        laReponseEstRefusee(*q, "0");
        laReponseEstRefusee(*q, "1");
    }

    supprimerFichier(nomFichier);
}

// Tests de gestion d'erreurs

TEST_CASE("[questionRepertoire] Un type de question inconnu lance une exception") {
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

    supprimerFichier(nomFichier);
}

// Tests de chargement de questions multiples

TEST_CASE("[questionRepertoire] Le chargement de plusieurs questions de types différents fonctionne") {
    SUBCASE("Question texte puis question numérique") {
        std::string nomFichier1 = "test_multi_texte.txt";
        std::string nomFichier2 = "test_multi_num.txt";

        creerFichierTexte(nomFichier1, "Question 1", "Reponse 1");
        creerFichierNumerique(nomFichier2, "Question 2", 42, 0, 100);

        auto q1 = chargerQuestion(nomFichier1, "TEXTE");
        auto q2 = chargerQuestion(nomFichier2, "NUMERIQUE");

        laQuestionEstDuType(*q1, "TEXTE");
        laQuestionEstDuType(*q2, "NUMERIQUE");
        laQuestionALEnonce(*q1, "Question 1");
        laQuestionALEnonce(*q2, "Question 2");

        supprimerFichier(nomFichier1);
        supprimerFichier(nomFichier2);
    }

    SUBCASE("Question numérique puis QCM") {
        std::string nomFichier1 = "test_multi_num2.txt";
        std::string nomFichier2 = "test_multi_qcm.txt";

        creerFichierNumerique(nomFichier1, "Question numerique", 42, 0, 100);
        std::vector<std::string> choix{"Choix A", "Choix B"};
        creerFichierQCM(nomFichier2, "Question QCM", choix, 1);

        auto q1 = chargerQuestion(nomFichier1, "NUMERIQUE");
        auto q2 = chargerQuestion(nomFichier2, "QCM");

        laQuestionEstDuType(*q1, "NUMERIQUE");
        laQuestionEstDuType(*q2, "QCM");

        supprimerFichier(nomFichier1);
        supprimerFichier(nomFichier2);
    }
}

// Tests avec intervalles négatifs

TEST_CASE("[questionRepertoire] Les questions numériques avec limites négatives fonctionnent") {
    std::string nomFichier = "test_rep_negatif.txt";
    creerFichierNumerique(nomFichier, "Temperature en hiver", -10, -20, 5);

    auto q = chargerQuestion(nomFichier, "NUMERIQUE");

    SUBCASE("Les propriétés sont correctes") {
        laQuestionEstDuType(*q, "NUMERIQUE");
        laQuestionALEnonce(*q, "Temperature en hiver");
        laQuestionALaReponse(*q, "-10");
    }

    SUBCASE("Seule la réponse exacte est acceptée") {
        laReponseEstAcceptee(*q, "-10");  // réponse exacte
        laReponseEstRefusee(*q, "-20");   // limite min
        laReponseEstRefusee(*q, "5");     // limite max
        laReponseEstRefusee(*q, "0");     // dans l'intervalle
        laReponseEstRefusee(*q, "-21");   // hors intervalle
        laReponseEstRefusee(*q, "6");     // hors intervalle
    }

    supprimerFichier(nomFichier);
}

// Tests de séquence complexe

TEST_CASE("[questionRepertoire] Le chargement séquentiel de questions complexes fonctionne") {
    questionRepertoire& rep = questionRepertoire::instance();

    std::string fichier1 = "test_seq1.txt";
    std::string fichier2 = "test_seq2.txt";
    std::string fichier3 = "test_seq3.txt";

    creerFichierTexte(fichier1, "Capitale de France ?", "Paris");
    creerFichierNumerique(fichier2, "Combien font 10*10 ?", 100, 50, 150);
    std::vector<std::string> choix{"Rouge", "Vert", "Bleu"};
    creerFichierQCM(fichier3, "Couleur du ciel ?", choix, 2);

    auto q1 = chargerQuestion(fichier1, "TEXTE");
    auto q2 = chargerQuestion(fichier2, "NUMERIQUE");
    auto q3 = chargerQuestion(fichier3, "QCM");

    SUBCASE("Toutes les questions sont du bon type") {
        laQuestionEstDuType(*q1, "TEXTE");
        laQuestionEstDuType(*q2, "NUMERIQUE");
        laQuestionEstDuType(*q3, "QCM");
    }

    SUBCASE("Toutes les questions ont les bons énoncés") {
        laQuestionALEnonce(*q1, "Capitale de France ?");
        laQuestionALEnonce(*q2, "Combien font 10*10 ?");
        laQuestionALEnonce(*q3, "Couleur du ciel ?");
    }

    SUBCASE("Toutes les questions ont les bonnes réponses") {
        laQuestionALaReponse(*q1, "Paris");
        laQuestionALaReponse(*q2, "100");
        laQuestionALaReponse(*q3, "Bleu");
    }

    SUBCASE("Les validations fonctionnent pour tous les type de questions") {
        // Question texte
        laReponseEstAcceptee(*q1, "Paris");
        laReponseEstRefusee(*q1, "Londres");

        // Question numérique - seule la réponse exacte est acceptée
        laReponseEstAcceptee(*q2, "100");
        laReponseEstRefusee(*q2, "120");  // dans l'intervalle mais pas exacte
        laReponseEstRefusee(*q2, "200");  // hors intervalle

        // Question QCM
        laReponseEstAcceptee(*q3, "2");
        laReponseEstRefusee(*q3, "0");
    }

    supprimerFichier(fichier1);
    supprimerFichier(fichier2);
    supprimerFichier(fichier3);
}