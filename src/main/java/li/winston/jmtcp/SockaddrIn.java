package li.winston.jmtcp;

import org.apache.commons.validator.routines.InetAddressValidator;

public class SockaddrIn {

    public static final short AF_INET = 2;
    public static final int SOCK_STREAM = 1;

    public short sin_family;
    public String sin_addr;
    public int port;

    public SockaddrIn(short sin_family, String sin_addr, int port) {
        assert sin_family == AF_INET;
        assert InetAddressValidator.getInstance().isValidInet4Address(sin_addr);
        assert port >= 0 && port < 65535;
        this.sin_family = sin_family;
        this.sin_addr = sin_addr;
        this.port = port;
    }

    public SockaddrIn(String sin_addr, int port) {
        this(AF_INET, sin_addr, port);
    }

}
