# Pomodoro-Timer

A tangible user interface designed to help individuals manage their work-rest cycles in a gentle, adaptive, and non-intrusive way. Inspired by the "Weekend Alarm" project (Spaa et al., 2019) and the Pomodoro Technique (Cirillo, 2018), this system dynamically adjusts session durations based on user input to reduce burnout and support creativity.

---

## Overview

The Adaptive Break and Work Timer is an Arduino-based system that supports healthy work rhythms using **ambient cues** and **user-driven feedback**. Rather than rigid countdowns or loud alerts, the system subtly guides users between periods of focused work and restful breaks through a screen, pulsing LED, and chime.

The system responds to button presses as indicators of stress or fatigue. Frequent presses during a work session will shorten the current focus time and lengthen the upcoming break. This makes it ideal for students, remote workers, creatives, and anyone seeking a more mindful, stress-sensitive approach to productivity.

---

## Key Features

- **Adaptive Timing**: Button presses shorten work duration by 25% increments, supporting flexible pacing based on stress levels.
- **Non-intrusive Feedback**: Ambient LED pulses and single chime signals replace disruptive alarms.
- **User-Controlled Breaks**: Breaks do not start until explicitly requested—offering flexibility and autonomy.
- **Minimalist Interface**: A screen provides simple prompts during transitions without overwhelming visual input.
- **Creative Support**: Encourages flow states and emotional regulation through embodied interaction and calm technology principles.

---

## Motivation

Strict timers can disrupt creative flow and heighten cognitive fatigue. This project replaces rigid structures with ambient, user-sensitive feedback to support emotional well-being and sustainable productivity. It's especially helpful in cognitively demanding or self-directed environments like writing, coding, or designing.

Inspired by:
- **Weekend Alarm (Spaa et al., 2019)**: Ambient cues for rest awareness
- **Pomodoro Technique (Cirillo, 2018)**: Structured intervals of work and rest
- **Calm Technology (Weiser & Brown, 1997)**: Informative yet unobtrusive system design

---

## System Components

- **Arduino Uno** or compatible board
- **LCD Screen** (16x2)
- **Physical Buttons** (Work, Stress, Break)
- **LED** for ambient pulsing feedback
- **Buzzer** for soft audio chime

---

## System Flow

1. **Start a Work Session**  
   Press **Button A** to begin a 60-minute focus session.

2. **Signal Stress or Fatigue**  
   Press **Button B** to shorten the session by 25% per press. This adapts the duration to your mental state.

3. **End of Work Session**  
   A chime sounds, and the screen prompts: `"Take a break"`  
   The LED begins to pulse ambiently.

4. **Start a Break**  
   Press **Button C** when you're ready. A hidden 15-minute break timer begins.  
   Screen shows: `"Rest well!"`

5. **End of Break**  
   Another chime and display update: `"Break time over!"`  
   LED pulses to gently signal return to work.

6. **Repeat**  
   Press **Button A** again to start a new session cycle.
