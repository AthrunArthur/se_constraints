#ifndef SYM_VAR_H_
#define SYM_VAR_H_
#include <memory>
#include <string>

class SymVar;
typedef std::shared_ptr<SymVar> SymVar_ptr;
class SymVar
{
public:
	virtual bool		startWith(SymVar_ptr sv) = 0;
	virtual bool		endWith(SymVar_ptr sv) = 0;
	virtual bool		contains(SymVar_ptr sv) = 0;
};





class ConstSymVar : public SymVar
{
public:
	ConstSymVar(const std::string & str)
		: m_value(str){}

	virtual bool		startWith(SymVar_ptr sv);
	virtual bool		endWith(SymVar_ptr sv);
	virtual bool		contains(SymVar_ptr sv);

	std::string 		get() const{return m_value;}
protected:
	std::string		m_value;
};


class SEValue : public SymVar
{
public:
	SEValue(const std::string & s){}
	virtual bool		startWith(SymVar_ptr sv);
	virtual bool		endWith(SymVar_ptr sv);
	virtual bool		contains(SymVar_ptr sv);
};

SymVar_ptr make_sym(const std::string & name);
SymVar_ptr make_const(const std::string & name);
#endif