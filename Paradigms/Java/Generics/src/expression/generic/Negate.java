package expression.generic;

public class Negate<T extends Number> extends UnaryOperation<T> {
    public Negate(TripleExpression<T> f, Operation<T> operation) {
        super(f, operation::negate);
    }
}