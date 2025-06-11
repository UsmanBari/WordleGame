# 🎯 Wordle SFML Game

A graphical clone of the classic **Wordle** game made in **C++** using **SFML**. Guess the hidden 5-letter word in 6 tries! With colorful visual feedback and keyboard input, this mini-project offers a polished arcade-like take on the viral word puzzle game.

![Language](https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square)
![Framework](https://img.shields.io/badge/SFML-2.5-green?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-purple?style=flat-square)
![License](https://img.shields.io/badge/License-Educational-lightgrey?style=flat-square)

---

---

## 🕹 Features

- 🎮 Classic Wordle mechanics with a graphical grid
- ✅ Green: Correct letter & position
- 🟨 Yellow: Correct letter, wrong position
- ❌ Red: Incorrect letter
- 🔤 Real-time keyboard input
- 📦 Built-in list of 50 valid 5-letter words
- 🧠 Feedback-based color grading
- 🎉 Game over + win message rendering

---

## 🛠 Requirements

- **C++17 or later**
- **SFML 2.5+**
- A font file (like `arial.ttf`) in the executable directory

---

## ⚙️ How to Compile

### On Linux:

```bash
sudo apt install libsfml-dev
g++ wordle.cpp -o wordle -lsfml-graphics -lsfml-window -lsfml-system
./wordle
```

### On Windows:

- Download and install [SFML](https://www.sfml-dev.org/)
- Use an IDE like **Visual Studio**, link the SFML libraries
- Place `arial.ttf` in the same directory as your `.exe`

---

## 📂 Files Included

```
wordle.cpp       # Main source file
arial.ttf        # Required font (not included – add manually)
README.md        # This file
```

---

## 👨‍💻 Developer

- **Muhammad Usman Bari** –

---

## 📝 License

This project is for **educational and personal use only**. All third-party assets (like fonts) must be used under their respective licenses.

---

> 💡 *Inspired by the viral game by Josh Wardle, reimagined in C++ and SFML.*
