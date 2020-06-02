#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>


class Equation
{
public:
	Equation() : m_bIsResolved(false) {}

	inline void addHypotheseOperation(const std::pair<std::string, bool>& p_Hypothese) { m_vHypotheseName.push_back(p_Hypothese); }
	inline void addConclusion(const std::string& p_conclusion) { m_sConclusion = std::make_pair(p_conclusion, false); }

	inline bool isResolved() { return m_bIsResolved; }

	void setConclusion(bool p_Result);
	std::pair<std::string, bool> const getConclusion() const { return m_sConclusion; }

	void clear();

	void print();

	void addHypotheseValue(const std::string& p_HypotheseName, const bool& p_HypotheseValue);

	bool tryToResolve();

protected :
	std::vector<std::pair<std::string, bool>> m_vHypotheseName;
	std::map<std::string, bool> m_HypotheseValue;
	std::pair<std::string, bool> m_sConclusion;
	bool m_bIsResolved;
};

