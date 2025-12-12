//
// Created by Kenza Bakadi on 12/12/2025.
//

#ifndef PROJET_QUIZZ_QUESTIONNAIRE_H
#define PROJET_QUIZZ_QUESTIONNAIRE_H

#include <string>
#include <vector>
#include "question.h"

class questionnaire {
    public:
    explicit questionnaire(const std::string &titre);
    std::string titre() const;
    void ajouterQuestion(std::unique_ptr<question> q);
    size_t nombreQuestions() const;
    const question& recupererQuestion(size_t index) const;
    private:
    std::string d_titre;
    std::vector<std::unique_ptr<question>> d_questions;
};


#endif //PROJET_QUIZZ_QUESTIONNAIRE_H