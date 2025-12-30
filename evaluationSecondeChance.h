//
// Created by Aktas Julidè on 30/12/2025.
//

#ifndef PROJET_QUIZZ1_EVALUATIONSECONDE_H
#define PROJET_QUIZZ1_EVALUATIONSECONDE_H
#include "sessionEvaluation.h"


class evaluationSecondeChance : public sessionEvaluation{
public:
    evaluationSecondeChance(const questionnaire &q);
    void gererSucces()  override;
    void gererEchec()  override;
    bool afficherBonneReponse() const override;
    void questionSuivante() override;

private:
    bool d_secondeChance;
};


#endif //PROJET_QUIZZ1_EVALUATIONSECONDE_H