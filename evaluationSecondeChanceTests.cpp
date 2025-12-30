//
// Created by Aktas Julidè on 30/12/2025.
//

#include "doctest.h"
#include "evaluationSecondeChance.h"
#include "questionnaire.h"
#include "questionNumerique.h"
#include "questionTexte.h"

TEST_CASE("[evaluationSecondeChance] la classe est correctement implémentée") {
    questionnaire q{"Questionnaire test"};
    q.ajouterQuestion(std::make_unique<questionTexte> ("Quelle est la capitale de la France ?","Paris"));
    q.ajouterQuestion(std::make_unique<questionNumerique> ("2+2",4,0,10));

    evaluationSecondeChance e {q};

    SUBCASE("Bonne réponse au premier essai") {
        e.transmettreReponse("Paris");
        SUBCASE("Le nombre de questions justes augmente") {
            REQUIRE_EQ(e.nombreQuestionsJustes(),1);
        }
        SUBCASE("Le nombre d'essais augmente ") {
            REQUIRE_EQ(e.nombreEssais(),1);
        }
        SUBCASE("Le passage à la question suivante est possible") {
            e.questionSuivante();
            REQUIRE_EQ(e.questionCourante().enonce(),"2+2");
        }
    }

    SUBCASE("Bonne réponse au deuxième essai (usage de la deuxième chance)") {
        e.transmettreReponse("Madrid");
        SUBCASE("Le nombre de questions justes est inchangé") {
            REQUIRE_EQ(e.nombreQuestionsJustes(),0);
        }
        SUBCASE("Le nombre d'essais augmente ") {
            REQUIRE_EQ(e.nombreEssais(),1);
        }
        SUBCASE("Le passage à la question suivante n'est pas possible") {
            e.questionSuivante();
            REQUIRE_EQ(e.questionCourante().enonce(),"Quelle est la capitale de la France ?");
        }

        e.transmettreReponse("Paris");
        SUBCASE("Le nombre de questions justes augmente") {
            REQUIRE_EQ(e.nombreQuestionsJustes(),1);
        }
        SUBCASE("Le nombre d'essais augmente ") {
            REQUIRE_EQ(e.nombreEssais(),2);
        }
        SUBCASE("Le passage à la question suivante est possible") {
            e.questionSuivante();
            REQUIRE_EQ(e.questionCourante().enonce(),"2+2");
        }


    }

    SUBCASE("La bonne réponse n'est pas trouvé au bout de 2 essais") {
        e.transmettreReponse("Madrid");
        e.transmettreReponse("Rome");
        SUBCASE("Le nombre de questions justes est inchangé") {
            REQUIRE_EQ(e.nombreQuestionsJustes(),0);
        }
        SUBCASE("Le nombre d'essais augmente ") {
            REQUIRE_EQ(e.nombreEssais(),2);
        }
        SUBCASE("La bonne réponse doit pouvoir être affichée") {
            REQUIRE_EQ(e.afficherBonneReponse(),true);
        }
        SUBCASE("Le passage à la question suivante est possible") {
            e.questionSuivante();
            REQUIRE_EQ(e.questionCourante().enonce(),"2+2");
        }
    }
}