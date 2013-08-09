#ifndef SYM_VAR_H_
#define SYM_VAR_H_
#include <memory>

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

	virtual bool startWith(SymVar_ptr sv);
	virtual bool		endWith(SymVar_ptr sv);
	virtual bool		contains(SymVar_ptr sv);

	std::string 		get(){return m_value;}
private:
	std::string		m_value;
};


class SEValue : public SymVar
{
public:
	virtual bool startWith(SymVar_ptr sv);
	virtual bool		endWith(SymVar_ptr sv);
	virtual bool		contains(SymVar_ptr sv);
protected:
};

#endif