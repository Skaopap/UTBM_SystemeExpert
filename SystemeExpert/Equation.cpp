#include "Equation.h"

void Equation::print() 
{
	for (auto it : m_vHypotheseName)
		std::cout << ((it.second == false) ? "!" : " ") << it.first << ((it == m_vHypotheseName.back()) ? "" : " + ");
	std::cout << " = " << m_sConclusion.first << std::endl;
}

void Equation::addHypotheseValue(const std::string& p_HypotheseName, const bool& p_HypotheseValue)
{
	if (std::find_if(m_vHypotheseName.begin(), m_vHypotheseName.end(),
		[p_HypotheseName](const std::pair<std::string, bool>& hypo)->bool {return hypo.first == p_HypotheseName; }) != std::end(m_vHypotheseName))
	{
		m_HypotheseValue[p_HypotheseName] = p_HypotheseValue;
	}
}

bool Equation::tryToResolve()
{
	if (m_bIsResolved || m_vHypotheseName.size() != m_HypotheseValue.size() )
		return false;

	bool l_bResult = true;
	for (int index = 0; index < m_vHypotheseName.size(); ++index) 
	{
		bool l_bHypotheseValue = (m_vHypotheseName[index].second) ? m_HypotheseValue[m_vHypotheseName[index].first] : !m_HypotheseValue[m_vHypotheseName[index].first];
		l_bResult = l_bResult && l_bHypotheseValue;
	}

	setConclusion(l_bResult);

	return true;
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