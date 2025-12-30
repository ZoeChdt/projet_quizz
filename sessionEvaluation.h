//
// Created by Aktas Julidè on 30/12/2025.
//

#ifndef PROJET_QUIZZ1_SESSIONEVALUATION_H
#define PROJET_QUIZZ1_SESSIONEVALUATION_H

#include "session.h"
#include "questionnaire.h"
#include <string>

class sessionEvaluation : public session{
    public:
    sessionEvaluation(const questionnaire &q);
    virtual ~sessionEvaluation()=default;
    int nombreEssais() const;
    int nombreQuestionsJustes() const;

    virtual bool transmettreReponse(const std::string &reponse )=0;
    virtual bool afficherBonneReponse()const =0;

    protected:
    int d_nombreQuestionsJustes, d_nombreEssais;
};


#endif //PROJET_QUIZZ1_SESSIONEVALUATION_H