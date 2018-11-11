package expression.generic;

import java.math.BigInteger;

public class OpBigInteger implements Operation<BigInteger> {
    public BigInteger add(BigInteger a, BigInteger b) {
        return a.add(b);
    }

    public BigInteger subtract(BigInteger a, BigInteger b) {
        return a.subtract(b);
    }

    public BigInteger multiply(BigInteger a, BigInteger b) {
        return a.multiply(b);
    }

    public BigInteger divide(BigInteger a, BigInteger b) {
        return a.divide(b);
    }

    public BigInteger mod(BigInteger a, BigInteger b) {
        return a.remainder(b);
    }

    public BigInteger abs(BigInteger f) {
        return f.compareTo(BigInteger.ZERO) < 0 ? f.negate() : f;
    }

    public BigInteger negate(BigInteger f) {
        return f.negate();
    }

    public BigInteger square(BigInteger f) {
        return f.multiply(f);
    }

    public BigInteger cnst(String s) {
        return new BigInteger(s);
    }

    public BigInteger mode(int m) {
        return BigInteger.valueOf(m);
    }
}
