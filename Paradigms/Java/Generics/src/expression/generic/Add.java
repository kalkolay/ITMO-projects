package expression.generic;

public class Add<T extends Number> extends BinaryOperation<T> {
    public Add(TripleExpression<T> l, TripleExpression<T> r, Operation<T> operation) {
        super(l, r, operation::add);
    }
}