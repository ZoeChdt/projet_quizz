//
// Created by chzoe on 13/12/2025.
//

#ifndef PROJET_QUIZZ_GESTIONNAIRE_H
#define PROJET_QUIZZ_GESTIONNAIRE_H

#include <string>
#include <fstream>
#include <stdexcept>
#include "questionnaire.h"

class gestionnaire {
public:
    void sauvegarder(const questionnaire& q, const std::string& nomFichier);
    questionnaire charger(const std::string& nomFichier);
private:
    void verifierOuvertureFichierEcriture(const std::ofstream& fichier, const std::string& nomFichier) const;
    void verifierOuvertureFichierLecture(const std::ifstream& fichier,const std::string& nomFichier) const;
    void ecrireEnTete(std::ofstream& fichier, const questionnaire& q) const;
    void ecrireQuestions(std::ofstream& fichier, const questionnaire& q) const;
    std::string lireTitre(std::ifstream& fichier) const;
    size_t lireNombreQuestions(std::ifstream& fichier) const;
    void chargerQuestions(std::ifstream& fichier, questionnaire& q, size_t nbQuestions) const;
};

#endif //PROJET_QUIZZ_GESTIONNAIRE_H