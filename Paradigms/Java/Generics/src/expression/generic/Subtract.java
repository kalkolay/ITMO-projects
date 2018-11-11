package expression.generic;

public class Subtract<T extends Number> extends BinaryOperation<T> {
    public Subtract(TripleExpression<T> l, TripleExpression<T> r, Operation<T> operation) {
        super(l, r, operation::subtract);
    }
}