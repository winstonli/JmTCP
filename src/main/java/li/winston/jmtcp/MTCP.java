package li.winston.jmtcp;

import java.nio.ByteBuffer;

public class MTCP {

    static {
        try {
            System.loadLibrary("jmtcp");
        } catch (Throwable t) {
            System.err.println("Failed to load jlibmtcp.so. Make sure you run " +
                    "the JVM with -Djava.library.path=<path to libmtcp.so>.");
            t.printStackTrace();
        }
    }

    public static native int mtcp_init(String config_file);

    public static native void mtcp_destroy();

    public static native int mtcp_getconf(MtcpConf conf);

    public static native int mtcp_setconf(MtcpConf conf);

    public static native int mtcp_core_affinitize(int cpu);

    public static native long mtcp_create_context(int cpu);

    public static native void mtcp_destroy_context(long mctx);

    public static native MtcpSighandler mtcp_register_signal(int signum,
                                                      MtcpSighandler handler);

    public static native int mtcp_pipe(long mctx, int[] pipeid);

    public static native int mtcp_getsockopt(long mctx,
                                             int sockid,
                                             int level,
                                             int optname,
                                             int[] optval);

    public static native int mtcp_setsockopt(MtcpConf mctx,
                                             int sockid,
                                             int level,
                                             int optname,
                                             int[] optval);

    public static native int mtcp_setsock_nonblock(long mctx,
                                                   int sockid);

    public static native int mtcp_socket_ioctl(long mctx,
                                               int sockid,
                                               int request,
                                               int[] argp);

    public static native int mtcp_socket(long mctx,
                                         int domain,
                                         int type,
                                         int protocol);

    public static native int mtcp_bind(long mctx,
                                       int sockid,
                                       final SockaddrIn addr);

    public static native int mtcp_listen(long mctx, int sockid, int backlog);

    public static native int mtcp_accept(long mctx,
                                         int sockid,
                                         SockaddrIn addr);

    public static native int mtcp_init_rss(long mctx,
                                           String saddr_base,
                                           int num_addr,
                                           String daddr,
                                           int dport);

    public static native int mtcp_connect(long mctx,
                                          int sockid,
                                          final SockaddrIn addr);

    public static native int mtcp_close(long mctx, int sockid);

    public static native int mtcp_abort(long mctx, int sockid);

    public static native int mtcp_read(long mctx,
                                       int sockid,
                                       byte[] buf);

    public static native int mtcp_readv(long mctx,
                                        int sockid,
                                        byte[][] iov);

    public static native int mtcp_write(long mctx,
                                        int sockid,
                                        ByteBuffer buf);

    public static native int mtcp_writev(long mctx,
                                         int sockid,
                                         byte[][] iov);

    public static native int mtcp_epoll_create(long mctx, int size);

    public static native int mtcp_epoll_ctl(long mctx,
                                            int epid,
                                            int op,
                                            int sockid,
                                            int event,
                                            long data);

    public static native int mtcp_epoll_wait(long mctx,
                                             int epid,
                                             ByteBuffer events,
                                             int timeout);

    public static native int errno();

    public static native void set_errno(int new_errno);

}
