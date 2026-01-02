cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES_COMMUNES
        gestionnaire.cpp
        questionChoixMultiples.cpp
        evaluationSecondeChance.cpp
        evaluationTest.cpp
        questionnaire.cpp
        evaluationAdaptative.cpp
        questionNumerique.cpp
        questionRepertoire.cpp
        questionTexte.cpp
        session.cpp
        sessionApprentissage.cpp
        sessionEvaluation.cpp
)

add_executable(untitled
        main.cpp
        ${SOURCES_COMMUNES}
)

add_executable(tests
        tests_main.cpp
        gestionnaireTest.cpp
        questionnaireTest.cpp
        evaluationTestTests.cpp
        questionChoixMultiplesTests.cpp
        evaluationSecondeChanceTests.cpp
        evaluationAdaptativeTests.cpp
        questionNumeriqueTest.cpp
        questionRepertoireTest.cpp
        questionTexteTest.cpp
        sessionTest.cpp
        ${SOURCES_COMMUNES}
)

