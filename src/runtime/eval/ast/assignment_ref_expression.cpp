/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <runtime/eval/ast/assignment_ref_expression.h>
#include <runtime/eval/ast/lval_expression.h>

namespace HPHP {
namespace Eval {
///////////////////////////////////////////////////////////////////////////////

AssignmentRefExpression::AssignmentRefExpression(EXPRESSION_ARGS,
                                                 LvalExpressionPtr lhs,
                                                 ExpressionPtr rhs)
  : Expression(KindOfAssignmentRefExpression, EXPRESSION_PASS),
  m_lhs(lhs), m_rhs(rhs) {}

Expression *AssignmentRefExpression::optimize(VariableEnvironment &env) {
  Eval::optimize(env, m_rhs);
  return NULL;
}

Variant AssignmentRefExpression::eval(VariableEnvironment &env) const {
  return m_lhs->setRef(env, m_rhs->refval(env));
}

Variant AssignmentRefExpression::refval(VariableEnvironment &env,
    int strict /* = 2 */) const {
  Variant tmp = strongBind(m_rhs->refval(env));
  m_lhs->setRef(env, tmp);
  return strongBind(tmp);
}

void AssignmentRefExpression::dump(std::ostream &out) const {
  m_lhs->dump(out);
  out << " = &";
  m_rhs->dump(out);
}

///////////////////////////////////////////////////////////////////////////////
}
}

