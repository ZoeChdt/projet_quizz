//
// Created by chzoe on 13/12/2025.
//

#include "questionRepertoire.h"
#include "questionNumerique.h"
#include "questionTexte.h"
#include "questionChoixMultiples.h"

questionRepertoire::questionRepertoire() {
    enregistrerPrototypesParDefaut();
}

questionRepertoire& questionRepertoire::instance() {
    static questionRepertoire instance;
    return instance;
}

void questionRepertoire::enregistrer(std::unique_ptr<question> prototype) {
    if (!prototype) {
        throw std::invalid_argument("Le prototype ne peut pas être null");
    }

    std::string type = prototype->typeQuestion();
    d_prototypes[type] = std::move(prototype);
}

std::unique_ptr<question> questionRepertoire::charger(std::ifstream& fichier, const std::string& type) {
    auto it = d_prototypes.find(type);
    if (it == d_prototypes.end()) {
        throw std::runtime_error(
            "Type de question inconnu : '" + type + "'");
    }
    return it->second->chargerDepuisFichier(fichier);
}

void questionRepertoire::enregistrerPrototypesParDefaut() {
    enregistrer(creerPrototypeQuestionNumerique());
    enregistrer(creerPrototypeQuestionTexte());
    enregistrer(creerPrototypeQuestionQCM());
}

std::unique_ptr<question> questionRepertoire::creerPrototypeQuestionNumerique() {
    return std::make_unique<questionNumerique>("", 0, 0, 0);
}

std::unique_ptr<question> questionRepertoire::creerPrototypeQuestionTexte() {
    return std::make_unique<questionTexte>("", "");
}

std::unique_ptr<question> questionRepertoire::creerPrototypeQuestionQCM() {
    return std::make_unique<questionQCM>("", std::vector<std::string>{"A"}, 0);
}