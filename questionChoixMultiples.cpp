//
// Created by chzoe on 19/11/2025.
//

#include "questionChoixMultiples.h"

questionQCM::questionQCM(const std::string& enonce, const std::vector<std::string>& choix, int reponse)
    : d_enonce{enonce}, d_choix{choix}, d_numeroReponse{reponse}
{
    validerNumeroReponse();
}

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

    for (char c : s) {
        if (!isdigit(c))
            return false;
    }

    return true;
}

bool questionQCM::reponseJuste(const std::string& reponse) const {
    if (!estEntierPositif(reponse))
        return false;

    int numeroReponse = std::stoi(reponse);
    return numeroReponse == d_numeroReponse;
}

std::string questionQCM::typeQuestion() const {
    return "QCM";
}

void questionQCM::sauvegarder(std::ofstream& fichier) const {
    fichier << typeQuestion() << "\n";
    fichier << d_enonce << "\n";
    fichier << d_choix.size() << "\n";

    for (const auto& c : d_choix) {
        fichier << c << "\n";
    }

    fichier << d_numeroReponse << "\n";
}

std::unique_ptr<question> questionQCM::chargerDepuisFichier(std::ifstream& fichier) const {
    std::string enonce;
    int nbChoix;

    std::getline(fichier, enonce);
    fichier >> nbChoix;
    fichier.ignore();

    std::vector<std::string> choix;
    choix.reserve(nbChoix);

    for (int j = 0; j < nbChoix; ++j) {
        std::string c;
        std::getline(fichier, c);
        choix.push_back(c);
    }

    int numeroReponse;
    fichier >> numeroReponse;
    fichier.ignore();

    return std::make_unique<questionQCM>(enonce, choix, numeroReponse);
}

bool questionQCM::estNumeroValide(int numero) const {
    return (numero >= 0) && (numero < static_cast<int>(d_choix.size()));
}

void questionQCM::validerNumeroReponse() const {
    if (!estNumeroValide(d_numeroReponse)) {
        throw std::invalid_argument("Numéro de réponse invalide");
    }
}