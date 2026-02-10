<a id="readme-top"></a>

<div align="center">

# 🍝 Philosophers

**The Dining Philosophers Problem — solved with threads and mutexes | 42 School Project**

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norm-OK-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)

---

*N philosophers sit at a round table with a bowl of spaghetti. Between each pair of philosophers is a fork. They must eat, think, and sleep — but never die of starvation.*

</div>

---

## 📖 Table of Contents

- [About](#-about)
- [The Problem](#%EF%B8%8F-the-problem)
- [Features](#-features)
- [How It Works](#%EF%B8%8F-how-it-works)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#-usage)
- [Output Format](#-output-format)
- [Project Structure](#-project-structure)
- [Concurrency Details](#-concurrency-details)
- [Author](#-author)

---

## 🧠 About

**Philosophers** is a classic concurrency problem from the 42 curriculum, based on [Dijkstra's Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). The goal is to create a multithreaded simulation where philosophers must share limited resources (forks) without causing **deadlocks** or **data races** — and without any philosopher starving.

This project builds strong foundations in:

- **POSIX threads** (`pthread`) creation & management
- **Mutexes** for safe shared resource access
- **Race condition** prevention & deadlock avoidance
- Precise **time management** with `gettimeofday`
- Thread **synchronization** patterns

---

## 🍽️ The Problem

```
         🧑‍🎓          
       /    \        
     🍴      🍴      
    /          \     
  🧑‍🎓   🍝🍝🍝   🧑‍🎓  
    \          /     
     🍴      🍴      
       \    /        
         🧑‍🎓          
```

- **N philosophers** sit around a circular table
- There is **one fork between each pair** of philosophers (N forks total)
- To **eat**, a philosopher must pick up **both** adjacent forks
- After eating, they **sleep**, then **think**, then try to eat again
- If a philosopher doesn't eat within `time_to_die` ms, they **die**
- The simulation stops when a philosopher dies or all have eaten enough meals

### Philosopher Lifecycle

```
┌─────────┐     ┌─────────┐     ┌─────────┐
│THINKING │ ──▶ │ EATING  │ ──▶ │SLEEPING │
└─────────┘     └─────────┘     └─────────┘
     ▲               │                │
     └───────────────┘────────────────┘
```

---

## ✨ Features

| Feature | Description |
|:--------|:------------|
| 🧵 **Thread per Philosopher** | Each philosopher runs as an independent POSIX thread |
| 🔒 **Mutex-Protected Forks** | Each fork is a mutex — no two philosophers can hold the same fork |
| 👁️ **Monitor Thread** | A dedicated thread continuously checks for deaths and meal completion |
| ⏱️ **Precise Timing** | Custom `precise_usleep` with spin-lock for microsecond accuracy |
| 🔄 **Desynchronization** | Even/odd staggering prevents immediate deadlocks at startup |
| 🎨 **Debug Mode** | Color-coded output with emojis and fork IDs (toggle `DEBUG_MODE`) |
| 🛡️ **Safe Wrappers** | `safe_malloc`, `safe_mutex_handle`, `safe_thread_handle` with full error reporting |
| 🧹 **Clean Shutdown** | All mutexes destroyed and memory freed on exit |
| 🧑 **Lone Philosopher** | Special handling for the single-philosopher edge case |

---

## ⚙️ How It Works

### Thread Architecture

```
┌──────────────────────────────────────────────────────────┐
│                        MAIN THREAD                       │
│                                                          │
│  1. Parse input                                          │
│  2. Initialize table, forks (mutexes), philosophers      │
│  3. Create N philosopher threads + 1 monitor thread      │
│  4. Signal all threads to start simultaneously           │
│  5. Join all threads → clean up                          │
└──────────────────────────────────────────────────────────┘
         │                                    │
         ▼                                    ▼
┌─────────────────┐              ┌──────────────────────┐
│  PHILO THREAD   │ × N          │   MONITOR THREAD     │
│                 │              │                      │
│  wait for start │              │  wait for all ready  │
│  loop:          │              │  loop:               │
│    eat()        │              │    check each philo  │
│    sleep()      │              │    if died → end     │
│    think()      │              │    if all full → end │
└─────────────────┘              └──────────────────────┘
```

### Deadlock Prevention

Philosophers are assigned forks in an **alternating order** based on their ID:

- **Odd-ID** philosophers pick up the **right** fork first, then left
- **Even-ID** philosophers pick up the **left** fork first, then right

This breaks the circular wait condition that causes deadlocks.

### Synchronization

- All threads are created first, then released simultaneously via `all_threads_ready`
- Even philosophers are staggered by a short sleep at startup
- Odd-count tables use a calculated `think` time to balance fork access

---

## 🚀 Getting Started

### Prerequisites

- **GCC** or **CC** compiler
- **Make**
- **POSIX threads** support (standard on Linux/macOS)

### Installation

```bash
# Clone the repository
git clone https://github.com/mmiguelo/philosophers.git
cd philosophers

# Build the project
make
```

---

## 🎯 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

<div align="center">

| Argument | Description |
|:---------|:------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in **ms** before a philosopher dies without eating |
| `time_to_eat` | Time in **ms** a philosopher spends eating |
| `time_to_sleep` | Time in **ms** a philosopher spends sleeping |
| `[number_of_meals]` | *(Optional)* Simulation stops after all eat this many times |

</div>

**Examples:**

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Same but stop after each philosopher eats 7 times
./philo 5 800 200 200 7

# A philosopher will die (time_to_die too short)
./philo 4 310 200 100

# Single philosopher (will always die — only 1 fork)
./philo 1 800 200 200
```

---

## 📺 Output Format

Each action is timestamped in milliseconds from simulation start:

```
0      1 has taken a fork
0      1 has taken a fork
0      1 is eating
200    1 is sleeping
200    2 has taken a fork
200    2 has taken a fork
200    2 is eating
400    1 is thinking
...
```

### Debug Mode

Set `DEBUG_MODE` to `1` in `philo.h` for enhanced output with colors and fork details:

```
     0 1 has taken the first fork 🍽️          nº[🍴 2  🍴]
     0 1 has taken the second fork 🍽️         nº[🍴 1  🍴]
     0 1 is eating 🍝                         [🍝 1  🍝]
   200 1 is sleeping 😴
              💀💀💀    810 3 died 💀💀💀
```

---

## 📁 Project Structure

```
philosophers/
├── 📄 Makefile
├── 📖 README.md
├── includes/
│   └── philo.h                # Header: structs, enums, prototypes, colors
└── src/
    ├── main.c                 # Entry point & argument dispatch
    ├── parsing.c              # Input validation & table config
    ├── init.c                 # Table, fork & philosopher initialization
    ├── dinner.c               # Simulation loop: eat → sleep → think
    ├── monitor.c              # Death detection & end-condition monitor
    ├── write.c                # Thread-safe status logging (normal + debug)
    ├── safe_function.c        # Safe wrappers: malloc, mutex, thread ops
    ├── syncro_utils.c         # Thread synchronization & desync helpers
    ├── getters_setters.c      # Mutex-protected getters/setters for shared data
    └── utils.c                # Time functions, precise_usleep, cleanup
```

---

## 🔬 Concurrency Details

### Shared Data Protection

| Data | Protected By |
|:-----|:-------------|
| Each fork | Individual `t_mtx` per fork |
| Philosopher state (`full`, `last_meal_time`) | Per-philosopher `philo_mutex` |
| Table state (`end_simulation`, `all_threads_ready`) | `table_mutex` |
| Console output (`printf`) | `write_mutex` |

### Timing Strategy

The `precise_usleep` function avoids the inaccuracy of `usleep()` alone:

1. If remaining time > 1ms → `usleep(remaining / 2)` (efficient sleep)
2. If remaining time ≤ 1ms → **spin-lock** (busy-wait for precision)
3. Checks `simulation_finished` each iteration for fast shutdown

---

## 🛠️ Makefile Targets

| Command | Description |
|:--------|:------------|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full recompile |
| `make san` | Compile with `-fsanitize=thread` |
| `make rv` | Run with Valgrind (use `ARGS="5 800 200 200"`) |

---

## 👤 Author

**mmiguelo** — 42 Student

[![GitHub](https://img.shields.io/badge/GitHub-mmiguelo-181717?style=for-the-badge&logo=github)](https://github.com/mmiguelo)

---

<div align="center">

*Made with ❤️ at 42*

<p>(<a href="#readme-top">⬆️ back to top</a>)</p>

</div>
