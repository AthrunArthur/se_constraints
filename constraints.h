#ifndef CONSTRAINTS_H_
#define CONSTRAINTS_H_
#include <tuple>
#include <vector>
#include <memory>
#include "symvar.h"


enum loc_t{
	start, 
	end, 
	any, 
	all,
};
enum relation_t{
	empty,
	imply,
	overlap
};

std::string str(loc_t l);
std::string str(relation_t r);

typedef bool pn_t;

class Constraint;
typedef std::shared_ptr<Constraint> Constraint_ptr;

class Constraint
{
public:
	Constraint(const SymVar_ptr& ph, SymVar_ptr ps, loc_t l, pn_t p);


	inline loc_t	loc() const {return m_loc;}
	inline pn_t	pn() const {return m_pn;}

	SymVar_ptr host() const {return m_host;}
	SymVar_ptr sub() const{return m_sub;}

protected:
	SymVar_ptr		m_host;
    SymVar_ptr		m_sub;
	loc_t   m_loc;
	pn_t	m_pn;
};


Constraint_ptr make_constraint(const SymVar_ptr & h, const std::string & str, loc_t l, pn_t p);

/*
template <class T>
Constraint_ptr make_constraint(const SymVar_ptr & h, T s, loc_t l, pn_t p)
{
	return std::make_shared<Constraint>(h, s, l, p);
}*/



class PathConstraints
{
public:
	PathConstraints(){};

	template<class T>
	void	addConstraint(const SymVar & h, T s, loc_t l, pn_t p)
	{
		m_oConstraints.push_back(make_constraint(h, s, l, p));
	}
	void	addConstraint(const Constraint_ptr & p)
	{
		m_oConstraints.push_back(p);
	}

	relation_t checkCondition(const Constraint_ptr & c);

protected:
	typedef std::vector<Constraint_ptr>		Container_t;
	Container_t m_oConstraints;
};



#endif