# Philosophers 🍝 - Threads and Mutexes in C

## 📌 Description

**Philosophers** is a project developed in **C**, demonstrating the fundamentals of threading, synchronization, and mutexes. It simulates the classic synchronization problem known as **"Dining Philosophers"**, highlighting issues like resource contention and avoiding race conditions.

The simulation involves philosophers who alternate between three states:

- 🍝 **Eating**
- 💤 **Sleeping**
- 💭 **Thinking**

Each philosopher needs two forks (mutex-protected resources) to eat. The goal: No philosopher should starve!

---

## 🎮 Features

- 🔀 **Multi-threaded simulation** using `pthread`
- 🔒 **Mutex synchronization** to protect shared resources (forks)
- 🕒 **Precise timing** to ensure accurate simulation (milliseconds precision)
- 📝 **Detailed logs** of philosopher states and actions
- 🚨 **Death detection** and graceful termination
- 📈 **Optional meal-count limit** to control simulation duration
- ❌ **Robust error handling and input validation**

---

## 🛠 Compilation and Execution

### 🔧 **Compilation**

Compile the project using:

```sh
make
```

### ▶️ **Execution**

Execute the simulation with the following syntax:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: Number of philosopher threads
- `time_to_die`: Time in milliseconds before a philosopher dies without eating
- `time_to_eat`: Duration in milliseconds each philosopher spends eating
- `time_to_sleep`: Duration in milliseconds each philosopher spends sleeping
- `[number_of_times_each_philosopher_must_eat]` *(optional)*: How many times each philosopher must eat before simulation stops

Example:

```sh
./philo 5 800 200 200
```

---

## 📂 Project Structure

```
42_philosophers/
├── philo/
│   ├── include/
│   │   └── philo.h                 # Main header with definitions
│   └── src/
│       ├── init.c                  # Initialization of data structures and mutexes
│       ├── main.c                  # Program entry point and thread management
│       ├── philo_monitor.c         # Monitoring philosopher states and termination
│       ├── philo_routine_tools.c   # Fork handling and utility routines
│       ├── philo_routine.c         # Philosopher behavior routines
│       └── philo_utils.c           # Utility functions for timing and printing
├── Makefile                        # Compilation rules
├── README.md                       # Project documentation
├── .gitignore                      # Git ignore file
├── start.sh                        # Script to launch tests
└── Sujet en PDF.pdf                # Original subject description
```

---

## ⌨️ Controls

| Arguments          | Description                               |
|--------------------|-------------------------------------------|
| `CTRL+C`  | Stop simulation manually (terminal)       |

---

## 📜 Author

- **vbonnard** (<vbonnard@student.42perpignan.fr>)

---

## 📌 Note

This project was developed as part of **42 School**, focusing on thread synchronization, mutex handling, and efficient multi-threaded programming practices. If you encounter issues or have ideas for improvements, feel free to contribute! 🚀
