#include "constraints.h"
#include "relations.h"
#include <sstream>


Constraint::Constraint(const SymVar_ptr& ph, SymVar_ptr ps, loc_t l, pn_t p)
	: m_host(ph)
	, m_sub(ps)
	, m_loc(l)
	, m_pn(p)
{
}

relation_t PathConstraints::checkCondition(const Constraint_ptr & p)
{
	relation_t r = overlap;
	for(Constraint_ptr & item : m_oConstraints)
	{
		r = relation_btw(item, p);
		if(r == imply || 
			r== empty)
			break;
	}
	return r;
}

Constraint_ptr make_constraint(const SymVar_ptr & h, const std::string & str, loc_t l, pn_t p)
{
	SymVar_ptr s = std::make_shared<ConstSymVar>(str);
	return std::make_shared<Constraint>(h, s, l, p);
}

std::string str(loc_t l)
{
	std::stringstream ss;
	switch (l)
	{
	case start:
		ss<<"start";
		break;
	case end:
		ss<<"end";
		break;
	case any:
		ss<<"any";
		break;
	case all:
		ss<<"all";
		break;
	default:
		break;
	}
	return ss.str();
}
std::string str(relation_t r)
{
	std::stringstream ss;
	switch (r)
	{
	case empty:
		ss<<"Empty";
		break;
	case imply:
		ss<<"Imply";
		break;
	case overlap:
		ss<<"Overlap";
		break;
	default:
		break;
	}
	return ss.str();
}