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
#include "question.h"

class questionRepertoire {
public:
    static questionRepertoire& instance();
    void enregistrer(std::unique_ptr<question> prototype);
    std::unique_ptr<question> charger(std::ifstream& fichier, const std::string& type);
private:
    std::map<std::string, std::unique_ptr<question>> d_prototypes;
    questionRepertoire();
    questionRepertoire(const questionRepertoire&) = delete;
    questionRepertoire& operator=(const questionRepertoire&) = delete;
    void enregistrerPrototypesParDefaut();
    std::unique_ptr<question> creerPrototypeQuestionNumerique();
    std::unique_ptr<question> creerPrototypeQuestionTexte();
    std::unique_ptr<question> creerPrototypeQuestionQCM();
};

#endif //PROJET_QUIZZ_QUESTION_REPERTOIRE_H