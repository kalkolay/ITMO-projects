package expression.generic;

import java.util.Arrays;
import java.util.List;

public class ExpressionParser<T extends Number> implements Parser<T> {
    private String expression;
    private int pointer;
    private String curOp;
    private int curOpIndex;
    private Operation<T> operation;
    private final List<String> correctOps = Arrays.asList("abs", "square", "min", "max", "mod");
    private final List<String> correctVars = Arrays.asList( "x", "y", "z");

    public ExpressionParser(Operation<T> operation) {
        this.operation = operation;
    }

    private void skipSpaces() {
        while (pointer < expression.length() && Character.isWhitespace(expression.charAt(pointer))) {
            pointer++;
        }
    }

    private void isCorrect(String op) throws ParsingException {
        if (!op.isEmpty()) {
            if (Character.isLetter(op.charAt(0))) {
                if (!(correctOps.contains(op) || correctVars.contains(op))) {
                    throw new ParsingException(String.format("Unknown identifier at index %d is %s", pointer + 1, op));
                }
            } else if (!Character.isDigit(op.charAt(0)) && !"+-*/()".contains("" + op.charAt(0))) {
                throw new ParsingException(String.format("Unknown symbol at index %d is %s", pointer + 1, expression.charAt(pointer)));
            }
        }
    }

    private String getIdentifier() {
        if (pointer < expression.length()) {
            if (Character.isLetter(expression.charAt(pointer))) {
                int i = pointer;
                while (i < expression.length() && (Character.isLetter(expression.charAt(i)) || Character.isDigit(expression.charAt(i)))) {
                    i++;
                }
                return expression.substring(pointer, i);
            } else {
                return "" + expression.charAt(pointer);
            }
        } else {
            return "";
        }
    }

    private boolean testOperation(String operation) throws ParsingException {
        skipSpaces();

        isCorrect(getIdentifier());
        if (expression.startsWith(operation, pointer)) {
            curOpIndex = pointer;
            pointer += operation.length();
            curOp = operation;
            return true;
        } else {
            return false;
        }
    }

    public TripleExpression<T> parse(String expression) throws ParsingException {
        this.expression = expression;
        pointer = 0;
        skipSpaces();
        if (expression.isEmpty()) {
            throw new ParsingException("Empty expression");
        }
        TripleExpression<T> result = parseAddSub();
        if (pointer < expression.length()) {
            if (expression.charAt(pointer) == ')') {
                throw new ParsingException(String.format("Missing opening bracket at index %d", pointer + 1));
            } else {
                throw new ParsingException(String.format("Unknown identifier at index %d is %s", pointer + 1, getIdentifier()));
            }
        }
        return result;
    }

    private TripleExpression<T> parseAddSub() throws ParsingException {
        TripleExpression<T> result = parseMulDivMod();
        while (true) {
            if (testOperation("+")) {
                result = new Add<>(result, parseMulDivMod(), operation);
            } else if (testOperation("-")) {
                result = new Subtract<>(result, parseMulDivMod(), operation);
            } else {
                return result;
            }
        }
    }

    private TripleExpression<T> parseMulDivMod() throws ParsingException {
        TripleExpression<T> result = parseUnary();
        while (true) {
            if (testOperation("*")) {
                result = new Multiply<>(result, parseUnary(), operation);
            } else if (testOperation("/")) {
                result = new Divide<>(result, parseUnary(), operation);
            } else  if (testOperation("mod")) {
                result = new Mod<>(result, parseUnary(), operation);
            } else {
                return result;
            }
        }
    }

    private TripleExpression<T> parseUnary() throws ParsingException {
        if (testOperation("-")) {
            if (!Character.isDigit(expression.charAt(pointer))) {
                return new Negate<>(parseUnary(), operation);
            } else {
                return new Const<>(parseNumber("-"));
            }
        } else if (testOperation("abs")) {
            return new Abs<>(parseUnary(), operation);
        } else if (testOperation("square")) {
            return new Square<>(parseUnary(), operation);
        } else if (testOperation("(")) {
            TripleExpression<T> result = parseAddSub();
            if (pointer == expression.length() || expression.charAt(pointer) != ')') {
                throw new ParsingException(String.format("Missing closing bracket at index %d", pointer));
            }
            pointer++;
            return result;
        } else if (parseVar()) {
            return new Variable<>("" + expression.charAt(pointer - 1));
        } else {
            return new Const<>(parseNumber(""));
        }
    }

    private boolean parseVar() {
        if (pointer < expression.length() && correctVars.contains(expression.substring(pointer, pointer + 1))) {
            pointer++;
            return true;
        } else {
            return false;
        }
    }


    private T parseNumber(String flag) throws ParsingException {
        int r = pointer;
        while (r < expression.length() && Character.isDigit(expression.charAt(r))) {
            r++;
        }
        if (pointer == r) {
            if (curOpIndex == 0 && curOp == null) {
                throw new ParsingException(String.format("Argument missing before (%s) at index 1", getIdentifier()));
            } else {
                throw new ParsingException(String.format("Argument missing after (%s) at index %d", curOp, curOpIndex + 1));
            }
        }
        String number = flag + expression.substring(pointer, r);
        pointer = r;
        try {
            return operation.cnst(number);
        } catch (NumberFormatException e) {
            throw new ParsingException("Overflow at index " + (pointer - number.length() + 1) + " is " + number);
        }
    }
}
