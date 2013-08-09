#include "relations.h"
#include <cassert>
Relations_ptr Relations::s_pInstance(nullptr);

Relations::Relations()
	: m_funcs()
{
}

Relations & Relations::instance()
{
	if(!s_pInstance)
	{
		s_pInstance = std::shared_ptr<Relations>(new Relations());
		s_pInstance->init();
	}
	return *(s_pInstance.get());
}

relation_t Relations::relation_btw(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->host() != c2->host() )
		return overlap;
	auto k = make_pair_key(c1, c2);
	
	if(m_funcs.find(k) == m_funcs.end())
		return overlap;
	return m_funcs[k](c1, c2);
}

CSPairKey_t make_pair_key(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return std::make_tuple(c1->loc(), c1->pn(), c2->loc(), c2->pn());
}

relation_t relation_btw(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	static Relations & r= Relations::instance();
	return r.relation_btw(c1, c2);
}

void Relations::init()
{
	////////
	add<start, true, start, true>(std::bind(se_t_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<start, true, start, false>(std::bind(se_t_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<start, false, start, true>(std::bind(se_f_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<start, false, start, false>(std::bind(se_f_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));

	/////////////
	add<end, true, end, true>(std::bind(se_t_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	add<end, true, end, false>(std::bind(se_t_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	add<end, false, end, true>(std::bind(se_f_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	add<end, false, end, false>(std::bind(se_f_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	//////////////////
	add<start, true, any, true>(se_t_any_t);
	add<start, true, any, false>(se_t_any_f);
	add<start, false, any, true>(se_f_any_t);
	add<start, false, any, false>(se_f_any_f);
	/////////////
	add<end, true, any, true>(se_t_any_t);
	add<end, true, any, false>(se_t_any_f);
	add<end, false, any, true>(se_f_any_t);
	add<end, false, any, false>(se_f_any_f);

}

relation_t se_t_se_t(const Constraint_ptr &c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
		return imply;
	else if(f(c2->sub(), c1->sub()))
		return overlap;
	else
		return empty;
}

relation_t se_t_se_f(const Constraint_ptr &c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(),c2->sub()))
		return empty;
	else if(!f(c2->sub(), c1->sub()))
	{
		return imply;
	}
	else
		return overlap;
}
relation_t se_f_se_t(const Constraint_ptr &c1, const Constraint_ptr & c2 , std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
		return empty;
	else
		return overlap;
}
relation_t se_f_se_f(const Constraint_ptr &c1, const Constraint_ptr & c2 , std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
		return imply;
	return overlap;
}


relation_t se_t_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{

}
relation_t se_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t se_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t se_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
