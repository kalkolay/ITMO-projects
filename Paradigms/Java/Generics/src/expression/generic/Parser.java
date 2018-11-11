package expression.generic;

public interface Parser<T extends Number> {
    TripleExpression<T> parse(String expression) throws ParsingException;
}
