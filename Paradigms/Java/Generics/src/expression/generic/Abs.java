package expression.generic;

public class Abs<T extends Number> extends UnaryOperation<T> {
    public Abs(TripleExpression<T> f, Operation<T> operation) {
        super(f, operation::abs);
    }
}