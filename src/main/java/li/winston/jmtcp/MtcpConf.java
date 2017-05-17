package li.winston.jmtcp;

public class MtcpConf {

    public int num_cores;
    public int max_concurrency;

    public int max_num_buffers;
    public int rcvbuf_size;
    public int sndbuf_size;

    public int tcp_timewait;
    public int tcp_timeout;

    public MtcpConf(int num_cores,
                    int max_concurrency,
                    int max_num_buffers,
                    int rcvbuf_size,
                    int sndbuf_size,
                    int tcp_timewait,
                    int tcp_timeout) {
        this.num_cores = num_cores;
        this.max_concurrency = max_concurrency;
        this.max_num_buffers = max_num_buffers;
        this.rcvbuf_size = rcvbuf_size;
        this.sndbuf_size = sndbuf_size;
        this.tcp_timewait = tcp_timewait;
        this.tcp_timeout = tcp_timeout;
    }

    public MtcpConf() {

    }

}
