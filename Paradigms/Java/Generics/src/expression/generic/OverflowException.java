package expression.generic;

public class OverflowException extends RuntimeException {
    public OverflowException() {
        super("overflow");
    }
}