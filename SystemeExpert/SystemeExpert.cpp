// SystemeExpert.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#include "Equation.h"
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
        int l_iSubstr = l_Value ? 0 : 1;
     
        // Add hypotheses
        p_Hypotheses.addHypotheses(std::make_pair(l_sTemp.substr(l_iSubstr), l_Value));
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

    std::vector<std::string> l_vWords;

    // Store each word in l_vWords
    std::copy(std::istream_iterator<std::string>(l_fSysteme),
        std::istream_iterator<std::string>(), back_inserter(l_vWords));

    std::vector<Equation> l_vEquations;
    Equation l_Equation;
    bool l_bIsConclusion = false;

    // Create Equations Vector
    for (auto word : l_vWords)
    {
        if (word != "+")
        {
            if (word != "=")
            {
                if (l_bIsConclusion)
                {
                    // Add conclusion
                    l_Equation.addConclusion(word);
                    l_vEquations.push_back(l_Equation);

                    // Reset
                    l_bIsConclusion = false;
                    l_Equation.clear();
                }
                else
                {
                    // Check negation
                    bool l_Value = (word[0] == '!') ? false : true;
                    int l_iSubstr = l_Value ? 0 : 1;

                    // Add hypotheses
                    l_Equation.addHypotheseOperation(std::make_pair(word.substr(l_iSubstr), l_Value));
                }
                
            }
            else
            {
                l_bIsConclusion = true;
            }
        }
    }

    // Create System
    p_Systeme.setEquations(l_vEquations);

    l_fSysteme.close();
    return true;
}

int main()
{
    // Init variables
    Hypotheses l_Hypotheses;
    Systeme l_Systeme;
    std::string l_sChoice;

    do {
        std::cout << "Systeme Expert, Bienvenue !\n";
        std::cout << "Choix : " << "\n " << "1 - Lancer le systeme avec les fichers d'exemples \n 2 - Lancer le systeme avec un couple systeme/hypotheses personnalise \n";
        std::cout << " Votre choix : ";
        std::getline(std::cin, l_sChoice);
    } while (l_sChoice != "1" && l_sChoice != "2");

    if (l_sChoice == "1")
    {
        // Lecture des fichiers Equation / Hypothèses d'exemple
        initHypotheses(l_Hypotheses);
        initSysteme(l_Systeme);
    }
    else if (l_sChoice == "2")
    {
        std::cout << "Veuillez remplir les fichiers nommes hypotheses et systeme dans le repertoires Resources selon les regles decrites dans regles.txt \n Appuyez sur entree une fois fini.";
        std::getline(std::cin, l_sChoice);

        initHypotheses(l_Hypotheses,"hypotheses");
        initSysteme(l_Systeme,"systeme");
    }

    // Afficher etat initial
    std::cout << "========== Etat Initial ==========" << std::endl;
    l_Hypotheses.print();
    l_Systeme.print();

    // Possibilité de laisser avec les fichiers exemples

    // Résoudre et affichage résultat
    l_Systeme.ResolveSystem(l_Hypotheses);

    // Affichage résultat
    std::cout << "========== Etat Final ==========" << std::endl;
    l_Hypotheses.print();
    l_Systeme.print(true);
}

