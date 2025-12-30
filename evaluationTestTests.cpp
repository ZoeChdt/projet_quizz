//
// Created by Aktas Julidè on 30/12/2025.
//

#include "doctest.h"
#include "evaluationTest.h"
#include "questionnaire.h"
#include "questionNumerique.h"
#include "questionTexte.h"

TEST_CASE("[evaluationTest] la classe est correctement implémentée") {
    questionnaire q{"Questionnaire test"};
    q.ajouterQuestion(std::make_unique<questionTexte> ("Quelle est la capitale de la France ?","Paris"));

    evaluationTest e {q};

    SUBCASE("En cas de bonne réponse") {
        e.transmettreReponse("Paris");
        SUBCASE("Le nombre de questions justes augmente") {
            REQUIRE_EQ(e.nombreQuestionsJustes(),1);
        }
        SUBCASE("Le nombre d'essais augmente ") {
            REQUIRE_EQ(e.nombreEssais(),1);
        }
        SUBCASE("La bonne réponse n'est pas affichée") {
            REQUIRE_FALSE(e.afficherBonneReponse());
        }
    }

    SUBCASE("En cas de mauvaise réponse") {
        e.transmettreReponse("Rome");
        SUBCASE("Le nombre de questions justes est inchangé") {
            REQUIRE_EQ(e.nombreQuestionsJustes(),0);
        }
        SUBCASE("Le nombre d'essais augmente ") {
            REQUIRE_EQ(e.nombreEssais(),1);
        }
        SUBCASE("La bonne réponse n'est pas affichée") {
            REQUIRE_FALSE(e.afficherBonneReponse());
        }
    }
}