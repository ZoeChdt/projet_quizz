//
// Created by Aktas Julidè on 01/01/2026.
//

#include "evaluationAdaptative.h"
#include <algorithm>
#include <random>

evaluationAdaptative::evaluationAdaptative(const questionnaire &q) : sessionEvaluation{q} {
    std::random_device rd;
    std::default_random_engine rg(rd());
    std::shuffle( d_indices.begin(), d_indices.end(),rg);

}

void evaluationAdaptative::gererEchec() {
    size_t indiceQuestionRatee=d_indices[index()];

    d_indices.push_back(indiceQuestionRatee);

}

bool evaluationAdaptative::afficherBonneReponse() const {
    return false;
}



