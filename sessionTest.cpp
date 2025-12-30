//
// Created by Aktas Julidè on 30/12/2025.
//
#include "doctest.h"
#include "session.h"
#include "questionnaire.h"
#include "questionNumerique.h"
#include "questionTexte.h"


TEST_CASE("[session] la classe est correctement implémentée") {
    questionnaire q{"questionnaire de test"};
    q.ajouterQuestion(std::make_unique<questionNumerique>("2+2",4,0,20));
    q.ajouterQuestion(std::make_unique<questionTexte> ("Quelle est la capitale de la France ?","Paris"));
    session s{q};

    SUBCASE("L'initialisation des indices est correctement effectuée") {
        REQUIRE_EQ(s.nombreIndices(),2);
        REQUIRE_EQ(s.indiceNumero(0),0);
        REQUIRE_EQ(s.indiceNumero(1),1);
    }

    SUBCASE("L'index retourné est correct") {
        REQUIRE_EQ(s.index(),0);
    }
    SUBCASE("La question courante retournée est correcte") {
        REQUIRE_EQ(s.questionCourante().enonce(),q.recupererQuestion(0).enonce());
    }
    SUBCASE("La réponse courante retournée est correcte") {
        REQUIRE_EQ(s.reponseCourante(),q.recupererQuestion(0).reponse());
    }
    SUBCASE("Le passage à la question suivante fonctionne") {
        s.questionSuivante();
        REQUIRE_EQ(s.index(),1);
    }

    SUBCASE("La méthode estTerminee fonctionne correctement") {
        SUBCASE("La session n'est pas terminée au départ") {
            REQUIRE_EQ(s.estTerminee(),false);
        }
        SUBCASE("La session n'est pas terminée pendant son déroulement") {
            s.questionSuivante();
            REQUIRE_EQ(s.estTerminee(),false);
        }
        SUBCASE("La session est terminée une fois toutes les questions passées") {
            s.questionSuivante();
            s.questionSuivante();
            REQUIRE_EQ(s.estTerminee(),true);
        }
    }
}





