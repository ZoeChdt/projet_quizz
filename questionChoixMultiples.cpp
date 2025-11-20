//
// Created by chzoe on 19/11/2025.
//

#include "questionChoixMultiples.h"

questionQCM::questionQCM(const std::string& enonce, const std::vector<std::string>& choix,int reponse):
    d_enonce{enonce}, d_choix{choix}, d_numeroReponse{reponse}
{}

std::string questionQCM::enonce() const {
    return d_enonce;
}

int questionQCM::numeroReponse() const {
    return d_numeroReponse;
}

std::string questionQCM::reponse() const {
    return d_choix[d_numeroReponse];
}

int questionQCM::nombreChoix() const {
    return d_choix.size();
}

std::string questionQCM::choix(int i) const {
    return d_choix[i];
}

bool questionQCM::reponseJuste(const std::string& reponse) const {
    return std::stoi(reponse) == d_numeroReponse;
}