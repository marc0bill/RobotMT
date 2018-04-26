from multiprocessing import Process, Queue
import time

def f1(q):
    time.sleep(5)
    q.put([42, None, 'hello'])

def f2(q):
    print('start f2')
    while q.empty() :
        print('rien recu')
        time.sleep(1)

    print(q.get()) # conn est bloquant

if __name__ == '__main__':
    q = Queue()
    p1 = Process(target=f1, args=(q,))
    p2 = Process(target=f2, args=(q,))
    p1.start()
    p2.start()

    p1.join()
    p2.join()