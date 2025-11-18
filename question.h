//
// Created by chzoe on 18/11/2025.
//

#ifndef PROJET_QUIZZ_QUESTION_H
#define PROJET_QUIZZ_QUESTION_H

class question {
public:
    virtual ~question() = default;
    virtual string enonce() const =0;
    virtual bool reponseJuste(const string& reponse) const = 0;
};

#endif //PROJET_QUIZZ_QUESTION_H