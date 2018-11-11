package expression.generic;

public class Mod<T extends Number> extends BinaryOperation<T> {
    public Mod(TripleExpression<T> l, TripleExpression<T> r, Operation<T> operation) {
        super(l, r, operation::mod);
    }
}