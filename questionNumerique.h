//
// Created by chzoe on 18/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTIONNUMERIQUE_H
#define PROJET_QUIZZ_QUESTIONNUMERIQUE_H
#include <iostream>

#include "question.h"

class questionNumerique : public question {
public:
    questionNumerique(std::string  enonce, int reponse);
    std::string enonce() const override;
    int reponse() const;
    bool reponseJuste(const std::string& reponse) const override;
private:
    std::string d_enonce;
    int d_reponse;
};


#endif //PROJET_QUIZZ_QUESTIONNUMERIQUE_H