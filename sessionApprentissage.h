//
// Created by Aktas Julidè on 29/12/2025.
//

#ifndef PROJET_QUIZZ1_SESSIONAPPRENTISSAGE_H
#define PROJET_QUIZZ1_SESSIONAPPRENTISSAGE_H

#include <string>
#include "questionnaire.h"

class sessionApprentissage {
public:
    sessionApprentissage(const questionnaire &q);
    size_t index() const;
    bool estTerminee() const;
    const question& questionCourante() const;
    std::string reponseCourante() const;
    void questionSuivante();


private:
    const questionnaire& d_questionnaire;
    size_t d_index;
};


#endif //PROJET_QUIZZ1_SESSIONAPPRENTISSAGE_H