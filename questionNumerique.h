//
// Created by chzoe on 18/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTIONNUMERIQUE_H
#define PROJET_QUIZZ_QUESTIONNUMERIQUE_H
#include <iostream>

#include "question.h"

class questionNumerique : public question {
public:
    questionNumerique(std::string  enonce, int reponse, int limiteMin, int limiteMax);
    std::string enonce() const override;
    int reponse() const;
    int limiteMinimum() const;
    int limiteMaximum() const;
    bool reponseJuste(const std::string& reponse) const override;
private:
    std::string d_enonce;
    int d_reponse;
    int d_limiteMinimum;
    int d_limiteMaximum;
};


#endif //PROJET_QUIZZ_QUESTIONNUMERIQUE_H