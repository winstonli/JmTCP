package li.winston.jmtcp;

public class sb2 {

    static {
        try {
            Class.forName("li.winston.jmtcp.FastSocketChannel");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        System.out.println("Hello world");
    }

}
