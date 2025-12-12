//
// Created by Kenza Bakadi on 12/12/2025.
//

#include "questionnaire.h"

questionnaire::questionnaire(const std::string &titre) :
    d_titre{titre}, d_questions{}
{}

std::string questionnaire::titre() const {
    return d_titre;
}

void questionnaire::ajouterQuestion(std::unique_ptr<question> q) {
    d_questions.push_back(std::move(q));
}

size_t questionnaire::nombreQuestions() const {
    return d_questions.size();
}

const question &questionnaire::recupererQuestion(size_t index) const {
    return *d_questions[index];
}




