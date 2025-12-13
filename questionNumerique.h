//
// Created by chzoe on 18/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTIONNUMERIQUE_H
#define PROJET_QUIZZ_QUESTIONNUMERIQUE_H

#include<fstream>

#include "question.h"

class questionNumerique : public question {
public:
    questionNumerique(std::string  enonce, int reponse, int limiteMin, int limiteMax);
    std::string enonce() const override;
    std::string reponse() const override;
    int reponseNumerique() const;
    int limiteMinimum() const;
    int limiteMaximum() const;
    bool reponseJuste(const std::string& reponse) const override;
    std::string typeQuestion() const override;
    void sauvegarder(std::ofstream& fichier) const override;
    std::unique_ptr<questionNumerique> chargerDepuisFichier(std::ifstream& fichier);
private:
    std::string d_enonce;
    int d_reponse;
    int d_limiteMinimum;
    int d_limiteMaximum;
};


#endif //PROJET_QUIZZ_QUESTIONNUMERIQUE_H