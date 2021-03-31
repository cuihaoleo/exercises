from threading import Lock, Semaphore


class AtomicCounter:
    def __init__(self):
        self.lock = Lock()
        self.counter = 0

    def inc(self):
        with self.lock:
            self.counter += 1
            return self.counter

class H2O:
    def __init__(self):
        self.H_counter = AtomicCounter()
        self.H_sem = Semaphore(2)

        self.O_lock = Lock()
        self.O_lock.acquire()

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.H_sem.acquire()

        releaseHydrogen()

        if self.H_counter.inc() & 1 == 0:
            self.O_lock.release()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.O_lock.acquire()

        releaseOxygen()

        self.H_sem.release()
        self.H_sem.release()
