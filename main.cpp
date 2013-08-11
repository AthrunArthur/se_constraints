#include "constraints.h"
#include "symvar.h"
#include "relations.h"

#include <iostream>

void test()
{
	
	auto s1 = make_sym("s1");

	auto c1 = make_constraint(s1, "ABCD", start, true);
	auto c2 = make_constraint(s1, "BC", start, true);
	
	relation_t r = relation_btw(c1, c2);

	std::cout<<str(r)<<std::endl;

	auto str1 = make_const("ABCDEFG");
	auto str2 = make_const("ABC");
	auto str3 = make_const("EFG");
	std::cout<<"should be true: "<<str1->contains(str2)<<std::endl;
	std::cout<<"should be true: "<<str1->contains(str3)<<std::endl;
	std::cout<<"should be true: "<<str1->startWith(str2)<<std::endl;
	std::cout<<"should be true: "<<str1->endWith(str3)<<std::endl;
	auto str4 = make_const("tt");
	std::cout<<"should be false: "<<str1->contains(str4)<<std::endl;
	std::cout<<"should be false: "<<str1->startWith(str4)<<std::endl;
	std::cout<<"should be false: "<<str1->endWith(str4)<<std::endl;
	auto str5 = make_const("TEFG");
	std::cout<<"should be false: "<<str3->endWith(str5)<<std::endl;

}
int main(int argc, char *argv[])
{
	test();
	PathConstraints pc;
	auto s1 = make_sym("s1");
	pc.addConstraint(make_constraint(s1, "ABCD", start, true));
	pc.addConstraint(make_constraint(s1, "XYZ", end, true));
	pc.addConstraint(make_constraint(s1, "abcd", any, false));

	auto c1 = make_constraint(s1, "ABC", start, true);
	relation_t r = pc.checkCondition(c1);
	std::cout<<"should be Imply: "<<str(r)<<std::endl;

	auto c2 = make_constraint(s1, "TXYZ", end, false);
	r = pc.checkCondition(c2);
	std::cout<<"should be Overlap: "<<str(r)<<std::endl;
	return 0;
}

