//
// Created by chzoe on 19/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTIONTEXTE_H
#define PROJET_QUIZZ_QUESTIONTEXTE_H
#include<fstream>

#include "question.h"

class questionTexte : public question {
public:
    questionTexte(std::string enonce, std::string reponse);
    std::string enonce() const override;
    std::string reponse() const override;
    bool reponseJuste(const std::string& reponse) const override;
    std::string typeQuestion() const override;
    void sauvegarder(std::ofstream& fichier) const override;
    std::unique_ptr<questionTexte> chargerDepuisFichier(std::ifstream& fichier);

private:
    std::string d_enonce;
    std::string d_reponse;
};


#endif //PROJET_QUIZZ_QUESTIONTEXTE_H