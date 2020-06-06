#include "Hypotheses.h"

void Hypotheses::print() const
{
	std::cout << "Liste D'hypothese : " << std::endl << "{ " << std::endl;
	for (auto it : m_vHypotheses)
		std::cout << "\t" << ((it.second == false) ? "!" : "") << it.first << std::endl;
	std::cout << "}" << std::endl;
}