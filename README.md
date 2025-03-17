# Philosophers - I never thought philosophy would be so deadly

## 📌 Description

**Philosophers** is a simulation project written in **C** that implements the classic Dining Philosophers problem using threads and mutexes. In this simulation, a group of philosophers sits around a circular table. Each philosopher alternates between eating, sleeping, and thinking. To eat, a philosopher must pick up two forks—one to their left and one to their right—while ensuring proper synchronization to avoid deadlocks and data races.

---

## 🎮 Features

- **Multithreaded simulation** using POSIX threads
- **Mutex-protected fork access** to prevent race conditions and deadlocks
- **Accurate time tracking** for philosopher actions and starvation detection
- **Customizable parameters** through command-line arguments
- **Real-time logging** of actions (fork pickup, eating, sleeping, thinking, death)
- **Strict adherence** to the 42 School coding norm

---

## 🚀 Command-Line Arguments

The program accepts the following arguments:

1. `number_of_philosophers` – Number of philosophers (and forks).
2. `time_to_die` (in milliseconds) – Maximum time a philosopher can go without eating before dying.
3. `time_to_eat` (in milliseconds) – Duration a philosopher spends eating.
4. `time_to_sleep` (in milliseconds) – Duration a philosopher spends sleeping.
5. `[number_of_times_each_philosopher_must_eat]` (optional) – If provided, the simulation ends when all philosophers have eaten at least this many times.

---

## 🛠 Compilation and Execution


### 🔧 Compilation

```sh
make
```


⸻

### ▶️ Execution

Run the program by passing the required arguments:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Example:

```sh
./philo 5 800 200 200 7
```
	•	5 philosophers, 800ms time to die, 200ms time to eat, 200ms time to sleep, and the simulation stops when each philosopher has eaten at least 7 times.

⸻


## 📂 Project Structure
```
42_philosophers/
├── philo/
│   ├── include/
│   │   └── philo.h               # Main header file with prototypes and structures
│   ├── src/
│   │   ├── init.c                # Initialization logic
│   │   ├── main.c                # Entry point (main function)
│   │   ├── philo_monitor.c       # Monitoring thread logic
│   │   ├── philo_routine.c       # Philosopher routine (eating, sleeping, thinking)
│   │   ├── philo_routine_tools.c # Helper functions for philosopher routine
│   │   └── philo_utils.c         # Utility functions (time tracking, printing, etc.)
├── Makefile                      # Compilation instructions
├── .gitignore                    # Git ignore rules
├── errors_log                    # Potential log file for errors
├── README.md                     # Project documentation
├── start.sh                      # Script to launch or test the project
└── Sujet en PDF.pdf             # Project instructions in PDF
```

⸻

## 📝 Norm and Submission
	•	The project is written in C and must adhere to the 42 School coding standard (Norme).
	•	All dynamically allocated memory must be freed; no global variables are allowed.
	•	Submission: Only files within the assigned Git repository will be evaluated.

⸻

👤 Author
-   **vbonnard** (<vbonnard@student.42perpignan.fr>)

⸻

## ℹ️ Notes

This project is part of the 42 School curriculum and focuses on multithreading and synchronization using mutexes. The bonus part (using processes and semaphores) is only evaluated if the mandatory part is fully functional.

If you encounter any issues or have suggestions, please feel free to contact me or contribute improvements!

⸻

Feel free to modify the author information and any details to suit your project requirements.
