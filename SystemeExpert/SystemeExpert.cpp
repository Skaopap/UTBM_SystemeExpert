#include <iostream>
#include <fstream>
#include <istream>
#include <string>

// Header
#include "Equation.h"
#include "Hypotheses.h"
#include "Systeme.h"


/**
 * Verifie qu'un mot respecte les règles d'écriture
 */
bool checkWordIntegrity(const std::string& p_word)
{
    if (p_word.find('+') != std::string::npos)
    {
        std::cout << "[ERROR](SystemeExpert::checkWordIntegrity) : le caractere '+' n'est pas correctement place (>"+ p_word +"<), voir regles.txt" << std::endl;
        return false;
    }

    if (p_word.substr(1).find('!') != std::string::npos)
    {
        std::cout << "[ERROR](SystemeExpert::checkWordIntegrity) : le caractere '!' n'est pas correctement place (>" + p_word + "<), voir regles.txt" << std::endl;
        return false;
    }

    if (p_word.find('=') != std::string::npos)
    {
        std::cout << "[ERROR](SystemeExpert::checkWordIntegrity) : le caractere '=' n'est pas correctement place (>" + p_word + "<), voir regles.txt" << std::endl;
        return false;
    }

    if (p_word.find(' ') != std::string::npos)
    {
        std::cout << "[ERROR](SystemeExpert::checkWordIntegrity) : le caractere ' ' (espace) n'est pas correctement place (>" + p_word + "<), voir regles.txt" << std::endl;
        return false;
    }

    return true;
}

/**
 * Lit le fichier spécifié dans le répertoires Resources
 * Afin de remplir l'objet p_Hypotheses des données fournies
 */
bool initHypotheses(Hypotheses& p_Hypotheses, const std::string& p_sFileName = "Exemples/hypotheses_ex")
{
    std::ifstream l_fHypotheses("../Resources/"+ p_sFileName);

    if (!l_fHypotheses)
    {
        std::cout << "[ERROR](SystemeExpert::initHypotheses) : Erreur lecture fichier." << std::endl;
        return false;
    }

    std::string l_sTemp;
    while (std::getline(l_fHypotheses, l_sTemp))
    {
        // Check Word integrity
        if (!checkWordIntegrity(l_sTemp))
            return false;

        // Read the negation
        bool l_Value = (l_sTemp[0] == '!') ? false : true;
        int l_iSubstr = l_Value ? 0 : 1;
     
        // Add hypotheses
        p_Hypotheses.addHypotheses(std::make_pair(l_sTemp.substr(l_iSubstr), l_Value));
    }

    l_fHypotheses.close();
    return true;
}

/**
 * Lit le fichier spécifié dans le répertoires Resources
 * Afin de remplir l'objet p_Systeme avec les equations fournies
 */
bool initSysteme(Systeme& p_Systeme, const std::string& p_sFileName = "Exemples/systeme_ex")
{
    std::ifstream l_fSysteme("../Resources/" + p_sFileName);

    if (!l_fSysteme)
    {
        std::cout << "[ERROR](SystemeExpert::initSysteme) : Erreur lecture fichier." << std::endl;
        return false;
    }

    std::vector<std::string> l_vWords;

    // Store each word in l_vWords
    // Les mots sont reconnu en étant séparé par un espace
    std::copy(std::istream_iterator<std::string>(l_fSysteme),
        std::istream_iterator<std::string>(), back_inserter(l_vWords));

    std::vector<std::vector<std::string>> l_vEquationsRows;
    std::vector<std::string> l_vEquationWords;
    int l_bIsEnd = 0;

    // In one vector, one equation
    for (auto word : l_vWords)
    {
        if (l_bIsEnd == 2)
        {
            l_vEquationsRows.push_back(l_vEquationWords);
            l_vEquationWords.clear();
            l_bIsEnd = 0;
        }

        l_vEquationWords.push_back(word);


        if (word == "=" || l_bIsEnd == 1)
            l_bIsEnd++;
    }

    // Add the last one
    l_vEquationsRows.push_back(l_vEquationWords);

    std::vector<Equation> l_vEquations;
    Equation l_Equation;
    bool l_bIsConclusion = false;

    bool flagWordExpected;

    // Create Equations Vector
    for (auto equationRow : l_vEquationsRows)
    {
        // First word should not be + or =
        flagWordExpected = true;

        for (auto word : equationRow)
        {
            if (word != "+")
            {
                if (word != "=")
                {
                    // check
                    if (!flagWordExpected)
                    {
                        std::cout << "[ERROR](initSysteme) : Dans le fichier systeme : Caractere '+' ou '=' attendu, ou trop de mot apres un caractere '=' \n";
                        return false;
                    }

                    // Check Word integrity
                    if (!checkWordIntegrity(word))
                        return false;

                    if (l_bIsConclusion)
                    {
                        // Check negation
                        bool l_Value = (word[0] == '!') ? false : true;
                        int l_iSubstr = l_Value ? 0 : 1;

                        // Add conclusion
                        l_Equation.addConclusion(word.substr(l_iSubstr), l_Value);
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

                        // Check next word
                        flagWordExpected = false;
                    }

                }
                else if (!flagWordExpected)
                {
                    // Next word is the conclusion
                    l_bIsConclusion = true;
                    flagWordExpected = true;
                }
                else 
                {
                    std::cout << "[ERROR](initSysteme) : Un caractere '=' est mal place dans le fichier systeme \n";
                    return false;
                }
            }
            else if (!flagWordExpected)
            {
                flagWordExpected = true;
            }
            else 
            {
                std::cout << "[ERROR](initSysteme) : Un caractere '+' est mal place dans le fichier systeme \n";
                return false;
            }

        }
    }
    

    // Create System
    p_Systeme.setEquations(l_vEquations);

    l_fSysteme.close(); // close read streal
    return true;
}


int main()
{
    // Init variables
    Hypotheses l_Hypotheses;
    Systeme l_Systeme;
    std::string l_sChoice;

    // Here we go
    while (true)
    {
        // Menu
        do {
            std::cout << "\nSysteme Expert, Bienvenue !\n";
            std::cout << "Choix : " << "\n " << "1 - Lancer le systeme avec les fichers d'exemples \n 2 - Lancer le systeme avec un couple systeme/hypotheses personnalise \n 3 - Exit \n";
            std::cout << " Votre choix : ";
            std::getline(std::cin, l_sChoice);
        } while (l_sChoice != "1" && l_sChoice != "2" && l_sChoice != "3");

        if (l_sChoice == "1")
        {
            std::cout << " Choix 1 : Realisation du programmes avec les fichiers d'exemples. \n";
            // Lecture des fichiers Equation / Hypothèses d'exemple
            ;
            if (!initHypotheses(l_Hypotheses) || !initSysteme(l_Systeme))
            {
                std::cout << "\n /!\\ Veuillez modifier les fichiers et recommencer.  /!\\ \n";
                l_Hypotheses.clear();
                l_Systeme.clear();
                continue;
            }

        }
        else if (l_sChoice == "2")
        {
            std::cout << " Choix 2 : \n Veuillez remplir les fichiers nommes hypotheses et systeme dans le repertoires Resources selon les regles decrites dans regles.txt \n Appuyez sur entree une fois fini.";
            std::getline(std::cin, l_sChoice);

            // Lecture des fichiers Equation / Hypotheses
            if (!initHypotheses(l_Hypotheses, "hypotheses") || !initSysteme(l_Systeme, "systeme"))
            {
                std::cout << "\n /!\\ Veuillez modifier les fichiers et recommencer.  /!\\ \n";
                l_Hypotheses.clear();
                l_Systeme.clear();
                continue;
            }
        }
        else {
            // Fin du programme
            return 1;
        }

        // Afficher etat initial
        std::cout << "==================== Etat Initial ====================" << std::endl;
        l_Hypotheses.print();
        l_Systeme.print();

        // Résoudre et affichage résultat
        l_Systeme.ResolveSystem(l_Hypotheses);

        // Affichage résultat
        std::cout << "==================== Etat Final ====================" << std::endl;
        l_Hypotheses.print();
        l_Systeme.print(true);

        // Reset data
        l_Hypotheses.clear();
        l_Systeme.clear();
    }
}

