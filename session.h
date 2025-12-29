//
// Created by Aktas Julidè on 29/12/2025.
//

#ifndef PROJET_QUIZZ1_SESSION_H
#define PROJET_QUIZZ1_SESSION_H

#include "questionnaire.h"
#include <vector>

class session {
public:
    session(const questionnaire &q);
    virtual ~session()=default;
    bool estTerminee() const;
    const question& questionCourante()const;
    virtual void questionSuivante();
protected:
    const questionnaire& d_questionnaire;
    std::vector<size_t> d_indices;
    size_t d_index;
};


#endif //PROJET_QUIZZ1_SESSION_H