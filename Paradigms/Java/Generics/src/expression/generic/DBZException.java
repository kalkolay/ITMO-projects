package expression.generic;

public class DBZException extends RuntimeException {
    public DBZException() {
        super("division by zero");
    }
}
