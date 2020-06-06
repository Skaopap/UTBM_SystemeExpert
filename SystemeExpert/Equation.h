#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>


class Equation
{
public:
	// Constructor 
	Equation() : m_bIsResolved(false) {}

	// Add hypothese
	inline void addHypotheseOperation(const std::pair<std::string, bool>& p_Hypothese) { m_vHypotheseName.push_back(p_Hypothese); }

	// Add the hypotheses value
	void addHypotheseValue(const std::string& p_HypotheseName, const bool& p_HypotheseValue);

	// Add the conclusion
	inline void addConclusion(const std::string& p_conclusion) { m_sConclusion = std::make_pair(p_conclusion, false); }

	// To check if the equation is resolved
	inline bool isResolved() { return m_bIsResolved; }

	// Set and get for conclusion
	void setConclusion(bool p_Result);
	std::pair<std::string, bool> const getConclusion() const { return m_sConclusion; }

	// Clear Equation Data
	void clear();

	// Output in console
	void print();

	// Resolve the equation if possible, return false if its not
	bool tryToResolve();

	// Return missing hypotheses data
	std::vector<std::string> getMissingData() const;

protected :
	// Vector of equation premisse, with its 'sign' ( '!' present or not )
	// pair < name , operator > , operator = true if a '!' is present
	std::vector<std::pair<std::string, bool>> m_vHypotheseName;

	// Store Hypothese value in a map < name , value >
	std::map<std::string, bool> m_HypotheseValue;

	// Store conclusion < name , value> 
	std::pair<std::string, bool> m_sConclusion;

	// Flag Resolved
	bool m_bIsResolved;
};

