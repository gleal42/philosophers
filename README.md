# philosophers
Introduction to threads and mutexes

With this project I learned how difficult it is to synchronize threads without having data races and how it can be difficult to coordinate both threads and processes.

For the Bonus I killed the processes using the sigterm signal after I trying to use the exit command and untrackable data races started occurring.

Definitely a very useful project. Can't wait to use threads in other projects!

## 1 Data races

Compiling with fsanitize=thread

We must have all shared variables protected by mutexes (having a mutex before and after the chunks of code which contain).
I used this template a lot:

```
int function ()
pthread_mutex_lock(&mutex);
if (validation)
{
	pthread_mutex_unlock(&mutex);
	return (1);
}
pthread_mutex_unlock(&mutex);
return (0);
```

## 2 Monitoring the philosophers at all times

In my opinion we shouldn't have the philosophers monitor if they died already:

- They can't see if they died if they are stuck in a mutex so if they are waiting for one of the forks they will not know that they died;

So I can only see 3 ways of solving this:

#### 2.1 - Main thread analyzes death by accessing the last_meal_time of each philosopher



#### 2.2 - We create variables for the forks to indicate if they are being used or not

I believe this could slow down the whole process because these variables need to be protected by mutexes.
However I didn't test and compare this with the 1st way of solving it.

##### 2.3 - Philosopher predicts if he will be stuck in fork at the time of death

For me this defeats the purpose of the exercise. They should check when
they die and not just predict it)
