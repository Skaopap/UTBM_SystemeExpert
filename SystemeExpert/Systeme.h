#pragma once
#include "Equation.h"
#include "Hypotheses.h"
#include <vector>

class Systeme
{
public:
	Systeme() {};
	Systeme(const std::vector<Equation>& p_vEquations) : m_vEquations(p_vEquations) {}

	void ResolveSystem(Hypotheses& p_Hypotheses);

	void print(bool asResult = false);

	inline void setEquations(const std::vector<Equation>& p_vEquations) { m_vEquations = p_vEquations; }
	inline std::vector<Equation> const getEquations() const {return m_vEquations;}

protected:
	std::vector<Equation> m_vEquations;
};



