//
// Created by chzoe on 18/11/2025.
//à
#include "gestionnaire.h"
#include "questionnaire.h"
#include "sessionApprentissage.h"
#include "evaluationTest.h"
#include "evaluationSecondeChance.h"
#include "evaluationAdaptative.h"
#include "questionChoixMultiples.h"
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

void afficheMenu()
{
    cout<<"Menu"<<endl;
    cout << "A. Charger un autre questionnaire"<<endl;
    cout << "B. Apprentissage"<<endl;
    cout << "C. Evaluation"<<endl;
    cout << "D. Evaluation seconde chance"<<endl;
    cout << "E. Evaluation adaptative"<<endl;
    cout << "F. Quitter"<<endl;
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
    chargerFichier(q);


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
                    cout <<"Réponse : "<<sessionApp.reponseCourante() <<endl;
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
