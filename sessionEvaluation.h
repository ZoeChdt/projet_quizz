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

    void ajouterQuestionsJustes();
    void ajouterEssais();

    bool transmettreReponse(const std::string &reponse );

    void comptabiliserBonneReponse();
    void comptabiliserMauvaiseReponse();

    virtual void gererSucces();
    virtual void gererEchec();

    virtual bool afficherBonneReponse()const =0;

    private:
    int d_nombreQuestionsJustes, d_nombreEssais;
};


#endif //PROJET_QUIZZ1_SESSIONEVALUATION_H