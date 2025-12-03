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

int questionNumerique::reponse() const {
    return d_reponse;
}

int questionNumerique::limiteMinimum() const {
    return d_limiteMinimum;
}

int questionNumerique::limiteMaximum() const {
    return d_limiteMaximum;
}

bool questionNumerique::reponseJuste(const std::string &reponse) const {

    return reponse == std::to_string(d_reponse);
}