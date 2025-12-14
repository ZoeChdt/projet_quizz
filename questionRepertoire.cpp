//
// Created by chzoe on 13/12/2025.
//

#include "questionRepertoire.h"
#include "questionNumerique.h"
#include "questionTexte.h"
#include "questionChoixMultiples.h"

questionRepertoire::questionRepertoire() {
    enregistrer(std::unique_ptr<question>(new questionNumerique("", 0, 0, 0)));
    enregistrer(std::unique_ptr<question>(new questionTexte("", "")));
    enregistrer(std::unique_ptr<question>(new questionQCM("", std::vector<std::string>{"A"}, 0)));
}

questionRepertoire& questionRepertoire::instance() {
    static questionRepertoire instance;
    return instance;
}

void questionRepertoire::enregistrer(std::unique_ptr<question> prototype) {
    std::string type = prototype->typeQuestion();
    d_prototypes[type] = std::move(prototype);
}

std::unique_ptr<question> questionRepertoire::charger(std::ifstream& fichier, const std::string& type) {
    auto it = d_prototypes.find(type);
    if (it == d_prototypes.end()) {
        throw std::runtime_error("Type de question inconnu: " + type);
    }
    return it->second->chargerDepuisFichier(fichier);
}