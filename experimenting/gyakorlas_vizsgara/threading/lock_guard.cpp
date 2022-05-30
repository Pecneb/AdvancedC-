#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>

using namespace std;

int main() {

    condition_variable cond; /* condition for fns to notify each other if other fns free to run */
    mutex mtex;

    /* without mutex */
    auto calc1 = []() {

        cout << "thread " << this_thread::get_id() << " aquired lock >> sleeping for 5 seconds" << '\n';

        this_thread::sleep_for( chrono::seconds( 5 ) );

    };

    auto calc2 = []() {

        cout << "thread " << this_thread::get_id() << " aquired lock >> sleeping for 3 seconds" << '\n';

        this_thread::sleep_for( chrono::seconds( 3 ) );

    };

    /* with lock_guard< mutex > */
    auto compute1 = [&mtex, &cond]() {

        lock_guard< mutex > lock( mtex );

        cout << "thread " << this_thread::get_id() << " aquired lock >> sleeping for 5 seconds" << '\n';

        this_thread::sleep_for( chrono::seconds( 5 ) );

        cond.notify_one(); /* notify run_on_notify fn */

    };

    auto compute2 = [&mtex]() {

        lock_guard< mutex > lock( mtex );

        cout << "thread " << this_thread::get_id() << " aquired lock >> sleeping for 3 seconds" << '\n';

        this_thread::sleep_for( chrono::seconds( 3 ) );

    };


    auto run_on_notify = [&mtex, &cond]() {  
    
        unique_lock < mutex > lock( mtex ); 

        cond.wait( lock );

        cout << "aquired lock from someone who notified me\n";
        
    }; 

    /* thread calc1thread(calc1);
    thread calc2thread(calc2);

    calc1thread.join();
    calc2thread.join(); */

    thread notifThread(run_on_notify);

    thread compute1thread(compute1);
    thread compute2thread(compute2);

    auto asyncfn = async(launch::async, []() { cout << "thread " << this_thread::get_id() << " is run by async fn\n"; } );

    int val_for_asyncfn2 = 10;

    auto asyncfn2 = async(launch::async, 
        [](int x) -> int { 
            cout << "this value: " << x << " going to be multiplied by 1000\n";
            return x * 1000; 
        },
        val_for_asyncfn2);

    compute1thread.join();
    compute2thread.join();
    notifThread.join();
    cout << "this is the mupltiplied value: " << asyncfn2.get() << '\n';    
    asyncfn.get();

    return 0;

}