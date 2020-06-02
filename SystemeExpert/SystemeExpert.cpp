// SystemeExpert.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#include "Hypotheses.h"
#include "Systeme.h"

bool initHypotheses(Hypotheses& p_Hypotheses, const std::string& p_sFileName = "Exemples/hypotheses_ex")
{
    std::ifstream l_fHypotheses("./Resources/"+ p_sFileName);

    if (!l_fHypotheses)
    {
        std::cout << "[ERROR](SystemeExpert::initHypotheses) : Erreur lecture fichier." << std::endl;
        return false;
    }

    std::string l_sTemp;
    while (std::getline(l_fHypotheses, l_sTemp))
    {
        std::cout << l_sTemp << std::endl;
        // Read the negation
        bool l_Value = (l_sTemp[0] == '!') ? false : true;
     
        // Add hypotheses
        p_Hypotheses.addHypotheses(std::make_pair(l_sTemp.substr(1), l_Value));
    }

    l_fHypotheses.close();
    return true;
}

bool initSysteme(Systeme& p_Systeme, const std::string& p_sFileName = "Exemples/systeme_ex")
{
    std::ifstream l_fSysteme("./Resources/" + p_sFileName);

    if (!l_fSysteme)
    {
        std::cout << "[ERROR](SystemeExpert::initSysteme) : Erreur lecture fichier." << std::endl;
        return false;
    }

    l_fSysteme.close();
    return true;
}

int main()
{
    std::cout << "Systeme Expert, Bienvenue !\n";

    // Init variables
    Hypotheses l_Hypotheses;
    Systeme l_Systeme;

    // Lecture des fichiers Equation / Hypothèses
    initHypotheses(l_Hypotheses);
    initSysteme(l_Systeme);

    // Possibilité de laisser avec les fichiers exemples

    // Résoudre

    // Affichage résultat
}

