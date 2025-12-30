//
// Created by Aktas Julidè on 30/12/2025.
//

#include "sessionEvaluation.h"

sessionEvaluation::sessionEvaluation(const questionnaire &q) :session{q},d_nombreQuestionsJustes{0},d_nombreEssais{0}
{}

int sessionEvaluation::nombreEssais() const {
    return d_nombreEssais;
}

int sessionEvaluation::nombreQuestionsJustes() const {
    return d_nombreQuestionsJustes;
}





