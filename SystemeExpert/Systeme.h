#pragma once
#include "Equation.h"
#include <vector>

class Systeme
{
public:
	Systeme() {};
	Systeme(const std::vector<Equation>& p_vEquations) : m_vEquations(p_vEquations) {}

	inline void setEquations(const std::vector<Equation>& p_vEquations) { m_vEquations = p_vEquations; }
	inline std::vector<Equation> const getEquations() const {return m_vEquations;}

protected:
	std::vector<Equation> m_vEquations;
};

