#pragma once

#include <iostream>
#include <vector>


class Hypotheses
{
public :
	// Constructeur 
	Hypotheses() {};

	// Show data in console
	void print() const;

	// Add hypothese 
	void addHypotheses(const std::pair<std::string, bool>& p_NewHypotheses) { m_vHypotheses.push_back(p_NewHypotheses); }

	// clear data
	void clear() { m_vHypotheses.clear(); };

	// Get the Hypotheses as a vector
	std::vector< std::pair<std::string, bool> > getHypotheses() { return m_vHypotheses; };

protected:
	// Format Hypothese : pair< name , value > 
	std::vector< std::pair<std::string, bool> > m_vHypotheses;
};

