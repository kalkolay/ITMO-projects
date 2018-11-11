package expression.generic;

public class Square<T extends Number> extends UnaryOperation<T> {
    public Square(TripleExpression<T> f, Operation<T> operation) {
        super(f, operation::square);
    }
}