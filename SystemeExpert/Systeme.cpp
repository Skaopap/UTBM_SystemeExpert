#include "Systeme.h"

void Systeme::ResolveSystem(Hypotheses& p_Hypotheses)
{
	std::vector< std::pair<std::string, bool> > l_Hypotheses = p_Hypotheses.getHypotheses();

	for (int index = 0 ; index < l_Hypotheses.size() ; ++index)
	{
		std::pair<std::string, bool> hypothese = l_Hypotheses[index];
		
		for (auto&& equation : m_vEquations)
		{
			// Add hypothese value
			equation.addHypotheseValue(hypothese.first, hypothese.second);

			// Resolve if possible
			if (equation.tryToResolve())
			{
				// Add conclusion 
				std::pair<std::string, bool> l_Conclusion = equation.getConclusion();
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
		if (asResult && !it.isResolved())
			std::cout << "(Hypotheses Manquante) ";
		it.print();
	}
	std::cout << "}" << std::endl;
		
}
