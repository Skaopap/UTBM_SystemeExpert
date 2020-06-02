#pragma once

#include <iostream>
#include <vector>


class Hypotheses
{
public :
	Hypotheses() {};
	void print();
	void addHypotheses(std::pair<std::string, bool> p_NewHypotheses) { m_vHypotheses.push_back(p_NewHypotheses); }
	std::vector< std::pair<std::string, bool> > getHypotheses() { return m_vHypotheses; };

protected:
	std::vector< std::pair<std::string, bool> > m_vHypotheses;
};

