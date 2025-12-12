//
// Created by Kenza Bakadi on 12/12/2025.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "questionnaire.h"
#include "questionTexte.h"
#include "questionNumerique.h"
#include "questionChoixMultiples.h"

// Tests de construction

TEST_CASE("[questionnaire] Le titre est correctement stocké") {
    questionnaire q{"Quizz de geographie"};
    REQUIRE(q.titre()=="Quizz de geographie");
}

TEST_CASE("[questionnaire] Questionnaire vide au départ") {
    questionnaire q{"Questionnaire vide"};
    REQUIRE(q.nombreQuestions()==0);
}

// Tests : ajouterQuestion

TEST_CASE("[questionnaire] Ajouter une question texte") {
    questionnaire q{"Quizz"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Capital de la France ?", "Paris"));
    REQUIRE(q.nombreQuestions()==1);
}

TEST_CASE("[questionnaire] Ajouter plusieurs questions") {
    questionnaire q{"Quizz mixte"};

    q.ajouterQuestion(std::make_unique<questionTexte>("Capital de la France ? ", "Paris"));
    q.ajouterQuestion(std::make_unique<questionNumerique>("Combien de doigts dans une main ?", 5, 0, 10));
    std::vector<std::string> choix{"A", "B","C", "D"};
    q.ajouterQuestion(std::make_unique<questionQCM>("Choix ? ", choix, 1));

    REQUIRE(q.nombreQuestions()==3);
}

// Tests recupererQuestion

TEST_CASE("questionnaire] Recuperer une question texte") {
    questionnaire q{"Quizz"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Capital de la France ?", "Paris"));

    const question& quest = q.recupererQuestion(0);
    REQUIRE(quest.enonce()=="Capital de la France ?");
    REQUIRE(quest.enonce()=="Paris");
}

TEST_CASE("[questionnaire] Recuperer plusieurs question dans l'odre") {
    questionnaire q{"Quizz"};
    q.ajouterQuestion(std::make_unique<questionTexte>("Question 1", "Reponse 1"));
    q.ajouterQuestion(std::make_unique<questionTexte>("Question 2", "Reponse 2"));
    q.ajouterQuestion(std::make_unique<questionTexte>("Question 3", "Reponse 3"));

    REQUIRE(q.recupererQuestion(0).enonce()=="Question 1");
    REQUIRE(q.recupererQuestion(1).enonce()=="Question 2");
    REQUIRE(q.recupererQuestion(2).enonce()=="Question 3");
}

TEST_CASE("[questionnaire] Verifier les reponse des questions") {
    questionnaire q{"Quizz"};

    q.ajouterQuestion(std::make_unique<questionTexte>("Capital de la France ?", "Paris"));
    const question& quest = q.recupererQuestion(0);
    REQUIRE(quest.reponseJuste("Paris"));
    REQUIRE_FALSE(quest.reponseJuste("Londres"));
}