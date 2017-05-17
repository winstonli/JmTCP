package li.winston.jmtcp;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.*;
import java.nio.channels.UnsupportedAddressTypeException;

import static li.winston.jmtcp.MTCP.*;

public class FastSocketImpl extends SocketImpl {

    public static final int EPOLL_SIZE = 100;

    static {
        init();
    }

    public static long mtcp_ctx;
    public static int epoll_id;

    static void init() {
        String mtcpConf = System.getProperty("li.winston.mtcp.conf");
        if (mtcpConf != null) {
            mtcp_init(mtcpConf);
            mtcp_core_affinitize(0);
            mtcp_ctx = mtcp_create_context(0);
            epoll_id = mtcp_epoll_create(mtcp_ctx, EPOLL_SIZE);
        } else {
            System.err.println("li.winston.mtcp.conf not set. mTCP not enabled.");
        }
    }

    private InputStream in;
    private OutputStream out;

    @Override
    protected void create(boolean stream) throws IOException {
        if (!stream) {
            throw new UnsupportedOperationException("can't create a datagram socket");
        }
    }

    @Override
    protected void connect(String host, int port) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void connect(InetAddress address, int port) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void connect(SocketAddress address, int timeout) throws IOException {
        assert address != null;
        if (!(address instanceof InetSocketAddress)) {
            throw new UnsupportedAddressTypeException();
        }
        InetSocketAddress isa = (InetSocketAddress) address;
        InetAddress addr = isa.getAddress();
        if (!(addr instanceof Inet4Address)) {
            if (addr instanceof Inet6Address) {
                throw new UnsupportedOperationException("doesn't support ipv6");
            } else {
                throw new IllegalArgumentException("invalid address type");
            }
        }
        if (addr.isAnyLocalAddress()) {
            throw new UnsupportedOperationException("localhost not supported");
        }
        int sockFD = mtcp_socket(mtcp_ctx, SockaddrIn.AF_INET, SockaddrIn.SOCK_STREAM, 0);
        if (sockFD < 0) {
            int errno = errno();
            if (errno == Errno.ENFILE) {
                throw new IOException("too many open files");
            } else {
                throw new IllegalStateException("unexpected errno after mtcp_socket: " + errno);
            }
        }
        int nonblock_ret = mtcp_setsock_nonblock(mtcp_ctx, sockFD);
        assert nonblock_ret >= 0;

        int connect_ret = mtcp_connect(mtcp_ctx, sockFD, new SockaddrIn(isa.getHostString(), isa.getPort()));
        if (connect_ret < 0 && errno() != Errno.EINPROGRESS) {
            throw new IOException("unable to connect");
        }
        mtcp_epoll_ctl(
                mtcp_ctx,
                epoll_id,
                MtcpEpollEvent.MTCP_EPOLL_CTL_ADD,
                sockFD,
                MtcpEpollEvent.MTCP_EPOLLOUT | MtcpEpollEvent.MTCP_EPOLLIN,
                sockFD
        );

    }



    @Override
    protected void bind(InetAddress host, int port) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void listen(int backlog) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void accept(SocketImpl s) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected InputStream getInputStream() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected OutputStream getOutputStream() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected int available() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void close() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void sendUrgentData(int data) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public void setOption(int optID, Object value) throws SocketException {
        throw new UnsupportedOperationException();
    }

    @Override
    public Object getOption(int optID) throws SocketException {
        throw new UnsupportedOperationException();
    }

}
