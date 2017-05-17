package li.winston.jmtcp;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import static li.winston.jmtcp.MTCP.*;

public class SbApp {

    private final String destIP;
    private final int destPort;
    private final int bufsize;
    private final int cnt;

    public SbApp(String destIP, int destPort, int bufsize, int cnt) {
        this.destIP = destIP;
        this.destPort = destPort;
        this.bufsize = bufsize;
        this.cnt = cnt;
    }

    public void run() {
        // init

        mtcp_core_affinitize(0);
        long mtcp_ctx = mtcp_create_context(0);

        //    mtcp_init_rss(
//        mtcp_ctx,
//        INADDR_ANY,
//        1,
//        sb_app_get_dest_in_addr(self),
//        sb_app_get_port_in_addr(self)
//    );

        // connect

        int epoll_id = mtcp_epoll_create(mtcp_ctx, 100);
        assert(epoll_id >= 0);

        ByteBuffer evs = ByteBuffer.allocateDirect(100 * (4 + 8)).order(ByteOrder.nativeOrder());

        int sock_fd = mtcp_socket(mtcp_ctx, SockaddrIn.AF_INET, SockaddrIn.SOCK_STREAM, 0);
        assert(sock_fd >= 0);
        int nonblock_ret = mtcp_setsock_nonblock(mtcp_ctx, sock_fd);
        assert(nonblock_ret >= 0);

        int connect_ret = mtcp_connect(
                mtcp_ctx,
                sock_fd,
                new SockaddrIn(destIP, destPort)
        );

        assert(connect_ret >= 0 || errno() == Errno.EINPROGRESS);

        mtcp_epoll_ctl(mtcp_ctx, epoll_id, MtcpEpollEvent.MTCP_EPOLL_CTL_ADD, sock_fd, MtcpEpollEvent.MTCP_EPOLLOUT, sock_fd);

        // do thing
        long start = System.currentTimeMillis();
        long last_update = 0;
        long bytes_written = 0;

    /* Number of bytes sent at a time */
        int bufsize = this.bufsize;
        ByteBuffer bufptr = ByteBuffer.allocateDirect(bufsize);
//    bufptr = get_huge_pages(bufsize * self->cnt, 0);
        //posix_memalign((void **) &bufptr, getpagesize(), bufsize * 1000);
        //if (bufptr == NULL) {
        //    perror("failed to memealign\n");
        //    exit(1);
        //}
        ByteBuffer curr = bufptr;
        int sent = 0;
        while (sent < cnt) {
            int num_events = mtcp_epoll_wait(mtcp_ctx, epoll_id, evs, -1);

            for (int i = 0; i < num_events; ++i) {
                int ev = evs.getInt(i * (4 + 8));
                if ((ev & MtcpEpollEvent.MTCP_EPOLLOUT) != 0) {
                    int write_ret = mtcp_write(mtcp_ctx, sock_fd, curr);
                    if (write_ret != -1) {
                        ++sent;
                        //curr = bufptr + ((sent % 1000) * bufsize);
                        bytes_written += write_ret;
                        long current = System.currentTimeMillis();
                        long time_passed = current - start;
                        long rate;
                        if (time_passed / 1000 == 0) {
                            rate = 0;
                        } else {
                            rate = (bytes_written / (time_passed / 1000)) / 1000;
                        }
                        if (current - last_update >= 1000 || time_passed == 60000) {
                            last_update = current;
                            System.out.println(rate + " kB/s (" + bytes_written + " written in " + (current - start) + ")");
                            if (time_passed >= 60000) {
                                mtcp_close(mtcp_ctx, sock_fd);
                                System.exit(0);
                            }
                        }
                    }
                } else if ((ev & MtcpEpollEvent.MTCP_EPOLLERR) != 0) {
                    System.err.println("Event error");
                } else {
                    System.err.println("Unknown event");
                }
            }

        }
        mtcp_close(mtcp_ctx, sock_fd);
//    printf("%i\n", num_written);

        // finish
        mtcp_destroy_context(mtcp_ctx);
    }

}
