// C++ program to illustrate the use of condition variable 
#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <thread> 
  
using namespace std; 
  
// condition variable and mutex lock 
condition_variable cv; 
mutex m; 
  
// shared resource 
int val = 0; 
  
void add(int num) 
{ 
    lock_guard<mutex> lock(m); 
    val += num; 
    cout << "After addition: " << val << endl; 
    cv.notify_one(); 
} 
  
void sub(int num) 
{ 
    unique_lock<mutex> ulock(m); 
    cv.wait(ulock, 
            [] { return (val != 0) ? true : false; }); 
    if (val >= num) { 
        val -= num; 
        cout << "After subtraction: " << val << endl; 
    } 
    else { 
        cout << "Cannot Subtract now!" << endl; 
    } 
    cout << "Total number Now: " << val << endl; 
} 
  
// driver code 
int main() 
{ 
    thread t2(sub, 600); 
    thread t1(add, 900); 
    t1.join(); 
    t2.join(); 
    return 0; 
}