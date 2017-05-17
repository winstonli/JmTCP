package li.winston.jmtcp;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.channels.UnsupportedAddressTypeException;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import static li.winston.jmtcp.MTCP.*;

public class FastSocketChannel extends SocketChannel {

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

    private boolean readyToRead;
    private boolean readyToWrite;
    private boolean blocking;

    protected FastSocketChannel() {
        super(null);
        readyToRead = false;
        readyToWrite = false;
        blocking = true;
    }

    @Override
    public SocketChannel bind(SocketAddress local) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public <T> SocketChannel setOption(SocketOption<T> name, T value) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public <T> T getOption(SocketOption<T> name) throws IOException {
        throw new UnsupportedOperationException();
    }

    static final Set<SocketOption<?>> supportedOptions = defaultOptions();

    private static Set<SocketOption<?>> defaultOptions() {
        Set<SocketOption<?>> options = new HashSet<SocketOption<?>>(8);
        options.add(StandardSocketOptions.SO_SNDBUF);
        options.add(StandardSocketOptions.SO_RCVBUF);
        options.add(StandardSocketOptions.SO_KEEPALIVE);
        options.add(StandardSocketOptions.SO_REUSEADDR);
        options.add(StandardSocketOptions.SO_LINGER);
        options.add(StandardSocketOptions.TCP_NODELAY);
        options.add(StandardSocketOptions.IP_TOS);
        options.add(new SocketOption<Boolean>() {

            @Override
            public String name() {
                return "SO_OOBINLINE";
            }

            @Override
            public Class<Boolean> type() {
                return Boolean.class;
            }

            @Override
            public String toString() {
                return name();
            }

        });
        return Collections.unmodifiableSet(options);
    }

    @Override
    public Set<SocketOption<?>> supportedOptions() {

        throw new UnsupportedOperationException();
    }

    @Override
    public SocketChannel shutdownInput() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public SocketChannel shutdownOutput() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public Socket socket() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean isConnected() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean isConnectionPending() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean connect(SocketAddress remote) throws IOException {
        assert remote != null;
        if (!(remote instanceof InetSocketAddress)) {
            throw new UnsupportedAddressTypeException();
        }
        InetSocketAddress isa = (InetSocketAddress) remote;
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
        boolean ret = connect_ret >= 0 || errno() == Errno.EINPROGRESS;
        if (ret) {
            mtcp_epoll_ctl(
                mtcp_ctx,
                epoll_id,
                MtcpEpollEvent.MTCP_EPOLL_CTL_ADD,
                sockFD,
                MtcpEpollEvent.MTCP_EPOLLOUT | MtcpEpollEvent.MTCP_EPOLLIN,
                sockFD
            );
        }
        return ret;
    }

    @Override
    public boolean finishConnect() throws IOException {
        return true;
    }

    @Override
    public SocketAddress getRemoteAddress() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public int read(ByteBuffer dst) throws IOException {
        if (!blocking) {
            throw new UnsupportedOperationException();
        }
        while (!readyToRead) {

        }
        return 0;
    }

    @Override
    public long read(ByteBuffer[] dsts, int offset, int length) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public int write(ByteBuffer src) throws IOException {
        return 0;
    }

    @Override
    public long write(ByteBuffer[] srcs, int offset, int length) throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public SocketAddress getLocalAddress() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    protected void implCloseSelectableChannel() throws IOException {

    }

    @Override
    protected void implConfigureBlocking(boolean block) throws IOException {
        blocking = block;
    }

}
