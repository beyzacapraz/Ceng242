#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const {return true;}

	__expr_t* AddOp::eval(const var_map_t& vars) const {
	    __expr_t* l = lhs_ -> eval(vars); __expr_t* r = rhs_ -> eval(vars);
	    const Const* ptr = dynamic_cast<const Const*>(l);
	    const Const* ptr2 = dynamic_cast<const Const*>(r);
	    if(ptr != NULL && ptr -> get_value() == 0){delete l; return r;}
	    else if(ptr2 != NULL && ptr2 -> get_value() == 0){delete r; return l;}
	    else if(ptr2 != NULL && ptr != NULL){delete l;delete r; return new Const(ptr -> get_value()+ptr2 -> get_value());}
	    else return new AddOp(l, r);
	}

	__expr_t* AddOp::diff(const std::string& v) const {
	    __expr_t* result = new AddOp(lhs_ -> diff(v),rhs_ -> diff(v));
	    __expr_t* final = result -> eval();
	    delete result;
	    return final;
	}

	std::ostream& AddOp::operator<< (std::ostream &out) const {
	    const __nullary_op_t* n = dynamic_cast<const __nullary_op_t*>(lhs_);
	    const __nullary_op_t* n2 = dynamic_cast<const __nullary_op_t*>(rhs_);
	    if(n != NULL && n2 != NULL) return out << *lhs_<< " + "<< *rhs_;
	    else if(n != NULL && n2 == NULL) return out << *lhs_ << " + " << "(" << *rhs_ << ")";
	    else if(n == NULL && n2 != NULL) return out << "("<< *lhs_ << ")" << " + " << *rhs_;
	    else return out << "(" << *lhs_ << ")" << " + " << "(" << *rhs_ << ")";
	    
	}

	bool AddOp::operator==(const __expr_t& other_) const {
	    const AddOp* ptr = dynamic_cast<const AddOp*>(&other_);
	    if(ptr == NULL) return false;
	    else if(*(ptr -> lhs_) == *lhs_ && *(ptr -> rhs_) == *rhs_) return true;
	    else if(*(ptr -> lhs_) == *rhs_ && *(ptr -> rhs_) == *lhs_) return true;
	    else return false;
	}
}

namespace sym 
{
	bool MulOp::is_mul() const {return true;}

	__expr_t* MulOp::eval(const var_map_t& vars) const {
	    __expr_t* l = lhs_ -> eval(); __expr_t* r = rhs_ -> eval();
	    const Const* ptr = dynamic_cast<const Const*>(l);
	    const Const* ptr2 = dynamic_cast<const Const*>(r);
	    if(ptr != NULL && ptr -> get_value() == 0){delete l;delete r; return new Const(0);}
	    else if(ptr2 != NULL && ptr2 -> get_value() == 0){delete l;delete r; return new Const(0);}
	    else if(ptr != NULL && ptr -> get_value() == 1){delete l; return r;}
	    else if(ptr2 != NULL && ptr2 -> get_value() == 1){delete r; return l;}
	    else if(ptr2 != NULL && ptr != NULL){delete l; delete r; return new Const(ptr -> get_value()*ptr2 -> get_value());}
	    else return new MulOp(l, r);
	    
	}

	__expr_t* MulOp::diff(const std::string& v) const {
	    __expr_t* result = new AddOp((MulOp(lhs_ -> diff(v),rhs_ -> eval())).eval(),(MulOp(lhs_->eval(),rhs_ -> diff(v))).eval());
	    __expr_t* f = result -> eval();
	    delete result; return f;
	   
	}

	std::ostream& MulOp::operator<< (std::ostream &out) const {
	    const __nullary_op_t* n = dynamic_cast<const __nullary_op_t*>(lhs_);
	    const __nullary_op_t* n2 = dynamic_cast<const __nullary_op_t*>(rhs_);
	    if(n != NULL && n2 != NULL) return out << *lhs_<< " * "<< *rhs_;
	    else if(n != NULL && n2 == NULL) return out << *lhs_ << " * " << "(" << *rhs_ << ")";
	    else if(n == NULL && n2 != NULL) return out << "("<< *lhs_ << ")" << " * " << *rhs_;
	    else return out << "(" << *lhs_ << ")" << " * " << "(" << *rhs_ << ")";
	    
	}

	bool MulOp::operator==(const __expr_t& other_) const {
	    const MulOp* ptr = dynamic_cast<const MulOp*>(&other_);
	    if(ptr == NULL) return false;
	    else if(*(ptr -> lhs_) == *lhs_ && *(ptr -> rhs_) == *rhs_) return true;
	    else if(*(ptr -> lhs_) == *rhs_ && *(ptr -> rhs_) == *lhs_) return true;
	    else return false;
	}
}
