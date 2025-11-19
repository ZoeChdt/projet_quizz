//
// Created by chzoe on 19/11/2025.
//

#include "questionTexte.h"

questionTexte::questionTexte(std::string enonce, std::string reponse):
    d_enonce{enonce},d_reponse{reponse}
{}

std::string questionTexte::enonce() const {
    return d_enonce;
}
std::string questionTexte::reponse() const {
    return d_reponse;
}
bool questionTexte::reponseJuste(const std::string& reponse) const {
    return reponse == d_reponse;
}