//
// Created by chzoe on 13/12/2025.
//

#ifndef PROJET_QUIZZ_QUESTION_REPERTOIRE_H
#define PROJET_QUIZZ_QUESTION_REPERTOIRE_H

#include <map>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include "gestionnaire.h"
#include "question.h"

class questionRepertoire {
public:
    static questionRepertoire& instance();
    void enregistrer(std::unique_ptr<question> prototype);
    std::unique_ptr<question> charger(std::ifstream& fichier, const std::string& type);
private:
    std::map<std::string, std::unique_ptr<question>> d_prototypes;
    questionRepertoire();
};

#endif //PROJET_QUIZZ_QUESTION_REPERTOIRE_H