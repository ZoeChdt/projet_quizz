//
// Created by chzoe on 13/12/2025.
//

#ifndef PROJET_QUIZZ_GESTIONNAIRE_H
#define PROJET_QUIZZ_GESTIONNAIRE_H

#include <string>
#include "questionnaire.h"

#include <fstream>
#include <stdexcept>

class gestionnaire {
public:
    void sauvegarder(const questionnaire& q, const std::string& nomFichier);
    questionnaire charger(const std::string& nomFichier);
};

#endif //PROJET_QUIZZ_GESTIONNAIRE_H