# Philosophers – *"I never thought philosophy would be so deadly"*

This project is a classic computer science problem that explores **synchronization, resource management, and concurrency**.  

The goal is to simulate a group of philosophers sitting at a round table who alternate between **thinking, eating, and sleeping**. The challenge lies in preventing them from **starving** or **deadlocking** while competing for a limited number of forks.  

This implementation is written entirely in **C**:  
- **Mandatory part** → uses `pthreads` and `mutexes`   

## 🧩 The Problem
The dining philosophers problem is stated as follows:  

- A number of philosophers are sitting at a round table.  
- In the center of the table, there is a large bowl of spaghetti.  
- Between each pair of adjacent philosophers, there is **one fork**.  
- There are as many forks as there are philosophers.  
- To eat, a philosopher needs to pick up **both their left and right forks**.  
- A philosopher can only pick up **one fork at a time**.  
- When a philosopher is done eating, they put both forks down, making them available to others.  

The simulation must avoid two main issues:  
- **Deadlock** → Every philosopher picks up one fork and waits forever for the other.  
- **Starvation** → A philosopher is perpetually denied access to forks while others eat.  


## ⚙️ How It Works
- Each philosopher is a **separate thread** (or **process** in the bonus part).  
- A **monitoring thread** constantly checks if any philosopher has exceeded `time_to_die` since their last meal.  
- If a philosopher hasn't eaten within this time → the simulation **stops**, and a `"died"` message is printed.  
- To prevent deadlocks, the logic ensures that philosophers cannot wait indefinitely for forks.  

The simulation ends when:  
- A philosopher dies, or  
- All philosophers have eaten a specified number of times.  

---
### Installation & Compilation
Clone the repository
```
git clone https://github.com/Jerehirvonenn/Philosophers.git
```
```
cd Philosophers
```
---

## 🖥️ Usage
Run the program with the following syntax:  
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Argument Descriptions

number_of_philosophers → Number of philosophers (and forks)

time_to_die (ms) → Time a philosopher survives without eating

time_to_eat (ms) → Duration of eating

time_to_sleep (ms) → Duration of sleeping

[number_of_times_each_philosopher_must_eat] (optional) → If provided, simulation ends when all philosophers have eaten at least this many times
#  


Example
```bash
./philo 5 800 200 200 7
```



This runs a simulation with:

5 philosophers

800 ms to live without food

200 ms to eat, 200 ms to sleep

Ends when each philosopher has eaten 7 times

Output Example

<timestamp_ms> <philosopher_id> has taken a fork

<timestamp_ms> <philosopher_id> is eating

<timestamp_ms> <philosopher_id> is sleeping

<timestamp_ms> <philosopher_id> is thinking

<timestamp_ms> <philosopher_id> died

## 📜 Rules & Constraints
Mandatory Part

Program name: philo

Concurrency: Uses pthreads (each philosopher = one thread)

Synchronization: Uses pthread_mutex for each fork

Restrictions: No global variables allowed
