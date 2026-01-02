//
// Created by chzoe on 18/11/2025.
//

#include "questionNumerique.h"
#include <utility>

questionNumerique::questionNumerique(std::string enonce, int reponse, int limiteMin, int limiteMax)
    : d_enonce{std::move(enonce)},
      d_reponse{reponse},
      d_limiteMinimum{limiteMin},
      d_limiteMaximum{limiteMax}
{
    validerLimites();
    validerReponse();
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

    size_t debut = (s[0] == '-') ? 1 : 0;

    for (size_t i = debut; i < s.length(); ++i) {
        if (!isdigit(s[i]))
            return false;
    }

    return debut < s.length();
}

bool questionNumerique::reponseJuste(const std::string &reponse) const {
    if (!estEntier(reponse))
        return false;
    int valeur = std::stoi(reponse);
    if (!estDansIntervalle(valeur)) 
        return false;
    return valeur == d_reponse;
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
    std::string enonce, reponseStr, limMinStr, limMaxStr;
    std::getline(fichier, enonce);
    std::getline(fichier, reponseStr);
    std::getline(fichier, limMinStr);
    std::getline(fichier, limMaxStr);
    int reponse = std::stoi(reponseStr);
    int limMin = std::stoi(limMinStr);
    int limMax = std::stoi(limMaxStr);
    return std::unique_ptr<question>(new questionNumerique(enonce, reponse, limMin, limMax));
}

bool questionNumerique::estDansIntervalle(int valeur) const {
    return (valeur >= d_limiteMinimum) && (valeur <= d_limiteMaximum);
}

void questionNumerique::validerLimites() const {
    if (d_limiteMinimum > d_limiteMaximum) {
        throw std::invalid_argument("limiteMinimum > limiteMaximum");
    }
}

void questionNumerique::validerReponse() const {
    if (!estDansIntervalle(d_reponse)) {
        throw std::invalid_argument("Réponse hors limites");
    }
}
