#include "expr.h"

namespace sym 
{
	Expr::Expr(const Const& c) {expr_ = c.eval();}
	Expr::Expr(const Var& v) {expr_ = v.eval();}
	Expr::Expr(const __expr_t* e) {expr_ = e;}
	Expr::Expr(const __expr_t& e) {expr_ = &e;}
	Expr::Expr(const Expr& e) {expr_ = e.expr_ -> eval();}
		
	Expr::~Expr() {delete expr_;}

	__expr_t* Expr::eval(const var_map_t& var_map) const {
	    __expr_t* r = expr_ -> eval();
	    return r;
	}
	__expr_t* Expr::diff(const std::string& v) const {
	    __expr_t* r = expr_ -> diff(v);
	    __expr_t* f = r -> eval();
	    delete r;
	    return f;
	}
	std::ostream& Expr::operator<< (std::ostream &out) const {
	    return out << *expr_;
	}
	bool Expr::operator==(const Expr& other) const {
	    if(*(other.expr_) == *expr_) return true; else false;
	}
	bool Expr::operator==(const __expr_t& other) const {
	    if(other == *expr_) return true; else false;
	}
}                                                                  	
