//
// Created by Aktas Julidè on 29/12/2025.
//

#include "session.h"
#include "questionnaire.h"

session::session(const questionnaire &q) : d_questionnaire{q}, d_index{0}
{}

bool session::estTerminee() const {
    return d_index==d_questionnaire.nombreQuestions();
}

const question &session::questionCourante() const {
    size_t indice=d_indices[d_index];
    return d_questionnaire.recupererQuestion(indice);
}

void session::questionSuivante() {
    if (!estTerminee())
        ++d_index;
}


