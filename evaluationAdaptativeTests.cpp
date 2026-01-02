//
// Created by Aktas Julidè on 01/01/2026.
//

#include "doctest.h"
#include "evaluationAdaptative.h"
#include "questionnaire.h"
#include "questionTexte.h"

TEST_CASE("[evaluationAdaptative] La classe est correctement implémentéé") {
    questionnaire q{"Questionnaire test"};
    q.ajouterQuestion(std::make_unique<questionTexte> ("Quelle est la capitale de la France ?","Paris"));
    q.ajouterQuestion(std::make_unique<questionTexte> ("Quelle est la capitale de l'Allemagne ?","Berlin"));

    evaluationAdaptative e{q};

    SUBCASE("En cas d'erreur, la question est reposée") {
        size_t tailleInitiale = e.nombreIndices();
        e.transmettreReponse("Rome");
        SUBCASE("Le nombre d'indices augmente") {
            REQUIRE_EQ(tailleInitiale,2);
            REQUIRE_EQ(e.nombreIndices(),3);
        }
        SUBCASE("La question échouée se retrouve à la fin du vecteur d'indices") {
            std::string questionRateeEnonce =e.questionCourante().enonce();
            e.questionSuivante();
            e.transmettreReponse(e.reponseCourante());
            e.questionSuivante();
            REQUIRE_EQ(e.questionCourante().enonce(),questionRateeEnonce);
        }
        }
    SUBCASE("La session se termine lorsque toutes les réponses données sont justes") {
        e.transmettreReponse("Rome");
        REQUIRE_FALSE(e.estTerminee());
        e.questionSuivante();
        e.transmettreReponse(e.reponseCourante());
        REQUIRE_FALSE(e.estTerminee());
        e.questionSuivante();
        e.transmettreReponse(e.reponseCourante());
        e.questionSuivante();
        REQUIRE(e.estTerminee());
    }



}