#include <future>
#include <iostream>
#include <thread>
/*
    A   B   C

    option 1: One after the other. Always complete one 
            thing before starting the next task.

            NAME: Single thread technique 
//////////////////////////////////////////////////////////////////

    option 2: I will complete all tasks in such a way that I 
            "practically start all of them at the same time "
            but keep juggling them based on some criteria.

            NAME: Multi thtreading approach
//////////////////////////////////////////////////////////////////

    option 3: Map number of tasks amongst number of available "workers".

            NAME: Parallel Execution
//////////////////////////////////////////////////////////////////

    option 4: Start a task. Either deligate it to another worker OR
            do it yourself after some time.

            If someone else is dong a task, monitor it, wait for their 
            work to be done take follow-up actions accordingly.

            NAME: Asynchronous Execution
*/

/*
    * 2 tasks 
    Calculate factorial of 5
    Calculate Square of the number given by the user
*/

int square( std::future<int>& ft ){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"HELLO FROM SQUARE. I have started my work !!\n";
    int number = ft.get();
    return number * number;
}

int factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(4));
    if(number < 0){
        throw std::runtime_error("NUMBER CAN'T BE NEGATIVE");
    }
    else if(number == 0 || number == 1){
        return 1;
    }
    else{
        return number * factorial(number - 1);
    }
}

int main()
{
    // Step 1: Make a promise
    std::promise<int> pr;

    // Step 2: A future linked to the promise
    std::future<int> ft = pr.get_future();

    /*
        * OS: Launch Square (if possible as a new thread) 
    */
    std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));
    
    // std::cout<< factorial(5);
    int val = 0;
    std::cin>>val;
    pr.set_value(val);
    std::cout<<"\nResult of the Factorial is: "<<result_ft.get();
}

/*
    client-server architecture



    future promise model


    square calculation 

    Main need to deligate the task of the square calculation

    -----> A ne thread for square will be registered with OS

    *******Call function in async thread and call in the main function******
*/