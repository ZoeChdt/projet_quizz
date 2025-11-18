//
// Created by chzoe on 18/11/2025.
//

#include "questionNumerique.h"
questionNumerique::questionNumerique(const std::string& enonce, int reponse):
    d_enonce{enonce},d_reponse{reponse}
{}

std::string questionNumerique::enonce() const {
    return d_enonce;
}

int questionNumerique::reponse() const {
    return d_reponse;
}

bool questionNumerique::reponseJuste(int reponse) const {
    return d_reponse==reponse;
}