//
// Created by chzoe on 19/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTIONCHOIXMULTIPLES_H
#define PROJET_QUIZZ_QUESTIONCHOIXMULTIPLES_H
#include "question.h"
#include <vector>

class questionQCM : public question {
public:
    questionQCM(const std::string& enonce, const std::vector<std::string>& choix, int reponse);
    std::string enonce() const override;
    int numeroReponse() const;
    int nombreChoix() const;
    std::string reponse() const;
    std::string choix(int i) const;
    bool reponseJuste(const std::string& reponse) const override;
private:
    std::string d_enonce;
    std::vector<std::string> d_choix;
    int d_numeroReponse;
};


#endif //PROJET_QUIZZ_QUESTIONCHOIXMULTIPLES_H