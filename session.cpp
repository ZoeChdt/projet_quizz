//
// Created by Aktas Julidè on 29/12/2025.
//

#include "session.h"
#include "questionnaire.h"
#include <vector>

session::session(const questionnaire &q) : d_questionnaire{q}, d_index{0}
{
    for (size_t i=0;i<d_questionnaire.nombreQuestions();++i)
        d_indices.push_back(i);
}

bool session::estTerminee() const {
    return d_index==d_indices.size();
}

const question &session::questionCourante() const {
    size_t indice=d_indices[d_index];
    return d_questionnaire.recupererQuestion(indice);
}

std::string session::reponseCourante() const {
    return questionCourante().reponse();
}

void session::questionSuivante() {
    if (!estTerminee())
        ++d_index;
}

size_t session::nombreIndices () const {
    return d_indices.size();
}

size_t session::indiceNumero(size_t i) const {
    return d_indices[i];
}

size_t session::index() const {
    return d_index;
}



