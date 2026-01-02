//
// Created by chzoe on 18/11/2025.
//
#include "gestionnaire.h"
#include "questionnaire.h"
#include "sessionApprentissage.h"
#include "evaluationTest.h"
#include "evaluationSecondeChance.h"
#include "evaluationAdaptative.h"
#include "questionChoixMultiples.h"
#include "question.h"
#include "questionTexte.h"
#include "questionChoixMultiples.h"
#include "questionNumerique.h"

#include <thread>
#include <chrono>

using std::cout;
using std::cin;
using std::string;
using std::endl;

void chargerFichier(questionnaire &q)
{
    gestionnaire g;
    string nom_fichier;

    bool charge = false;

    do {
        cout << "Nom du fichier a charger : ";
        cin >> nom_fichier;

        try {
            q = g.charger(nom_fichier);
            cout << "Questionnaire charge"<<endl;
            charge = true;
        }
        catch (const std::exception& erreur) {
            cout << "Erreur : " << erreur.what() << ""<<endl;
            cout << "Veuillez reessayer."<<endl;
        }

    } while (!charge);
}

void nettoyerBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string lireLigne(const std::string& prompt) {
    std::cout << prompt;
    std::string ligne;
    std::getline(std::cin, ligne);
    return ligne;
}

int lireEntier(const std::string& prompt) {
    int valeur;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valeur) {
            nettoyerBuffer();
            return valeur;
        }
        std::cout << "Entrée invalide. Veuillez entrer un nombre entier.\n";
        nettoyerBuffer();
    }
}

std::unique_ptr<question> creerQuestionTexte() {
    std::cout << "\n=== Creation d'une Question Texte ===\n";

    std::string enonce = lireLigne("Enonce de la question : ");
    std::string reponse = lireLigne("Reponse correcte : ");

    return std::make_unique<questionTexte>(enonce, reponse);
}

std::unique_ptr<question> creerQuestionNumerique() {
    std::cout << "\n=== Creation d'une Question Numerique ===\n";

    std::string enonce = lireLigne("Enonce de la question : ");
    int reponse = lireEntier("Reponse correcte (nombre entier) : ");
    int limiteMin = lireEntier("Limite minimum acceptable : ");
    int limiteMax = lireEntier("Limite maximum acceptable : ");

    try {
        return std::make_unique<questionNumerique>(enonce, reponse, limiteMin, limiteMax);
    } catch (const std::invalid_argument& e) {
        std::cout << "Erreur : " << e.what() << "\n";
        std::cout << "La question n'a pas pu etre creee.\n";
        return nullptr;
    }
}

std::unique_ptr<question> creerQuestionQCM() {
    std::cout << "\n=== Creation d'une Question a Choix Multiples ===\n";

    std::string enonce = lireLigne("Enonce de la question : ");
    int nombreChoix = lireEntier("Nombre de choix possibles : ");

    if (nombreChoix < 2) {
        std::cout << "Erreur : Il faut au moins 2 choix.\n";
        return nullptr;
    }

    std::vector<std::string> choix;
    std::cout << "\nEntrez les choix (un par ligne) :\n";
    for (int i = 0; i < nombreChoix; ++i) {
        std::string choixText = lireLigne("  Choix " + std::to_string(i) + " : ");
        choix.push_back(choixText);
    }

    int numeroReponse = lireEntier("Numero de la bonne reponse (0-" +
                                   std::to_string(nombreChoix - 1) + ") : ");

    try {
        return std::make_unique<questionQCM>(enonce, choix, numeroReponse);
    } catch (const std::invalid_argument& e) {
        std::cout << "Erreur : " << e.what() << "\n";
        std::cout << "La question n'a pas pu etre creee.\n";
        return nullptr;
    }
}

void creerQuestionnaire() {

    std::string titre = lireLigne("Titre du questionnaire : ");
    questionnaire q{titre};

    std::cout << "\nQuestionnaire '" << titre << "' cree.\n";

    bool continuer = true;
    int numeroQuestion = 1;

    while (continuer) {
        std::cout << "\nQuestion #" << numeroQuestion << "\n";
        std::cout << "\nType de question :\n";
        std::cout << "  1. Question Texte\n";
        std::cout << "  2. Question Numerique\n";
        std::cout << "  3. Question a Choix Multiples (QCM)\n";
        std::cout << "  0. Terminer la creation\n";

        int choix = lireEntier("\nVotre choix : ");

        std::unique_ptr<question> nouvelleQuestion = nullptr;

        switch (choix) {
            case 1:
                nouvelleQuestion = creerQuestionTexte();
                break;
            case 2:
                nouvelleQuestion = creerQuestionNumerique();
                break;
            case 3:
                nouvelleQuestion = creerQuestionQCM();
                break;
            case 0:
                continuer = false;
                break;
            default:
                std::cout << "Choix invalide.\n";
                continue;
        }

        if (nouvelleQuestion) {
            q.ajouterQuestion(std::move(nouvelleQuestion));
            std::cout << "\nQuestion ajoutee avec succes!\n";
            numeroQuestion++;
        }
    }
    if (q.nombreQuestions() == 0) {
        std::cout << "\n Aucune question n'a été ajoutee. Le questionnaire ne sera pas sauvegarde.\n";
        return;
    }
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "RESUME DU QUESTIONNAIRE\n";
    std::cout << std::string(50, '=') << "\n";
    std::cout << "Titre : " << q.titre() << "\n";
    std::cout << "Nombre de questions : " << q.nombreQuestions() << "\n\n";

    for (size_t i = 0; i < q.nombreQuestions(); ++i) {
        const question& quest = q.recupererQuestion(i);
        std::cout << "  " << (i + 1) << ". [" << quest.typeQuestion() << "] "
                  << quest.enonce() << "\n";
        std::cout << "     Reponse : " << quest.reponse() << "\n\n";
    }

    std::string nomFichier = lireLigne("Nom du fichier de sauvegarde (ex: quiz.txt) : ");

    if (nomFichier.find(".txt") == std::string::npos) {
        nomFichier += ".txt";
    }
    try {
        gestionnaire g;
        g.sauvegarder(q, nomFichier);
        std::cout << "\nQuestionnaire sauvegarde avec succes dans '" << nomFichier << "'!\n";
    } catch (const std::exception& e) {
        std::cout << "\nErreur lors de la sauvegarde : " << e.what() << "\n";
    }
}


void afficheMenu()
{
    cout<<"Menu"<<endl;
    cout << "A. Charger un autre questionnaire"<<endl;
    cout << "B. Apprentissage"<<endl;
    cout << "C. Evaluation"<<endl;
    cout << "D. Evaluation seconde chance"<<endl;
    cout << "E. Evaluation adaptative"<<endl;
    cout << "F. Creer un questionnaire"<<endl;
    cout << "G. Quitter"<<endl;
    cout << "Choix : ";
}

void afficheChoixSiQCM(const question& questionC) {
    if (questionC.typeQuestion() == "QCM") {
        const questionQCM& qcm = static_cast<const questionQCM&>(questionC);
        for (int i = 0; i < qcm.nombreChoix(); i++) {
            std::cout<<i<<". "<<qcm.choix(i)<< std::endl;
        }
    }
}


void executerSession(sessionEvaluation& eval, const questionnaire& q, const string &typeEval)
{
    while (!eval.estTerminee()) {

        cout << eval.questionCourante().enonce() << endl;
        afficheChoixSiQCM(eval.questionCourante());

        string rep;
        cin >> rep;

        bool juste = eval.transmettreReponse(rep);
        cout << endl;
        if (!juste)
        {
            if (typeEval == "Evaluation simple") {
                cout << eval.reponseCourante() << endl;
            }
            else if (typeEval == "Evaluation seconde chance") {

                if (eval.afficherBonneReponse())
                    cout << "Reponse : " << eval.reponseCourante() <<"\n";
            }
            else if (typeEval == "Evaluation adaptative") {

                if (!eval.afficherBonneReponse())
                    cout << "Mauvaise reponse" << endl;
            }
        }

        if (!eval.estTerminee())
            eval.questionSuivante();
    }

    cout << endl<<"Resultats :" << endl;
    cout << "Questions : " << q.nombreQuestions() << endl;
    cout << "Essais : " << eval.nombreEssais() << endl;
    cout << "Bonnes reponses : " << eval.nombreQuestionsJustes() << endl;
}


void choixMenu()
{
    questionnaire q{"Questionnaire vide"};

    bool quitter = false;
    string typeEval;

    while (!quitter)
    {
        afficheMenu();
        char choix;
        cin >> choix;
        cout<<endl;

        switch (choix)
        {
            case 'A':
                {
                    chargerFichier(q);
                    break;
                }

            case 'B':
                {
                sessionApprentissage sessionApp{q};

                while (!sessionApp.estTerminee()) {
                    const question &questionC = sessionApp.questionCourante();
                    cout << questionC.enonce() <<"\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    cout <<"R?ponse : "<<sessionApp.reponseCourante() <<endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    sessionApp.questionSuivante();
                }
                cout<<endl;

                break;
                }

            case 'C':
                {
                evaluationTest eval{q};
                typeEval = "Evaluation simple";
                executerSession(eval, q, typeEval);
                break;
                }

            case 'D':
                {
                evaluationSecondeChance evalSeconde{q};
                typeEval = "Evaluation seconde chance";
                executerSession(evalSeconde, q, typeEval);
                break;
                }

            case 'E':
                {
                    evaluationAdaptative evalAdapt(q);
                    typeEval = "Evaluation adaptative";
                    executerSession(evalAdapt, q, typeEval);
                     break;
                }
            case 'F':
                creerQuestionnaire();
                break;

            case 'G':
                quitter = true;
                break;

            default:
                cout << "Choix invalide, reessayez."<<endl;
                break;
        }
        cout<<endl;
    }
}

int main()
{
    choixMenu();
    return 0;
}
