package expression.generic;

public class Variable<T extends Number> implements TripleExpression<T> {
    private String name;

    public Variable(String name) {
        this.name = name;
    }

    public T evaluate(T x, T y, T z) {
        if (name.equals("x")) {
            return x;
        } else if (name.equals("y")){
            return y;
        } else {
            return z;
        }
    }
}		