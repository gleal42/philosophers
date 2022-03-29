# philosophers
Introduction to threads and mutexes

I had a lot of problems with this project:

I will present the main issues and possible solutions, some that I tried others that I considered:

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
