//
// Created by chzoe on 18/11/2025.
//

#include "questionNumerique.h"

#include <utility>
questionNumerique::questionNumerique(std::string  enonce, int reponse, int limiteMin, int limiteMax):
    d_enonce{std::move(enonce)},d_reponse{reponse}, d_limiteMinimum{limiteMin}, d_limiteMaximum{limiteMax}
{
    if (d_limiteMinimum > d_limiteMaximum)
        throw std::invalid_argument("limiteMinimum > limiteMaximum");
    if (d_reponse < d_limiteMinimum || d_reponse > d_limiteMaximum)
        throw std::invalid_argument("Réponse hors limites");
}

std::string questionNumerique::enonce() const {
    return d_enonce;
}

std::string questionNumerique::reponse() const {
    return std::to_string(d_reponse);
}

int questionNumerique::reponseNumerique() const {
    return d_reponse;
}

int questionNumerique::limiteMinimum() const {
    return d_limiteMinimum;
}

int questionNumerique::limiteMaximum() const {
    return d_limiteMaximum;
}

bool estEntier(const std::string &s) {
    if (s.empty())
        return false;
    else {
        size_t j = 0;
        if (s[0]== '-')
            j = 1;
        for (size_t i = j; i < s.length(); ++i)
            if (!isdigit(s[i]))
                return false;
    }
    return true;
}

bool questionNumerique::reponseJuste(const std::string &reponse) const {

    if (!estEntier(reponse))
        return false;
    int valeur = std::stoi(reponse); //la chaîne est un entier
    return (valeur >= d_limiteMinimum) && (valeur <= d_limiteMaximum);
}

std::string questionNumerique::typeQuestion() const {
    return "NUMERIQUE";
}

void questionNumerique::sauvegarder(std::ofstream& fichier) const {
    fichier << typeQuestion() << "\n";
    fichier << d_enonce << "\n";
    fichier << d_reponse << "\n";
    fichier << d_limiteMinimum << "\n";
    fichier << d_limiteMaximum << "\n";
}

std::unique_ptr<question> questionNumerique::chargerDepuisFichier(std::ifstream& fichier) const {
    std::string enonce;
    int reponse, limMin, limMax;
    std::getline(fichier, enonce);
    fichier >> reponse >> limMin >> limMax;
    fichier.ignore();
    return std::unique_ptr<question>(new questionNumerique(enonce, reponse, limMin, limMax));
}