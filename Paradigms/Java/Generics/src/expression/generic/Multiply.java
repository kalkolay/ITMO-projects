package expression.generic;

public class Multiply<T extends Number> extends BinaryOperation<T> {
    public Multiply(TripleExpression<T> l, TripleExpression<T> r, Operation<T> operation) {
        super(l, r, operation::multiply);
    }
}