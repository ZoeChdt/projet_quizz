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
    std::string reponseCourante() const;
    virtual void questionSuivante();
    size_t nombreIndices () const;
    size_t indiceNumero(size_t i) const;
    size_t index() const;


private:
    const questionnaire& d_questionnaire;
    std::vector<size_t> d_indices;
    size_t d_index;
};


#endif //PROJET_QUIZZ1_SESSION_H