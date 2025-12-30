//
// Created by Aktas Julidè on 30/12/2025.
//

#ifndef PROJET_QUIZZ1_EVALUATIONTEST_H
#define PROJET_QUIZZ1_EVALUATIONTEST_H
#include "sessionEvaluation.h"


class evaluationTest : public sessionEvaluation{
public:
    evaluationTest(const questionnaire &q);
    bool afficherBonneReponse() const override ;
};


#endif //PROJET_QUIZZ1_EVALUATIONTEST_H