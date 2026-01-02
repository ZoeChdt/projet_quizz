//
// Created by chzoe on 18/11/2025.
//à
#include "gestionnaire.h"
#include "questionnaire.h"
#include "sessionApprentissage.h"
#include "evaluationTest.h"
#include "evaluationSecondeChance.h"
#include "evaluationAdaptative.h"
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
            cout << "Questionnaire charge."<<endl;
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
    cout << "C. Evaluation test"<<endl;
    cout << "D. Evaluation seconde chance"<<endl;
    cout << "E. Evaluation adaptative"<<endl;
    cout << "F. Quitter"<<endl;
    cout << "Choix : ";
}


void executerSession(sessionEvaluation& eval, const questionnaire& q, const string &typeEval)
{
    while (!eval.estTerminee()) {

        cout << eval.questionCourante().enonce() << endl;

        string rep;
        cin >> rep;

        bool juste = eval.transmettreReponse(rep);
        cout << endl;
        if (!juste)
        {
            if (typeEval == "Test simple") {
                cout << eval.reponseCourante() << endl;
            }
            else if (typeEval == "Seconde chance") {

                if (eval.afficherBonneReponse())
                    cout << "Reponse : " << eval.reponseCourante() << endl;
            }
            else if (typeEval == "Adaptatif") {

                if (!eval.afficherBonneReponse())
                    cout << "Mauvaise reponse" << endl;
            }
        }

        if (!eval.estTerminee())
            eval.questionSuivante();
    }

    cout << endl<<"Résultats :" << endl;
    cout << "Questions : " << q.nombreQuestions() << endl;
    cout << "Essais : " << eval.nombreEssais() << endl;
    cout << "Bonnes réponses : " << eval.nombreQuestionsJustes() << endl;
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
                    cout << sessionApp.questionCourante().enonce() <<endl;
                    cout <<"Réponse : "<<sessionApp.reponseCourante() <<endl;
                    sessionApp.questionSuivante();
                }

                break;
                }

            case 'C':
                {
                evaluationTest eval{q};
                typeEval = "Test simple";
                executerSession(eval, q, typeEval);
                break;
                }

            case 'D':
                {
                evaluationSecondeChance evalSeconde{q};
                typeEval = "Seconde chance";
                executerSession(evalSeconde, q, typeEval);
                break;
                }

            case 'E':
                {
                    evaluationAdaptative evalAdapt(q);
                    typeEval = "Adaptatif";
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
