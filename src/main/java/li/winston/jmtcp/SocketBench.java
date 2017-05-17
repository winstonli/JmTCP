package li.winston.jmtcp;

import org.apache.commons.validator.routines.InetAddressValidator;

import java.io.File;

import static li.winston.jmtcp.MTCP.*;

/**
 * Created by winston on 01/01/16.
 */
public class SocketBench {

    public static void main(String[] args) {
        if (args.length < 5) {
            System.err.println("usage: socketbench [mtcp_conf_path] [target_host] [target_port] [bufsize] [cnt]");
            System.exit(1);
        }
        File file = new File(args[0]);
        if (!file.exists()) {
            System.err.println("file at " + args[0] + " does not exist");
            System.exit(1);
        }
        if (!InetAddressValidator.getInstance().isValid(args[1])) {
            System.err.println("invalid destination ip: " + args[1]);
            System.exit(1);
        }
        if (args[2].length() > 5) {
            System.err.println("invalid target port: " + args[2]);
            System.exit(1);
        }
        int target_port = Integer.parseInt(args[2]);
        if (target_port > 65535 || target_port < 0) {
            System.err.println("invalid target port: " + args[2]);
            System.exit(1);
        }
        int bufsize = Integer.parseInt(args[3]);
        if (bufsize < 0) {
            System.err.println("invalid bufsize: " + bufsize);
            System.exit(1);
        }
        int cnt = Integer.parseInt(args[4]);
        if (cnt < 0) {
            System.err.println("invalid cnt: " + cnt);
            System.exit(1);
        }

        int mtcp_init_ret = mtcp_init(args[0]);
        if (mtcp_init_ret != 0) {
            System.err.println("mTCP failed to init");
            System.exit(1);
        }

        SbApp app = new SbApp(args[1], target_port, bufsize, cnt);
        app.run();

        mtcp_destroy();

        System.exit(0);
    }

}
