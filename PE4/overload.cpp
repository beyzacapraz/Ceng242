#include "nullary.h"
#include "unary.h"
#include "binary.h"

namespace sym {
	__expr_t& operator-(const __expr_t &op) {
	   if(op.is_nullary()) return *(new NegOp(op.eval()));
	   else *(new NegOp(&op));
	    
	}
	__expr_t& exp(const __expr_t &op) {
	    if(op.is_nullary()) return *(new ExpOp(op.eval()));
	    else return *(new ExpOp(&op));
	    
	}

	__expr_t& operator+(const __expr_t &lhs, const __expr_t &rhs) {
	    if(lhs.is_nullary() && rhs.is_nullary()) return *(new AddOp(lhs.eval(),rhs.eval()));
	    else if(lhs.is_nullary()) return *(new AddOp(lhs.eval(),&rhs));
	    else if(rhs.is_nullary()) return *(new AddOp(&lhs,rhs.eval()));
	    else return *(new AddOp(&lhs,&rhs));
	    
	}
	__expr_t& operator+(double lhs, const __expr_t &rhs) {
	    Const* l = new Const(lhs);
	    if (rhs.is_nullary()) return *(new AddOp(l,rhs.eval()));
	    else return *(new AddOp(l,&rhs));
	}
	__expr_t& operator+(const __expr_t &lhs, double rhs) {
	    Const* r = new Const(rhs);
	    if(lhs.is_nullary()) return *(new AddOp(lhs.eval(),r));
	    else return *(new AddOp(&lhs,r));//??
	    
	}

	__expr_t& operator*(const __expr_t &lhs, const __expr_t &rhs) {
	    if(lhs.is_nullary() && rhs.is_nullary()) return *(new MulOp(lhs.eval(),rhs.eval()));
	    else if(lhs.is_nullary()) return *(new MulOp(lhs.eval(),&rhs));
	    else if(rhs.is_nullary()) return *(new MulOp(&lhs,rhs.eval()));
	    else return *(new MulOp(&lhs,&rhs));
	    
	}
	__expr_t& operator*(double lhs, const __expr_t &rhs) {
	    Const* l= new Const(lhs);
	    if(rhs.is_nullary()) return *(new MulOp(l,rhs.eval()));
	    else return *(new MulOp(l,&rhs));
	}
	__expr_t& operator*(const __expr_t &lhs, double rhs) {
	    Const* r = new Const(rhs);
	    if(lhs.is_nullary()) return *(new MulOp(lhs.eval(),r));
	    else return *(new MulOp(&lhs,r));
	}
}
