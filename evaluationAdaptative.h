//
// Created by Aktas Julidè on 01/01/2026.
//

#ifndef PROJET_QUIZZ1_EVALUATIONADAPTATIVE_H
#define PROJET_QUIZZ1_EVALUATIONADAPTATIVE_H
#include "questionnaire.h"
#include "sessionEvaluation.h"


class evaluationAdaptative : public sessionEvaluation{
public:
    evaluationAdaptative(const questionnaire &q);

    void gererEchec() override;

    bool afficherBonneReponse() const override;
};


#endif //PROJET_QUIZZ1_EVALUATIONADAPTATIVE_H