#include "constraints.h"


relation_t Constraint::relation_btw(const Constraint_ptr & p)
{

}

relation_t PathConstraints::checkCondition(const Constraint_ptr & p)
{
	relation_t r = overlap;
	for(Constraint_ptr & item : m_oConstraints)
	{
		r = item->relation_btw(p);
		if(r == imply || 
			r== empty)
			break;
	}
	return r;
}