//
// Created by Aktas Julidè on 30/12/2025.
//

#include "sessionEvaluation.h"

sessionEvaluation::sessionEvaluation(const questionnaire &q) :session{q},d_nombreQuestionsJustes{0},d_nombreEssais{0}
{}

int sessionEvaluation::nombreEssais() const {
    return d_nombreEssais;
}

int sessionEvaluation::nombreQuestionsJustes() const {
    return d_nombreQuestionsJustes;
}

void sessionEvaluation::ajouterQuestionsJustes() {
    ++d_nombreQuestionsJustes;
}

void sessionEvaluation::ajouterEssais() {
    ++d_nombreEssais;
}

void sessionEvaluation::gererSucces()  {

}
void sessionEvaluation::gererEchec() {

}

void sessionEvaluation::comptabiliserBonneReponse() {
    ajouterQuestionsJustes();
    gererSucces();
}

void sessionEvaluation::comptabiliserMauvaiseReponse(){
    gererEchec();
}

bool sessionEvaluation::transmettreReponse(const std::string &reponse) {
    const question& q = questionCourante();
    bool estJuste=q.reponseJuste(reponse);

    ajouterEssais();

    if(estJuste) {
        comptabiliserBonneReponse();
        return true;
    }

    else {
        comptabiliserMauvaiseReponse();
        return false;
    }
}








