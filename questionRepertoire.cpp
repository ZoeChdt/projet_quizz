//
// Created by chzoe on 13/12/2025.
//

#include "questionRepertoire.h"

void gestionnaire::sauvegarder(const questionnaire& q, const std::string& nomFichier) {
    std::ofstream fichier(nomFichier);
    if (!fichier) {
        std::cout<<("Impossible d'ouvrir le fichier pour l'écriture");
        return 0;
    }
    else {
        fichier << q.titre() << "\n";
        fichier << q.nombreQuestions() << "\n";

        for (size_t i = 0; i < q.nombreQuestions(); ++i) {
            const question& quest = q.recupererQuestion(i);
            quest.sauvegarder(fichier);
        }
    }
    fichier.close();
}

questionnaire gestionnaire::charger(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);
    if (!fichier) {
        std::cout<<("Impossible d'ouvrir le fichier pour l'écriture");
        return 0;
    }
    else {
        std::string titre;
        std::getline(fichier, titre);

        questionnaire q(titre);

        size_t nbQuestions;
        fichier >> nbQuestions;
        fichier.ignore();

        for (size_t i = 0; i < nbQuestions; ++i) {
            std::string type;
            std::getline(fichier, type);

            auto quest = questionRepertoire::instance().charger(fichier, type);
            if (quest) {
                q.ajouterQuestion(std::move(quest));
            }
        }
        fichier.close();
        return q;
    }
}