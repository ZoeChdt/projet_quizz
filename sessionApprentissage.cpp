//
// Created by Aktas Julidè on 29/12/2025.
//

#include "sessionApprentissage.h"
#include "questionnaire.h"
#include <string>

sessionApprentissage::sessionApprentissage(const questionnaire &q): d_questionnaire{q}, d_index{0}
{}

size_t sessionApprentissage::index() const {
    return d_index;
}

bool sessionApprentissage::estTerminee() const {
    return d_index==d_questionnaire.nombreQuestions();
}

const question &sessionApprentissage::questionCourante() const {
    return d_questionnaire.recupererQuestion(d_index);
}

std::string sessionApprentissage::reponseCourante() const {
    return questionCourante().reponse();
}

void sessionApprentissage::questionSuivante() {
    if (!estTerminee())
        ++d_index;
}



