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

bool estEntierPositif(const std::string &s) {
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.length(); ++i)
        if (!isdigit(s[i]))
            return false;
    return true;
}

bool questionQCM::reponseJuste(const std::string& reponse) const {
    if (!estEntierPositif(reponse))
        return false;
    int rep = std::stoi(reponse);
    return rep == d_numeroReponse;
}