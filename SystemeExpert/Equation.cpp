#include "Equation.h"

void Equation::print() 
{
	for (auto it : m_vHypotheseName)
		std::cout << ((it.second == false) ? "!" : " ") << it.first << ((it == m_vHypotheseName.back()) ? "" : " + ");
	std::cout << " = " << m_sConclusion.first << std::endl;
}

void Equation::addHypotheseValue(const std::string& p_HypotheseName, const bool& p_HypotheseValue)
{
	// Check if the given hypothese is needed, and add it
	if (std::find_if(m_vHypotheseName.begin(), m_vHypotheseName.end(),
		[p_HypotheseName](const std::pair<std::string, bool>& hypo)->bool {return hypo.first == p_HypotheseName; }) != std::end(m_vHypotheseName))
	{
		m_HypotheseValue[p_HypotheseName] = p_HypotheseValue;
	}
}

bool Equation::tryToResolve()
{
	// Check if it's already resolve or if it's possible to resolve it
	if (m_bIsResolved || m_vHypotheseName.size() != m_HypotheseValue.size() )
		return false;

	// Compute the conclusion
	bool l_bResult = true;
	for (int index = 0; index < m_vHypotheseName.size(); ++index) 
	{
		// if '!'
		bool l_bHypotheseValue = (m_vHypotheseName[index].second) ? m_HypotheseValue[m_vHypotheseName[index].first] : !m_HypotheseValue[m_vHypotheseName[index].first];
		l_bResult = l_bResult && l_bHypotheseValue;
	}

	// Set the equation conclusion
	setConclusion(l_bResult);

	return true;
}

std::vector<std::string> Equation::getMissingData() const
{
	std::vector<std::string> l_vOutput;

	for (auto hyp : m_vHypotheseName)
	{
		if (m_HypotheseValue.find(hyp.first) == m_HypotheseValue.end())
		{
			l_vOutput.push_back(hyp.first);
		}
	}
	return l_vOutput;
}

void Equation::setConclusion(bool p_Result)
{
	m_sConclusion.second = p_Result;
	m_bIsResolved = true;
}

void Equation::clear() 
{
	m_vHypotheseName.clear(); m_sConclusion.first = "";
}