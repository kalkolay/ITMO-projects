package expression.generic;

public class OpInteger implements Operation<Integer> {
    private boolean checkOverflow;

    public OpInteger(boolean checkOverflow) {
        this.checkOverflow = checkOverflow;
    }

    public Integer add(Integer a, Integer b) {
        if (checkOverflow) {
            if (((a ^ (a + b)) & (b ^ (a + b))) < 0) {
                throw new OverflowException();
            }
        }
        return a + b;
    }

    public Integer subtract(Integer a, Integer b) {
        if (checkOverflow) {
            if (((a ^ b) & (a ^ (a - b))) < 0) {
                throw new OverflowException();
            }
        }
        return a - b;
    }

    private void checkMultiply(Integer a, Integer b) {
        if ((a > 0 && a > Integer.MAX_VALUE / b) // Т.к. a < b , то проверка b > 0 ненужна
                || (a < 0 && b < 0 && a < Integer.MAX_VALUE / b)
                || (a < 0 && b > 0 && a < Integer.MIN_VALUE / b)) {
            throw new OverflowException();
        }
    }

    public Integer multiply(Integer a, Integer b) {
        if (a > b) {
            int buf = a;
            a = b;
            b = buf;
        }
        if (checkOverflow) {
            checkMultiply(a, b);
        }
        return a * b;
    }

    public Integer divide(Integer a, Integer b) {
        if (checkOverflow) {
            if (b == 0) {
                throw new DBZException();
            } else if (a == Integer.MIN_VALUE && b == -1) {
                throw new OverflowException();
            }
        }
        return a / b;
    }

    public Integer mod(Integer a, Integer b) {
        return a % b;
    }

    public Integer abs(Integer f) {
        if (checkOverflow) {
            if (f == Integer.MIN_VALUE) {
                throw new OverflowException();
            }
        }
        return f < 0 ? -f : f;
    }

    public Integer negate(Integer f) {
        if (checkOverflow) {
            if (f == Integer.MIN_VALUE) {
                throw new OverflowException();
            }
        }
        return -f;
    }

    public Integer square(Integer f) {
        if (checkOverflow) {
            checkMultiply(f, f);
        }
        return f * f;
    }

    public Integer cnst(String s) {
        return Integer.parseInt(s);
    }

    public Integer mode(int m) {
        return m;
    }
}
