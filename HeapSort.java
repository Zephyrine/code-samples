import java.io.*;
import java.util.StringTokenizer;

public class HeapSort {
    private int[] data;
    private int hsize;

    private FastScanner in;
    private PrintWriter out;

    public static void main(String[] args) throws IOException {
        new HeapSort().solve();
    }

    private static int leftChild(int i) {
        return 2*i + 1;
    }

    private static int rightChild(int i) {
        return 2*i + 2;
    }

    private static int parent(int i) {
        return (i-1)/2;
    }

    private void readData() throws IOException {
        int n = in.nextInt();
        data = new int[n];
        for (int i = 0; i < n; ++i) {
            data[i] = in.nextInt();
        }
        hsize = n;
    }

    private void writeResponse() {
        for (int i : data) {
            out.print(i + " ");
            out.println("");
        }
    }

    private void SiftDown(int i) {
        while (true) {
            int lh = leftChild(i);
            if (lh >= hsize) {
                break;
            }
            int maxIndex = i;
            if (data[lh] > data[maxIndex]) {
                maxIndex = lh;
            }
            int rh = rightChild(i);
            if ((rh < hsize) && (data[rh] > data[maxIndex])) {
                maxIndex = rh;
            }
            if (i != maxIndex) {
                int temp = data[i];
                data[i] = data[maxIndex];
                data[maxIndex] = temp;
                i = maxIndex;
            } else {
                break;
            }
        }
    }

    private void buildHeap() {
        for (int i = (hsize-1)/2; i >= 0; --i) {
            SiftDown(i);
        }
    }

    private void doSort() {
        for (int i = data.length - 1; i >= 1; --i) {
            int temp = data[i];
            data[i] = data[0];
            data[0] = temp;
            --hsize;
            SiftDown(0);
        }
    }

    void solve() throws IOException {
        in = new FastScanner();
        out = new PrintWriter(new BufferedOutputStream(System.out));
        readData();
        buildHeap();
        doSort();
        writeResponse();
        out.close();
    }

    static class FastScanner {
        private BufferedReader reader;
        private StringTokenizer tokenizer;

        FastScanner() {
            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
        }

        String next() throws IOException {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
