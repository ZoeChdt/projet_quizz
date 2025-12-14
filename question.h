//
// Created by chzoe on 18/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTION_H
#define PROJET_QUIZZ_QUESTION_H
#include <iostream>
#include <memory>

class question {
public:
    virtual ~question() = default;
    virtual std::string enonce() const =0;
    virtual std::string reponse() const =0;
    virtual bool reponseJuste(const std::string& reponse) const = 0;
    virtual std::string typeQuestion() const = 0;
    virtual void sauvegarder(std::ofstream& fichier) const = 0;
    virtual std::unique_ptr<question> chargerDepuisFichier(std::ifstream& fichier) const = 0;
};

#endif //PROJET_QUIZZ_QUESTION_H