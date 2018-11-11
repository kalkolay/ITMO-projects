package expression.generic;

import java.util.function.UnaryOperator;

abstract class UnaryOperation<T extends Number> implements TripleExpression<T> {
    private TripleExpression<T> f;
    private UnaryOperator<T> operator;

    protected UnaryOperation(TripleExpression<T> f, UnaryOperator<T> operator) {
        this.f = f;
        this.operator = operator;
    }

    public T evaluate(T x, T y, T z) {
        return operator.apply(f.evaluate(x, y, z));
    }
}
