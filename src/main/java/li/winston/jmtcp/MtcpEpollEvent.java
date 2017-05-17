package li.winston.jmtcp;

public class MtcpEpollEvent {

    public static int MTCP_EPOLLNONE	= 0x000;
    public static int MTCP_EPOLLIN	= 0x001;
    public static int MTCP_EPOLLPRI	= 0x002;
    public static int MTCP_EPOLLOUT	= 0x004;
    public static int MTCP_EPOLLRDNORM	= 0x040;
    public static int MTCP_EPOLLRDBAND	= 0x080;
    public static int MTCP_EPOLLWRNORM	= 0x100;
    public static int MTCP_EPOLLWRBAND	= 0x200;
    public static int MTCP_EPOLLMSG		= 0x400;
    public static int MTCP_EPOLLERR		= 0x008;
    public static int MTCP_EPOLLHUP		= 0x010;
    public static int MTCP_EPOLLRDHUP 	= 0x2000;
    public static int MTCP_EPOLLONESHOT	= (1 << 30);
    public static int MTCP_EPOLLET		= (1 << 31);

    public static int MTCP_EPOLL_CTL_ADD = 1;
    public static int MTCP_EPOLL_CTL_DEL = 2;
    public static int MTCP_EPOLL_CTL_MOD = 3;

}
