#include "Systeme.h"

void Systeme::ResolveSystem(Hypotheses& p_Hypotheses)
{
	// Get Hypotheses Data
	std::vector< std::pair<std::string, bool> > l_Hypotheses = p_Hypotheses.getHypotheses();

	// For each hypotheses
	for (int index = 0 ; index < l_Hypotheses.size() ; ++index)
	{
		// Get hypothese once
		std::pair<std::string, bool> hypothese = l_Hypotheses[index];
		
		// For each equations
		for (auto&& equation : m_vEquations)
		{
			// Add hypothese value
			equation.addHypotheseValue(hypothese.first, hypothese.second);

			// Resolve if possible (possible if all equation hypotheses is known)
			if (equation.tryToResolve())
			{
				// If resolved, Add conclusion 
				std::pair<std::string, bool> l_Conclusion = equation.getConclusion();

				// Add the new hypotheses data in local vector and in Hypotheses object
				l_Hypotheses.push_back(l_Conclusion);
				p_Hypotheses.addHypotheses(l_Conclusion);
			}
		}
	}
}

void Systeme::print(bool asResult)
{
	std::cout << "Systeme d'equation : " << std::endl << "{ " << std::endl;
	for (auto it : m_vEquations)
	{
		std::cout << "\t";
		// Custom print
		if (asResult && !it.isResolved())
		{
			std::cout << "(Hypotheses Manquantes : ";
			std::vector<std::string> l_vMissingHypothesesNames = it.getMissingData();
			for (auto name : l_vMissingHypothesesNames)
				std::cout << name << " , ";
			std::cout << " ) : ";
		}
		it.print();
	}
	std::cout << "}" << std::endl;
		
}
