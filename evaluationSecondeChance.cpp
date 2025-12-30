//
// Created by Aktas Julidè on 30/12/2025.
//

#include "evaluationSecondeChance.h"

evaluationSecondeChance::evaluationSecondeChance(const questionnaire &q) : sessionEvaluation{q},d_secondeChance{false}
{}

void evaluationSecondeChance::gererSucces() {
    d_secondeChance = false;
}

void evaluationSecondeChance::gererEchec() {
    d_secondeChance = !d_secondeChance;
}

bool evaluationSecondeChance::afficherBonneReponse() const{
    return !d_secondeChance;
}

void evaluationSecondeChance::questionSuivante() {
    if (!d_secondeChance) {
        session::questionSuivante();
    }
}




