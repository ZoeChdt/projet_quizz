//
// Created by Aktas Julidè on 29/12/2025.
//

#ifndef PROJET_QUIZZ1_SESSIONAPPRENTISSAGE_H
#define PROJET_QUIZZ1_SESSIONAPPRENTISSAGE_H

#include <string>
#include "session.h"
#include "questionnaire.h"

class sessionApprentissage : public session {
public:
    sessionApprentissage(const questionnaire& q);
    std::string reponseCourante() const;


};


#endif //PROJET_QUIZZ1_SESSIONAPPRENTISSAGE_H