//
// Created by chzoe on 13/12/2025.
//
#include "gestionnaire.h"
#include "questionRepertoire.h"

void gestionnaire::sauvegarder(const questionnaire& q,const std::string& nomFichier) {
    std::ofstream fichier(nomFichier);
    verifierOuvertureFichierEcriture(fichier, nomFichier);
    ecrireEnTete(fichier, q);
    ecrireQuestions(fichier, q);
    fichier.close();
}

questionnaire gestionnaire::charger(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    verifierOuvertureFichierLecture(fichier, nomFichier);
    std::string titre = lireTitre(fichier);
    questionnaire q(titre);
    size_t nbQuestions = lireNombreQuestions(fichier);
    chargerQuestions(fichier, q, nbQuestions);
    fichier.close();
    return q;
}

void gestionnaire::verifierOuvertureFichierEcriture(const std::ofstream& fichier, const std::string& nomFichier) const {
    if (!fichier) {
        throw std::runtime_error(
            "Impossible d'ouvrir le fichier '" + nomFichier +
            "' pour l'écriture");
    }
}

void gestionnaire::verifierOuvertureFichierLecture(const std::ifstream& fichier, const std::string& nomFichier) const {
    if (!fichier) {
        throw std::runtime_error(
            "Impossible d'ouvrir le fichier '" + nomFichier +
            "' pour la lecture");
    }
}

void gestionnaire::ecrireEnTete(std::ofstream& fichier, const questionnaire& q) const {
    fichier << q.titre() << "\n";
    fichier << q.nombreQuestions() << "\n";
}

void gestionnaire::ecrireQuestions(std::ofstream& fichier, const questionnaire& q) const {
    for (size_t i = 0; i < q.nombreQuestions(); ++i) {
        const question& quest = q.recupererQuestion(i);
        quest.sauvegarder(fichier);
    }
}

std::string gestionnaire::lireTitre(std::ifstream& fichier) const {
    std::string titre;
    std::getline(fichier, titre);
    return titre;
}

size_t gestionnaire::lireNombreQuestions(std::ifstream& fichier) const {
    size_t nbQuestions;
    fichier >> nbQuestions;
    fichier.ignore();
    return nbQuestions;
}

void gestionnaire::chargerQuestions(std::ifstream& fichier, questionnaire& q, size_t nbQuestions) const {
    for (size_t i = 0; i < nbQuestions; ++i) {
        std::string type;
        std::getline(fichier, type);

        auto quest = questionRepertoire::instance().charger(fichier, type);
        if (quest) {
            q.ajouterQuestion(std::move(quest));
        }
    }
}