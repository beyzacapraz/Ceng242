#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const {return true;}

	__expr_t* NegOp::eval(const var_map_t& vars) const {
	    __expr_t* op = operand -> eval(vars);
    	const Const* ptr = dynamic_cast<const Const*>(op);
    	if(ptr != NULL){delete op; return new Const((ptr -> get_value())*(-1));}
        else return new NegOp(op);
	}

	__expr_t* NegOp::diff(const std::string& v) const {
	    return new NegOp(operand -> diff(v));
	}

	std::ostream& NegOp::operator<< (std::ostream &out) const {
	    const __nullary_op_t* n = dynamic_cast<const __nullary_op_t*>(operand);
	    if(n == NULL) return out << "-" << "(" << *operand << ")";
	    else return out << "-" << *operand;
	}

	bool NegOp::operator==(const __expr_t& other_) const {
	    const NegOp* ptr = dynamic_cast<const NegOp*>(&other_);
	    if(ptr == NULL) return false; else if(*(ptr -> operand) == *operand) return true; else return false;
	}
}

namespace sym 
{
	bool ExpOp::is_exp() const {return true;}

	__expr_t* ExpOp::eval(const var_map_t& vars) const {
	    __expr_t* op = operand -> eval(vars);
	    const Const* ptr = dynamic_cast<const Const*>(op);
    	if(ptr != NULL){delete op; return new Const(std::exp(ptr -> get_value()));}
        else return new ExpOp(op);
	}

	__expr_t* ExpOp::diff(const std::string& v) const {
	    __expr_t* r = new ExpOp(operand -> eval());
	    __expr_t* e = new MulOp(operand -> diff(v),r);
	    __expr_t* result = e -> eval();
	    delete e;
	    return result;
	    
	}

	std::ostream& ExpOp::operator<< (std::ostream &out) const {
	    const __nullary_op_t* n = dynamic_cast<const __nullary_op_t*>(operand);
	    if(n == NULL) return out << "e^" << "("<< *operand << ")";
	    else return out << "e^" << *operand;
	}

	bool ExpOp::operator==(const __expr_t& other_) const {
	    const ExpOp* ptr = dynamic_cast<const ExpOp*>(&other_);
	    if(ptr == NULL) return false; else if(*(ptr -> operand) == *operand) return true;else return false;
	}
}
