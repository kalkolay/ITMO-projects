package expression.generic;

public class Const<T extends Number> implements TripleExpression<T> {
    private T val;

    public Const(T val) {
        this.val = val;
    }

    public T evaluate(T x, T y, T z) {
        return val;
    }
}