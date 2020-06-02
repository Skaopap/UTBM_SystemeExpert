#pragma once

#include <iostream>
#include <vector>


class Hypotheses
{
public :
	Hypotheses() {};

	void addHypotheses(std::pair<std::string, bool> p_NewHypotheses) { m_vHypotheses.push_back(p_NewHypotheses); }

protected:
	std::vector< std::pair<std::string, bool> > m_vHypotheses;
};

