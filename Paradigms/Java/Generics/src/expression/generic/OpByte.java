package expression.generic;

public class OpByte implements Operation<Byte> {
    public Byte add(Byte a, Byte b) {
        return (byte) (a + b);
    }

    public Byte subtract(Byte a, Byte b) {
        return (byte) (a - b);
    }

    public Byte multiply(Byte a, Byte b) {
        return (byte) (a * b);
    }

    public Byte divide(Byte a, Byte b) {
        if (b == 0) {
            throw new DBZException();
        }
        return (byte) (a / b);
    }

    public Byte mod(Byte a, Byte b) {
        return (byte) (a % b);
    }

    public Byte abs(Byte f) {
        return f < 0 ? (byte) (-f) : f;
    }

    public Byte negate(Byte f) {
        return (byte) (-f);
    }

    public Byte square(Byte f) {
        return (byte) (f * f);
    }

    public Byte cnst(String s) {
        return Byte.parseByte(s);
    }

    public Byte mode(int m) {
        return (byte) m;
    }
}
