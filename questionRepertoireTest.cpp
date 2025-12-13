//
// Created by chzoe on 13/12/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionRepertoire.h"
#include "questionTexte.h"
#include "questionNumerique.h"
#include "questionChoixMultiples.h"
#include <sstream>

// Tests du singleton

TEST_CASE("[questionRepertoire] Instance retourne toujours le même objet") {
    questionRepertoire& rep1 = questionRepertoire::instance();
    questionRepertoire& rep2 = questionRepertoire::instance();

    REQUIRE(&rep1 == &rep2);
}

// Tests de chargement des questions

TEST_CASE("[questionRepertoire] Charger une question texte") {
    std::stringstream ss;
    ss << "Question texte ?\n";
    ss << "Réponse texte\n";

    std::ifstream fichier;
    // Créer un fichier temporaire
    std::ofstream temp("temp_texte.txt");
    temp << ss.str();
    temp.close();

    fichier.open("temp_texte.txt");
    auto question = questionRepertoire::instance().charger(fichier, "TEXTE");
    fichier.close();

    REQUIRE(question != nullptr);
    REQUIRE(question->typeQuestion() == "TEXTE");
    REQUIRE(question->enonce() == "Question texte ?");
    REQUIRE(question->reponse() == "Réponse texte");

    std::remove("temp_texte.txt");
}

TEST_CASE("[questionRepertoire] Charger une question numérique") {
    std::ofstream temp("temp_num.txt");
    temp << "Combien font 2+2 ?\n";
    temp << "4\n";
    temp << "0\n";
    temp << "10\n";
    temp.close();

    std::ifstream fichier("temp_num.txt");
    auto question = questionRepertoire::instance().charger(fichier, "NUMERIQUE");
    fichier.close();

    REQUIRE(question != nullptr);
    REQUIRE(question->typeQuestion() == "NUMERIQUE");
    REQUIRE(question->enonce() == "Combien font 2+2 ?");
    REQUIRE(question->reponse() == "4");
    REQUIRE(question->reponseJuste("4"));
    REQUIRE(question->reponseJuste("5"));
    REQUIRE_FALSE(question->reponseJuste("15"));

    std::remove("temp_num.txt");
}

TEST_CASE("[questionRepertoire] Charger un QCM") {
    std::ofstream temp("temp_qcm.txt");
    temp << "Quelle est la capitale de France ?\n";
    temp << "3\n";
    temp << "Paris\n";
    temp << "Londres\n";
    temp << "Berlin\n";
    temp << "0\n";
    temp.close();

    std::ifstream fichier("temp_qcm.txt");
    auto question = questionRepertoire::instance().charger(fichier, "QCM");
    fichier.close();

    REQUIRE(question != nullptr);
    REQUIRE(question->typeQuestion() == "QCM");
    REQUIRE(question->enonce() == "Quelle est la capitale de France ?");
    REQUIRE(question->reponse() == "Paris");
    REQUIRE(question->reponseJuste("0"));
    REQUIRE_FALSE(question->reponseJuste("1"));

    std::remove("temp_qcm.txt");
}

// Tests d'enregistrement de prototypes

TEST_CASE("[questionRepertoire] Enregistrer un nouveau prototype") {
    // Créer un prototype personnalisé
    auto prototype = std::make_unique<questionTexte>("", "");
    std::string type = prototype->typeQuestion();

    REQUIRE_NOTHROW(questionRepertoire::instance().enregistrer(std::move(prototype)));

    // Vérifier qu'on peut charger ce type
    std::ofstream temp("temp_enreg.txt");
    temp << "Test enonce\n";
    temp << "Test reponse\n";
    temp.close();

    std::ifstream fichier("temp_enreg.txt");
    auto question = questionRepertoire::instance().charger(fichier, type);
    fichier.close();

    REQUIRE(question != nullptr);
    REQUIRE(question->typeQuestion() == type);

    std::remove("temp_enreg.txt");
}

// Tests d'intégration avec sauvegarde/chargement

TEST_CASE("[questionRepertoire] Sauvegarde et chargement d'une question texte") {
    questionTexte qOriginal{"Question originale ?", "Réponse originale"};

    std::ofstream fichierSortie("temp_integration_texte.txt");
    qOriginal.sauvegarder(fichierSortie);
    fichierSortie.close();

    std::ifstream fichierEntree("temp_integration_texte.txt");
    std::string type;
    std::getline(fichierEntree, type);

    auto qCharge = questionRepertoire::instance().charger(fichierEntree, type);
    fichierEntree.close();

    REQUIRE(qCharge->typeQuestion() == qOriginal.typeQuestion());
    REQUIRE(qCharge->enonce() == qOriginal.enonce());
    REQUIRE(qCharge->reponse() == qOriginal.reponse());

    std::remove("temp_integration_texte.txt");
}

TEST_CASE("[questionRepertoire] Sauvegarde et chargement d'une question numérique") {
    questionNumerique qOriginal{"Combien font 10+5 ?", 15, 10, 20};

    std::ofstream fichierSortie("temp_integration_num.txt");
    qOriginal.sauvegarder(fichierSortie);
    fichierSortie.close();

    std::ifstream fichierEntree("temp_integration_num.txt");
    std::string type;
    std::getline(fichierEntree, type);

    auto qCharge = questionRepertoire::instance().charger(fichierEntree, type);
    fichierEntree.close();

    REQUIRE(qCharge->typeQuestion() == qOriginal.typeQuestion());
    REQUIRE(qCharge->enonce() == qOriginal.enonce());
    REQUIRE(qCharge->reponse() == qOriginal.reponse());
    REQUIRE(qCharge->reponseJuste("15"));
    REQUIRE(qCharge->reponseJuste("18"));
    REQUIRE_FALSE(qCharge->reponseJuste("25"));

    std::remove("temp_integration_num.txt");
}

TEST_CASE("[questionRepertoire] Sauvegarde et chargement d'un QCM") {
    std::vector<std::string> choix{"Rouge", "Vert", "Bleu", "Jaune"};
    questionQCM qOriginal{"Quelle est la couleur du ciel ?", choix, 2};

    std::ofstream fichierSortie("temp_integration_qcm.txt");
    qOriginal.sauvegarder(fichierSortie);
    fichierSortie.close();

    std::ifstream fichierEntree("temp_integration_qcm.txt");
    std::string type;
    std::getline(fichierEntree, type);

    auto qCharge = questionRepertoire::instance().charger(fichierEntree, type);
    fichierEntree.close();

    REQUIRE(qCharge->typeQuestion() == qOriginal.typeQuestion());
    REQUIRE(qCharge->enonce() == qOriginal.enonce());
    REQUIRE(qCharge->reponse() == qOriginal.reponse());
    REQUIRE(qCharge->reponseJuste("2"));
    REQUIRE_FALSE(qCharge->reponseJuste("0"));

    std::remove("temp_integration_qcm.txt");
}

// Tests de robustesse

TEST_CASE("[questionRepertoire] Les prototypes par défaut sont enregistrés") {
    // Les types TEXTE, NUMERIQUE et QCM doivent être disponibles dès le départ
    std::ofstream temp1("temp_default1.txt");
    temp1 << "Test\nReponse\n";
    temp1.close();

    std::ifstream fichier1("temp_default1.txt");
    REQUIRE_NOTHROW(questionRepertoire::instance().charger(fichier1, "TEXTE"));
    fichier1.close();
    std::remove("temp_default1.txt");

    std::ofstream temp2("temp_default2.txt");
    temp2 << "Test\n5\n0\n10\n";
    temp2.close();

    std::ifstream fichier2("temp_default2.txt");
    REQUIRE_NOTHROW(questionRepertoire::instance().charger(fichier2, "NUMERIQUE"));
    fichier2.close();
    std::remove("temp_default2.txt");

    std::ofstream temp3("temp_default3.txt");
    temp3 << "Test\n2\nA\nB\n0\n";
    temp3.close();

    std::ifstream fichier3("temp_default3.txt");
    REQUIRE_NOTHROW(questionRepertoire::instance().charger(fichier3, "QCM"));
    fichier3.close();
    std::remove("temp_default3.txt");
}