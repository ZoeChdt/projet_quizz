//
// Created by chzoe on 13/12/2025.
//

#include "gestionnaire.h"
#include "questionTexte.h"
#include "questionNumerique.h"
#include "questionChoixMultiples.h"
#include <fstream>
#include <stdexcept>

void gestionnaire::sauvegarder(const questionnaire& q, const std::string& nomFichier) {
    std::ofstream fichier(nomFichier);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour l'écriture");
    }
    fichier << q.titre() << "\n";
    fichier << q.nombreQuestions() << "\n";
    for (size_t i = 0; i < q.nombreQuestions(); ++i) {
        const question& quest = q.recupererQuestion(i);
        sauvegarderQuestion(fichier, &quest);
    }

    fichier.close();
}

void gestionnaire::sauvegarderQuestion(std::ofstream& fichier, const question* q) {
    if (auto qTexte = dynamic_cast<const questionTexte*>(q)) {
        fichier << "TEXTE\n";
        fichier << qTexte->enonce() << "\n";
        fichier << qTexte->reponse() << "\n";
    }
    else if (auto qNum = dynamic_cast<const questionNumerique*>(q)) {
        fichier << "NUMERIQUE\n";
        fichier << qNum->enonce() << "\n";
        fichier << qNum->reponseNumerique() << "\n";
        fichier << qNum->limiteMinimum() << "\n";
        fichier << qNum->limiteMaximum() << "\n";
    }
    else if (auto qQCM = dynamic_cast<const questionQCM*>(q)) {
        fichier << "QCM\n";
        fichier << qQCM->enonce() << "\n";
        fichier << qQCM->nombreChoix() << "\n";
        for (int i = 0; i < qQCM->nombreChoix(); ++i) {
            fichier << qQCM->choix(i) << "\n";
        }
        fichier << qQCM->numeroReponse() << "\n";
    }
    else {
        throw std::runtime_error("Type de question inconnu");
    }
}

questionnaire gestionnaire::charger(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour la lecture");
    }

    std::string titre;
    std::getline(fichier, titre);

    questionnaire q(titre);

    size_t nbQuestions;
    fichier >> nbQuestions;
    fichier.ignore();

    for (size_t i = 0; i < nbQuestions; ++i) {
        std::string type;
        std::getline(fichier, type);

        auto quest = chargerQuestion(fichier, type);
        if (quest) {
            q.ajouterQuestion(std::move(quest));
        }
    }

    fichier.close();
    return q;
}

std::unique_ptr<question> gestionnaire::chargerQuestion(std::ifstream& fichier, const std::string& type) {
    if (type == "TEXTE") {
        std::string enonce, reponse;
        std::getline(fichier, enonce);
        std::getline(fichier, reponse);
        return std::make_unique<questionTexte>(enonce, reponse);
    }
    else if (type == "NUMERIQUE") {
        std::string enonce;
        int reponse, limMin, limMax;
        std::getline(fichier, enonce);
        fichier >> reponse >> limMin >> limMax;
        fichier.ignore();
        return std::make_unique<questionNumerique>(enonce, reponse, limMin, limMax);
    }
    else if (type == "QCM") {
        std::string enonce;
        int nbChoix;
        std::getline(fichier, enonce);
        fichier >> nbChoix;
        fichier.ignore();

        std::vector<std::string> choix;
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
    else {
        throw std::runtime_error("Type de question inconnu: " + type);
    }
}