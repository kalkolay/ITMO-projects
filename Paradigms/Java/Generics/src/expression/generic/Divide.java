package expression.generic;

public class Divide<T extends Number> extends BinaryOperation<T> {
    public Divide(TripleExpression<T> l, TripleExpression<T> r, Operation<T> operation) {
        super(l, r, operation::divide);
    }
}