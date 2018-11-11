package expression.generic;

public interface Operation<T extends Number> {
    T add(T a, T b);
    T subtract(T a, T b);
    T multiply(T a, T b);
    T divide(T a, T b);
    T mod(T a, T b);
    T abs(T f);
    T negate(T f);
    T square(T f);
    T cnst(String s);
    T mode(int m);
}
