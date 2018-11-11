package expression.generic;

public class GenericTabulator implements Tabulator {
    private Operation<?> getMode(String mode) throws Exception  {
        switch (mode) {
            case "i" : return new OpInteger(true);
            case "d" : return new OpDouble();
            case "bi" : return new OpBigInteger();
            case "u" : return new OpInteger(false);
            case "b" : return new OpByte();
            case "f" : return new OpFloat();
            default: throw new Exception("Unknown mode");
        }
    }
    private <T extends Number> Object[][][] newTable(Operation<T> operation, String expression, int x1, int x2, int y1, int y2, int z1, int z2) throws ParsingException {
        Object[][][] result = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        TripleExpression<T> expression1 = new ExpressionParser<>(operation).parse(expression);
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                for (int k = z1; k <= z2; k++) {
                    try {
                        result[i - x1][j - y1][k - z1] = expression1.evaluate(operation.mode(i), operation.mode(j),operation.mode(k));
                    } catch (Exception e) {
                        result[i - x1][j - y1][k - z1] = null;
                    }
                }
            }
        }
        return result;
    }

    public Object[][][] tabulate(String mode, String expression, int x1, int x2, int y1, int y2, int z1, int z2) throws Exception {
        return newTable(getMode(mode), expression, x1, x2, y1, y2, z1, z2);
    }
}
