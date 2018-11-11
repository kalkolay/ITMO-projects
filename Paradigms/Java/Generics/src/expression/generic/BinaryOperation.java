package expression.generic;

import java.util.function.BinaryOperator;

abstract class BinaryOperation<T extends Number> implements TripleExpression<T> {
    private TripleExpression<T> l;
    private TripleExpression<T> r;
    private BinaryOperator<T> operator;

    protected BinaryOperation(TripleExpression<T> l, TripleExpression<T> r, BinaryOperator<T> operator) {
        this.l = l;
        this.r = r;
        this.operator = operator;
    }

    public T evaluate(T x, T y, T z) {
        return operator.apply(l.evaluate(x, y, z), r.evaluate(x, y, z));
    }
}