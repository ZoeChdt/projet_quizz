//
// Created by chzoe on 13/12/2025.
//

#ifndef PROJET_QUIZZ_GESTIONNAIRE_H
#define PROJET_QUIZZ_GESTIONNAIRE_H

#include <string>
#include <memory>
#include "questionnaire.h"
#include "question.h"

class gestionnaire {
public:
    void sauvegarder(const questionnaire& q, const std::string& nomFichier);
    questionnaire charger(const std::string& nomFichier);

private:
    void sauvegarderQuestion(std::ofstream& fichier, const question* q);
    std::unique_ptr<question> chargerQuestion(std::ifstream& fichier, const std::string& type);
};

#endif //PROJET_QUIZZ_GESTIONNAIRE_H