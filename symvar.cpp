#include "symvar.h"

bool ConstSymVar::startWith(SymVar_ptr sv)
{
	auto p = std::dynamic_pointer_cast<ConstSymVar>(sv);
	if(!p)
		return false;
	std::string s = p->get();
	if(m_value.find(s) == 0)
		return true;
	return false;
}

bool ConstSymVar::endWith(SymVar_ptr sv)
{
	auto p = std::dynamic_pointer_cast<ConstSymVar>(sv);
	if(!p)
		return false;
	std::string s = p->get();
	std::size_t pos = m_value.rfind(s);
	if(pos != std::string::npos)
	{
		if(pos + s.length() == m_value.length())
			return true;
		return false;
	}
	return false;
}

bool ConstSymVar::contains(SymVar_ptr sv)
{
	auto p = std::dynamic_pointer_cast<ConstSymVar>(sv);
	if(!p)
		return false;
	std::string s = p->get();
	if(m_value.find(s) != std::string::npos)
		return true;
	return false;
}

bool SEValue::contains(SymVar_ptr sv)
{
	return false;
}

bool SEValue::startWith(SymVar_ptr sv)
{
	return false;
}

bool SEValue::endWith(SymVar_ptr sv)
{
	return false;
}

SymVar_ptr make_sym(const std::string & name)
{
	return SymVar_ptr(new SEValue(name));
}
SymVar_ptr make_const(const std::string & name)
{
	return SymVar_ptr(new ConstSymVar(name));
}