#include "relations.h"
#include <cassert>
Relations_ptr Relations::s_pInstance(nullptr);

using namespace std::placeholders;
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
	
	add<start, true, all, true>(std::bind(se_t_all_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<start, true, all, false>(std::bind(se_t_all_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<start, false, all, true>(std::bind(se_f_all_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<start, false, all, false>(std::bind(se_f_all_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	
	add<end, true, all, true>(std::bind(se_t_all_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<end, true, all, false>(std::bind(se_t_all_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<end, false, all, true>(std::bind(se_f_all_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<end, false, all, false>(std::bind(se_f_all_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	////////start-end(4), any-se(8), always overlap

	add<all, true, start, true>(std::bind(all_t_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<all, true, start, false>(std::bind(all_t_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<all, false, start, true>(std::bind(all_f_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));
	add<all, false, start, false>(std::bind(all_f_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->startWith(s2);}));

	add<all, true, end, true>(std::bind(all_t_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	add<all, true, end, false>(std::bind(all_t_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	add<all, false, end, true>(std::bind(all_f_se_t, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));
	add<all, false, end, false>(std::bind(all_f_se_f, _1, _2, [](const SymVar_ptr & s1, const SymVar_ptr & s2){
		return s1->endWith(s2);}));

	add<all, true, any, true>(all_t_any_t);
	add<all, true, any, false>(all_t_any_f);
	add<all, false, any, true>(all_f_any_t);
	add<all, false, any, false>(all_f_any_f);

	add<any, true, all, true>(any_t_all_t);
	add<any, true, all, false>(any_t_all_f);
	add<any, false, all, true>(any_f_all_t);
	add<any, false, all, false>(any_f_all_f);

	add<any, true, any, true>(any_t_any_t);
	add<any, true, any, false>(any_t_any_f);
	add<any, false, any, true>(any_f_any_t);
	add<any, false, any, false>(any_f_any_f);

	add<all, true, all, true>(all_t_all_t);
	add<all, true, all, false>(all_t_all_f);
	add<all, false, all, true>(all_f_all_t);
	add<all, false, all, false>(all_f_all_f);
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
	if(c1->sub()->contains(c2->sub()))
		return imply;
	return overlap;
}
relation_t se_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()))
		return empty;
	return overlap;
}
relation_t se_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return overlap;
}
relation_t se_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return overlap;
}

relation_t se_t_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c2->sub(), c1->sub()))
		return imply;
	else
		return overlap;
}
relation_t se_t_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(!f(c2->sub(), c1->sub()))
		return imply;
	else
		return overlap;
}
relation_t se_f_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c2->sub(), c1->sub()))
		return empty;
	else
		return overlap;
}
relation_t se_f_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	return overlap;
}


relation_t all_t_se_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
	{
		return imply;
	}
	else
		return empty;
}
relation_t all_t_se_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
	{
		return empty;
	}
	else
		return imply;
}
relation_t all_f_se_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
		return empty;
	else
		return overlap;
}
relation_t all_f_se_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f)
{
	if(f(c1->sub(), c2->sub()))
		return imply;
	return overlap;
}

relation_t all_t_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()))
		return imply;
	return empty;
}
relation_t all_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()))
		return empty;
	return imply;
}
relation_t all_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return overlap;
}
relation_t all_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return overlap;
}


relation_t any_t_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(!c2->sub()->contains(c1->sub()))
		return empty;
	return overlap;
}
relation_t any_t_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return overlap;
}
relation_t any_f_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c2->sub()->contains(c1->sub()))
		return empty;
	return overlap;
}
relation_t any_f_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	return overlap;
}
//4*1
relation_t any_t_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()))
		return imply;
	else
		return overlap;
}
relation_t any_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()) ||
		c2->sub()->contains(c1->sub()))
		return empty;
	else
		return overlap;
}
relation_t any_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()) ||
		c2->sub()->contains(c1->sub()))
		return empty;
	else
		return overlap;
}
relation_t any_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()))
		return imply;
	else
		return overlap;
}
//4*1
relation_t all_t_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()) && c2->sub()->contains(c1->sub()))
		return imply;
	else
		return empty;
}
relation_t all_t_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(!c1->sub()->contains(c2->sub()) || !c2->sub()->contains(c1->sub()))
		return imply;
	return empty;
}
relation_t all_f_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(!c1->sub()->contains(c2->sub()) || !c2->sub()->contains(c1->sub()))
		return imply;
	return empty;
}
relation_t all_f_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2)
{
	if(c1->sub()->contains(c2->sub()) && c2->sub()->contains(c1->sub()))
		return imply;
	else
		return overlap;
}
