#pragma once
#include "Equation.h"
#include "Hypotheses.h"
#include <vector>

class Systeme
{
public:
	// Constructors
	Systeme() {};
	Systeme(const std::vector<Equation>& p_vEquations) : m_vEquations(p_vEquations) {}

	// Resolve the system with the known hypotheses
	void ResolveSystem(Hypotheses& p_Hypotheses);

	// Output in console
	void print(bool asResult = false);

	// clear data
	void clear() { m_vEquations.clear(); }

	// set and get
	inline void setEquations(const std::vector<Equation>& p_vEquations) { m_vEquations = p_vEquations; }
	inline std::vector<Equation> const getEquations() const {return m_vEquations;}

protected:
	// Vector of equation
	std::vector<Equation> m_vEquations;
};



