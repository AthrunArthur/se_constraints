#ifndef RELATIONS_H_
#define RELATIONS_H_
#include <memory>
#include <map>
#include <functional>
#include "constraints.h"

class Relations;
typedef std::shared_ptr<Relations> Relations_ptr;

typedef std::tuple<loc_t, pn_t, loc_t, pn_t> CSPairKey_t;
typedef std::function<relation_t (const Constraint_ptr & c1, const Constraint_ptr & c2) > RelationFunc_t;
CSPairKey_t make_pair_key(const Constraint_ptr & c1, const Constraint_ptr & c2);

relation_t relation_btw(const Constraint_ptr & c1, const Constraint_ptr & c2);

class Relations
{
public:
	static Relations &	instance();
	
	relation_t relation_btw(const Constraint_ptr & c1, const Constraint_ptr & c2);

	template <loc_t l1, pn_t p1, loc_t l2, pn_t p2, class F>
	void		add(F && f)
	{
		CSPairKey_t k = std::make_tuple(l1, p1, l2, p2);
		m_funcs.insert(std::make_pair(k, f));
	}
protected:

	void init();
	Relations();
private:
	static Relations_ptr s_pInstance;
	std::map<CSPairKey_t, RelationFunc_t>	m_funcs;
};

//4*2
relation_t se_t_se_t(const Constraint_ptr &c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t se_t_se_f(const Constraint_ptr &c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t se_f_se_t(const Constraint_ptr &c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t se_f_se_f(const Constraint_ptr &c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
///s-e, e-s, 4*2
//4*2
relation_t se_t_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t se_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t se_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t se_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
//4*2
relation_t se_t_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t se_t_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t se_f_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t se_f_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
//any-se, 4*2
//4*2
relation_t all_t_se_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t all_t_se_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t all_f_se_t(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
relation_t all_f_se_f(const Constraint_ptr & c1, const Constraint_ptr & c2, std::function<bool (const SymVar_ptr &, const SymVar_ptr &)> f);
//4*1
relation_t all_t_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t all_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t all_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t all_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
//4*1
relation_t any_t_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t any_t_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t any_f_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t any_f_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
//4*1
relation_t any_t_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t any_t_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t any_f_any_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t any_f_any_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
//4*1
relation_t all_t_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t all_t_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t all_f_all_t(const Constraint_ptr & c1, const Constraint_ptr & c2);
relation_t all_f_all_f(const Constraint_ptr & c1, const Constraint_ptr & c2);


#endif