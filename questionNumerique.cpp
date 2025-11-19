//
// Created by chzoe on 18/11/2025.
//

#include "questionNumerique.h"

#include <utility>
questionNumerique::questionNumerique(std::string  enonce, int reponse):
    d_enonce{std::move(enonce)},d_reponse{reponse}
{}

std::string questionNumerique::enonce() const {
    return d_enonce;
}

int questionNumerique::reponse() const {
    return d_reponse;
}

bool questionNumerique::reponseJuste(const std::string &reponse) const {

    return reponse == std::to_string(d_reponse);
}