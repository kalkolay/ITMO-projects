package expression.generic;

public class OpFloat implements Operation<Float> {
    public Float add(Float a, Float b) {
        return a + b;
    }

    public Float subtract(Float a, Float b) {
        return a - b;
    }

    public Float multiply(Float a, Float b) {
        return a * b;
    }

    public Float divide(Float a, Float b) {
        return a / b;
    }

    public Float mod(Float a, Float b) {
        return a % b;
    }

    public Float abs(Float f) {
        return f < 0 ? -f : f;
    }

    public Float negate(Float f) {
        return -f;
    }

    public Float square(Float f) {
        return f * f;
    }

    public Float cnst(String s) {
        return Float.parseFloat(s);
    }

    public Float mode(int m) {
        return (float) m;
    }
}
