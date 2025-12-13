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

std::string questionTexte::typeQuestion() const {
    return "TEXTE";
}

void questionTexte::sauvegarder(std::ofstream& fichier) const{
    fichier << typeQuestion() << "\n";
    fichier << d_enonce << "\n";
    fichier << d_reponse << "\n";
}

std::unique_ptr<questionTexte> questionTexte::chargerDepuisFichier(std::ifstream& fichier) {
    std::string enonce, reponse;
    std::getline(fichier, enonce);
    std::getline(fichier, reponse);
    return std::make_unique<questionTexte>(enonce, reponse);
}