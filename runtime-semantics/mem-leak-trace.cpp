#include <stdlib.h>  
#include <iostream>  
#include <map>  
#include <string>  
#include <string.h>  
#include <vector>  
#include <pthread.h>
#include <unistd.h>
using namespace std;  
  
class Tracer  
{  
private:  
    class Entry  
    {  
    public:  
        Entry (char const * file, int line)  
            : _file (file), _line (line)  
        {}  
        Entry ()  
            : _file (0), _line (0)  
        {}  
        char const * File () const { return _file; }  
        int Line () const { return _line; }  
    private:  
        char const * _file;  
        int _line;  
    };  
  
    class Lock  
    {  
    public:  
        Lock (Tracer & tracer)  
            : _tracer (tracer)  
        {  
            _tracer.lock ();  
        }  
        ~Lock ()  
        {  
            _tracer.unlock ();  
        }  
    private:  
        Tracer & _tracer;  
    };  
  
  
  
public:  
    Tracer ();  
    ~Tracer ();  
    void Add (void * p, char const * file, int line);  
    void Remove (void * p);  
    void Dump ();  
  
    static bool Ready;  
    static bool map_add; //avoid infinite recursive..cause map add will new a map entry
  
private:  
    void lock () { pthread_mutex_lock(&mutex); }  
    void unlock () { pthread_mutex_unlock(&mutex); }  
  
private:  
    typedef std::map<void *, Entry>::iterator iterator;  
    std::map<void *, Entry> _map;  
    int _lockCount;
    pthread_mutex_t mutex;
};  
  
bool Tracer::Ready = false;  
bool Tracer::map_add = false;
  
Tracer::Tracer():_lockCount(0)  
{  
	Ready = true;  
	map_add = false;

	pthread_mutexattr_t Attr;
	pthread_mutexattr_init(&Attr);
	pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &Attr);
}  
  
Tracer::~Tracer()  
{  
        Ready = false;  
        Dump();  
	cout << "Tracer::~Tracer" << endl;
}  
  
void Tracer::Dump()  
{  
        cout << "Dump _map.size()=" << _map.size() << endl;  
#if 0
        if (_map.size() != 0)  
        {  
                cout << _map.size() << " memory leaks detected" << endl;  
                for (iterator itor = _map.begin(); itor != _map.end(); ++itor)  
                {  
                        char const* file = itor->second.File();  
                        int line = itor->second.Line();  
                        cout << file << ", " << line << endl;  
                }  
        }  
#endif
}  
  
void Tracer::Add(void *p, const char *file, int line)  
{  
        Tracer::Lock lock(*this);  
	map_add = true;
        _map[p] = Entry(file, line);  
	map_add = false;
}  
 
void Tracer::Remove(void *p)  
{  
        Tracer::Lock lock(*this);  
  
        iterator itor = _map.find(p);  
        if (itor != _map.end())  {
                _map.erase(itor);  
	}
}  
  
/*extern*/ Tracer gNewTracer;  
  
void* operator new (size_t size, const char* file, int line)  
{  
	//cout << "operator new (size_t size, const char* file, int line)" << endl;
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, file, line);  
	//cout << "operator new (size_t, const char*, int)=" <<size << " p=" << (long*)p << endl;
        return p;  
}  
  
void operator delete(void* p, const char* file, int line)  
{  
	//cout << "operator delete(void*, const char*, int)=" << (long*)p << endl;
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new (size_t size)  
{  
	//cout << "operator new (size_t )=" << size << endl;
        void* p = malloc(size);  
        if (Tracer::Ready && Tracer::map_add == false)  
                gNewTracer.Add(p, "?", 0);  
	//cout << "operator new (size_t )=" << size <<" p=" << (long*)p << endl;
        return p;  
}  
  
void operator delete(void* p)  
{  
	//cout << "operator delete(void*)=" << (long*)p<< endl;
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new [](size_t size, const char* file, int line)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, file, line);  
	cout << "operator new [](size_t, const char*, int)=" << size << " p= " << (long*)p <<  endl;
        return p;  
}  
  
void operator delete[](void* p, const char* file, int line)  
{  
	cout << "operator delete[](void*, const char*, int)=" <<(long*)p << endl;
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new[] (size_t size)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, "?", 0);  
	cout << "operator new[] (size_t)=" << size << " p=" << (long*)p << endl;
        return p;  
}  
  
void operator delete[](void* p)  
{  
        //cout << "delete[](void* )=" << (long*)p <<endl;  
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
#define new new(__FILE__, __LINE__)  
  
class X {
private:
	long mi[1000];
};

pthread_t pid1;
pthread_t pid2;

void *thread1(void* argv)
{
	cout << "thread1\n";
	int i=0;
	while(i<10000000) {
		int *a = new int(3);
		a = a;
		i++;
	}
	return 0;
}

void *thread2(void* argv)
{
	cout << "thread2\n";
	int i=0;
	while(i<10000000) {
		int *a = new int(4);
		a = a;
		i++;
	}
	return 0;
}

int main(int argc, char *argv[])  
{  
	pthread_create(&pid1, NULL, thread1, NULL) ;
	pthread_create(&pid2, NULL, thread2, NULL) ;

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);
        return 0;  
} 
