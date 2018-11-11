package expression.generic;

public class OpDouble implements Operation<Double> {
    public Double add(Double a, Double b) {
        return a + b;
    }

    public Double subtract(Double a, Double b) {
        return a - b;
    }

    public Double multiply(Double a, Double b) {
        return a * b;
    }

    public Double divide(Double a, Double b) {
        return a / b;
    }

    public Double mod(Double a, Double b) {
        return a % b;
    }

    public Double abs(Double f) {
        return f < 0 ? -f : f;
    }

    public Double negate(Double f) {
        return -f;
    }

    public Double square(Double f) {
        return f * f;
    }

    public Double cnst(String s) {
        return Double.parseDouble(s);
    }

    public Double mode(int m) {
        return (double) m;
    }
}
