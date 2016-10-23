import java.util.Random;
import java.util.concurrent.Semaphore;

public class SemaphoreDemo {
    public static void main(String[] args) throws InterruptedException {
        int slot_number = 0, c_work = 0, c_sleep = 0, p_work = 0, p_sleep = 0;

        if (args.length != 5) {
            System.err.println("Wrong number of arguments!");
            System.exit(-1);
        } else {
            try {
                slot_number = Integer.parseInt(args[0]);
                c_work = Integer.parseInt(args[1]);
                c_sleep = Integer.parseInt(args[2]);
                p_work = Integer.parseInt(args[3]);
                p_sleep = Integer.parseInt(args[4]);
            } catch (NumberFormatException e) {
                System.err.println("The format of arguments is not correct!");
                System.exit(-1);
            }
        }

        SemaphoreDemo sdemo = new SemaphoreDemo(slot_number);
        sdemo.demo(c_sleep, c_work, p_sleep, p_work);
    }

    private static final Random rand = new Random();

    private Semaphore empty;  // empty slot counter
    private Semaphore full;  // full slot counter
    private final Object mutex = new Object();  // a dummy mutex for critical region access

    private int task_count = 0;
    private String[] task_buffer;  // a limit length task slot

    SemaphoreDemo (int capacity) throws InterruptedException {
        task_buffer = new String[capacity];
        empty = new Semaphore(capacity, true);  // empty = capacity
        full = new Semaphore(capacity, true);
        full.acquire(capacity);  // full = 0
    }

    private void demo(int c1, int c2, int p1, int p2) {
        Thread customer_thread = new Thread(new Customer(c1, c2));
        Thread producer_thread = new Thread(new Producer(p1, p2));
        customer_thread.start();
        producer_thread.start();
    }

    private abstract class AbstractMan implements Runnable {
        private Thread t;
        private Semaphore first, second;
        private int max_time_in_cr;
        private int max_time_sleep;

        protected int critical_counter = 0;
        protected String name;

        AbstractMan(String name, Semaphore first, Semaphore second,
                    int max_time_in_cr, int max_time_sleep) {
            this.first = first;
            this.second = second;
            this.max_time_in_cr = max_time_in_cr;
            this.max_time_sleep = max_time_sleep;
            this.name = name;
        }

        protected abstract void critical_region();

        public void run() {
            long last_time = System.currentTimeMillis();
            while (true) {
                long elapse_time = System.currentTimeMillis() - last_time;

                try {
                    if (elapse_time <= max_time_sleep)
                        Thread.sleep(rand.nextInt((int)(max_time_sleep - elapse_time) + 1));

                    first.acquire();
                    synchronized (mutex) {  // enter critical region
                        critical_counter++;
                        critical_region();
                        Thread.sleep(rand.nextInt(1+max_time_in_cr));
                    } // leave critical region
                    second.release();
                } catch (InterruptedException e) {
                    break;
                } finally {
                    last_time = System.currentTimeMillis();
                }
            }
        }

        public void start() {
            if (t == null) {
                t = new Thread (this);
                t.start();
            }
        }
    }

    private final class Producer extends AbstractMan {
        Producer(int time_produce, int time_sleep) {
            super("P", empty, full, time_produce, time_sleep);
        }

        protected void critical_region() {
            String task = name + "_" + critical_counter;
            task_buffer[task_count++] = task;
            System.out.printf("[%s] submit %s at slot #%d\n", name, task, task_count);
        }
    }

    private final class Customer extends AbstractMan {
        Customer(int time_consume, int time_sleep) {
            super("C", full, empty, time_consume, time_sleep);
        }

        protected void critical_region() {
            String task = task_buffer[--task_count];
            System.out.printf("[%s] finish %s at slot #%d\n", name, task, task_count + 1);
        }
    }
}