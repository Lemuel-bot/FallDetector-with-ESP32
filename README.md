 **Fall Detection System – ESP32 & Telegram Alerts**  

**Project Overview**  
This project is a **Fall Detection System** using an **ESP32 microcontroller** and an **MPU6050 accelerometer**. It monitors motion and detects sudden falls. When a fall occurs, the system:  

✅ Activates a **buzzer and LED** for immediate alert.  
✅ Sends a **Telegram notification** to caregivers.  

**Components Used**  
- **ESP32** – Microcontroller  
- **MPU6050 Accelerometer** – Motion detection  
- **Buzzer & LED** – Alerts  
- **Wi-Fi & Telegram Bot** – Remote notifications  

**How It Works**  
1. **Read Acceleration Data** (X, Y, Z values)  
2. **Compute Acceleration Magnitude**  
3. **Detect Fall** (Threshold-based)  
4. **Trigger Alerts** (Buzzer, LED, Telegram message)  

**Setting Up the Telegram Bot**  
1. Create a bot via **@BotFather** on Telegram.  
2. Get your **Bot Token** and **Chat ID**.  
3. Replace `telegramBotToken` and `chatID` in the code.  

**📜 License**  
Open-source for educational purposes.  
